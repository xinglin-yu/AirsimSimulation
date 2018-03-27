/* 函数说明 UDP套接字通信示例*/

#ifndef UDPMODEL_H
#define UDPMODEL_H

#include "Winsock2.h"  
#include "iostream"  
#include "stdio.h"  
#pragma comment(lib, "ws2_32.lib")  


//定义数据传输类*服务器类
class UdpSever
{
private: //私有成员
		 //默认端口
#define MODEL_PORT		    8085  

	SOCKET socServer;
	SOCKADDR_IN addrSrv;
	// a instance of SOCKADDR_IN, which is used in format of SOCKADDR.  
	SOCKADDR_IN addr_Clt;

public: //公有成员
	char RecvBuf[100];
	char RecvLen = 0;
	float RecvOutput;

public: //公有方法
		//构造函数
	UdpSever();

	void Init();
	void Close();
	void SendData(char *dataToSend, char length);
	void ReceiveData(char *dataRecv, char *length);
};


#endif