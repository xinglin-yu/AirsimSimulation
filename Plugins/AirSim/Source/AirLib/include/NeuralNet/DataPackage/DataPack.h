#pragma once

#ifndef _DATAPACK_H
#define _DATAPACK_H

//定义数据包类,用来将发送的数据进行打包
class DataPack
{
public: //公有成员
	char Data[200];//数据包数据 
	char Length;//数据包长度

public: //公有方法
	void PackPoint(float Point); //浮点数包
	void PackPoint3(float P1, float P2, float P3); //3个点
	void PackPoint6(float P1, float P2, float P3, float P4, float P5, float P6); //6个点
																				 //数据包帧尾
	void PackEnd();
	//解析包
	void PackAnalyze(char *data_buf, char num, float *output);
};


#endif
