// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.


#ifndef msr_airlib_SimpleImu_hpp
#define msr_airlib_SimpleImu_hpp

#include "common/Common.hpp"
#include "ImuSimpleParams.hpp"
#include "ImuBase.hpp"

// 按照相对路径 包含类
#include "NeuralNet/Matrix/_Matrix.h"  
#include "NeuralNet/DebugPrint/DebugPrint.h"   
#include "NeuralNet/Thread/Thread.h"

namespace msr { namespace airlib {

class ImuSimple : public ImuBase {
public:
    //constructors
    ImuSimple(const ImuSimpleParams& params = ImuSimpleParams())
        : params_(params)
    {
        gyro_bias_stability_norm = params_.gyro.bias_stability / sqrt(params_.gyro.tau);
        accel_bias_stability_norm = params_.accel.bias_stability / sqrt(params_.accel.tau);
    
		//启动线程
		CreateThread(NULL, 0, ThreadReceive, NULL, 0, NULL);		//Model线程
	}

    //*** Start: UpdatableState implementation ***//
    virtual void reset() override
    {
        ImuBase::reset();

        last_time_ = clock()->nowNanos();

        state_.gyroscope_bias = params_.gyro.turn_on_bias;
        state_.accelerometer_bias = params_.accel.turn_on_bias;
        gauss_dist.reset();
        updateOutput();
    }

    virtual void update() override
    {
        ImuBase::update();

        updateOutput();
    }
    //*** End: UpdatableState implementation ***//

    virtual ~ImuSimple() = default;

private: //methods
    void updateOutput_orign()
    {
        Output output;
        const GroundTruth& ground_truth = getGroundTruth();

        output.angular_velocity = ground_truth.kinematics->twist.angular;
        output.linear_acceleration = ground_truth.kinematics->accelerations.linear - ground_truth.environment->getState().gravity;
        output.orientation = ground_truth.kinematics->pose.orientation;

        //acceleration is in world frame so transform to body frame
        output.linear_acceleration = VectorMath::transformToBodyFrame(output.linear_acceleration, 
            ground_truth.kinematics->pose.orientation, true);

        //add noise
        addNoise(output.linear_acceleration, output.angular_velocity);
        // TODO: Add noise in orientation?

        setOutput(output);
    }

    void addNoise_orign(Vector3r& linear_acceleration, Vector3r& angular_velocity)
    {
        TTimeDelta dt = clock()->updateSince(last_time_);

        //ref: An introduction to inertial navigation, Oliver J. Woodman, Sec 3.2, pp 10-12
        //https://www.cl.cam.ac.uk/techreports/UCAM-CL-TR-696.pdf

        real_T sqrt_dt = static_cast<real_T>(sqrt(std::max<TTimeDelta>(dt, params_.min_sample_time)));

        // Gyrosocpe
        //convert arw to stddev
        real_T gyro_sigma_arw = params_.gyro.arw / sqrt_dt;
        angular_velocity += gauss_dist.next() * gyro_sigma_arw + state_.gyroscope_bias;
        //update bias random walk
        real_T gyro_sigma_bias = gyro_bias_stability_norm * sqrt_dt;
        state_.gyroscope_bias += gauss_dist.next() * gyro_sigma_bias;

        //accelerometer
        //convert vrw to stddev
        real_T accel_sigma_vrw = params_.accel.vrw / sqrt_dt;
        linear_acceleration += gauss_dist.next() * accel_sigma_vrw + state_.accelerometer_bias;
        //update bias random walk
        real_T accel_sigma_bias = accel_bias_stability_norm * sqrt_dt;
        state_.accelerometer_bias += gauss_dist.next() * accel_sigma_bias;
    }

