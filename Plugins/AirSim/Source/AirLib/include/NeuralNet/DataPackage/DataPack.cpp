#include "DataPack.h"

//浮点数包
void DataPack::PackPoint(float Point)
{
	//发送数据
	int cnt = 0;

	for (cnt = 0; cnt < 4; cnt++)
		Data[3 - cnt + Length] = *((char *)&Point + cnt);

	Length += cnt; //更新数据包长度
}

void DataPack::PackPoint3(float P1, float P2, float P3)
{
	PackPoint(P1);
	PackPoint(P2);
	PackPoint(P3);
}

void DataPack::PackPoint6(float P1, float P2, float P3, float P4, float P5, float P6)
{
	PackPoint(P1);
	PackPoint(P2);
	PackPoint(P3);
	PackPoint(P4);
	PackPoint(P5);
	PackPoint(P6);
}

//数据包帧尾
void DataPack::PackEnd()
{
	//发送数据
	Data[Length++] = 'A';
	Data[Length++] = 'A';
	Data[Length++] = 'A';
	Data[Length++] = 'A';//帧尾
}
//解析包
void DataPack::PackAnalyze(char *data_buf, char num, float *output)
{
	char cRecvBuf2[4];
	//转换顺序
	for (int i = 0; i<4; i++)
		cRecvBuf2[3 - i] = *(data_buf + i);

	*output = *((float *)cRecvBuf2);
}
