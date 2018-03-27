#include "MechanismModel.h"

namespace msr {
	namespace airlib {

		void MechanismModel::LinearModel(Vector3r force, real_T mass, Pose current_pose, Vector3r gravity, Vector3r& linear_accel)
		{
			real_T pitch, roll, yaw;
			real_T cp, sp, cr, sr, cy, sy;

			//欧拉角度
			VectorMath::toEulerianAngle(current_pose.orientation, pitch, roll, yaw);//求欧拉角度
			cp = std::cos(pitch); sp = std::sin(pitch);
			cr = std::cos(roll); sr = std::sin(roll);
			cy = std::cos(yaw); sy = std::sin(yaw);

			linear_accel[0] = -(cr*sp*cy + sr*sy)*force[0] / mass; //线加速度模型
			linear_accel[1] = -(cr*sp*sy - sr*cy)*force[1] / mass;
			linear_accel[1] = -(cr*cp)*force[2] / mass;

			linear_accel -= gravity;//减去重力

		}

	}
}