	//是否是能MATLAB发送并接受数据
	bool MatlabEnable = true;
	//调用次数
	uint itimes = 0;
	// updateOutput by xlin*20171003
	void updateOutput()
	{
		Output output;
		const GroundTruth& ground_truth = getGroundTruth();
		Vector3r linear_velocity;
		Vector3r position;
		Vector3r linear_accel, angular_velocity;

		float pitch, roll, yaw;
		unsigned char test = 12;

		//角速度，线加速度，角度四元数
		output.angular_velocity = ground_truth.kinematics->twist.angular;	//获取 角速度
		output.linear_acceleration = ground_truth.kinematics->accelerations.linear - ground_truth.environment->getState().gravity; //获取 线加速度
		output.orientation = ground_truth.kinematics->pose.orientation;		//获取角度

		linear_velocity = ground_truth.kinematics->twist.linear;	//获取 速度
		position = ground_truth.kinematics->pose.position;	//获取 位置
															
		output.linear_acceleration = VectorMath::transformToBodyFrame(output.linear_acceleration,
			ground_truth.kinematics->pose.orientation, true);//acceleration is in world frame so transform to body frame

		//欧拉角度
		VectorMath::toEulerianAngle(output.orientation, pitch, roll, yaw);

		addNoise(linear_accel, angular_velocity);

		itimes++;
		if (MatlabEnable && itimes == 100)
		{
			itimes = 0;
			if (false)
			{
				DP0("********ImuSimple updateOutput*******\n"); //显示调试信息
				DP1("itimes: %d\n", itimes);
				DP3("angular velocity: %f  %f  %f\n", output.angular_velocity[0], output.angular_velocity[1], output.angular_velocity[2]);
				DP3("linear velocity:  %f  %f  %f\n", linear_velocity[0], linear_velocity[1], linear_velocity[2]);
				DP3("linear acceleration:  %f  %f  %f\n", output.linear_acceleration[0], output.linear_acceleration[1], output.linear_acceleration[2]);
				DP3("position:  %f  %f  %f\n", position[0], position[1], position[2]);
				DP3("linear_accel:  %f  %f  %f\n", linear_accel[0], linear_accel[1], linear_accel[2]);
			}

			//发送到MATLAB进行运算
			if (udpSever.RecvLen > 0)
			{
				//显示接收数据
				//DP1("Receive length is %d\n", udpSever.RecvLen);
				//DP1("Receive data is %f\n", udpSever.RecvOutput);
				udpSever.RecvLen = 0;

				//发送浮点数
				dataPack.PackPoint(1);
				//速度包 (角速度*线速度)
				dataPack.PackPoint6(output.angular_velocity[0], output.angular_velocity[1],output.angular_velocity[2], 
					linear_velocity[0], linear_velocity[1], linear_velocity[2]);
				//状态包 (角度*位移)
				dataPack.PackPoint6(roll, pitch, yaw, position[0], position[1], position[2]);
				//加速度包
				dataPack.PackPoint3(output.linear_acceleration[0],output.linear_acceleration[1], output.linear_acceleration[2]);
				//加速度 噪声值  打包
				dataPack.PackPoint3(linear_accel[0],linear_accel[1], linear_accel[2]);

				 //统一一起发送
				udpSever.SendData(dataPack.Data, dataPack.Length);//数据发送
				dataPack.Length = 0;

				//更新加速度
				//output.linear_acceleration[2] += udpSever.RecvOutput;
			}

		}

		//add noise
		//addNoise(output.linear_acceleration, output.angular_velocity);
		// TODO: Add noise in orientation?
		//output.linear_acceleration += linear_accel;

		setOutput(output);
	}

	void addNoise(Vector3r& linear_accel, Vector3r& angular_velocity)
	{
		TTimeDelta dt = clock()->updateSince(last_time_);

		//ref: An introduction to inertial navigation, Oliver J. Woodman, Sec 3.2, pp 10-12
		//https://www.cl.cam.ac.uk/techreports/UCAM-CL-TR-696.pdf

		real_T sqrt_dt = static_cast<real_T>(sqrt(std::max<TTimeDelta>(dt, params_.min_sample_time)));

		// Gyrosocpe
		//convert arw to stddev
		real_T gyro_sigma_arw = params_.gyro.arw / sqrt_dt;
		angular_velocity = gauss_dist.next() * gyro_sigma_arw + state_.gyroscope_bias;
		//update bias random walk
		real_T gyro_sigma_bias = gyro_bias_stability_norm * sqrt_dt;
		state_.gyroscope_bias += gauss_dist.next() * gyro_sigma_bias;

		//accelerometer
		//convert vrw to stddev
		/*20170928
		应该是有错误的
		real_T accel_sigma_vrw = params_.accel.vrw / (sqrt_dt/3);
		*/
		real_T accel_sigma_vrw = params_.accel.vrw / sqrt_dt;
		linear_accel = gauss_dist.next() * accel_sigma_vrw + state_.accelerometer_bias;
		//update bias random walk
		real_T accel_sigma_bias = accel_bias_stability_norm * sqrt_dt;
		state_.accelerometer_bias += gauss_dist.next() * accel_sigma_bias;
	}

private: //fields
    ImuSimpleParams params_;
    RandomVectorGaussianR gauss_dist = RandomVectorGaussianR(0, 1);

    //cached calculated values
    real_T gyro_bias_stability_norm, accel_bias_stability_norm;

    struct State {
        Vector3r gyroscope_bias;
        Vector3r accelerometer_bias;
    } state_;

    TTimePoint last_time_;
};


}} //namespace
#endif
