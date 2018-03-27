
#include "Thread.h"

namespace msr {
	namespace airlib {
		//数据包初始化
		DataPack dataPack;

		//UDP初始化
		UdpSever udpSever;

		DWORD WINAPI ThreadReceive(LPVOID lpParam)
		{
			while (1)
			{
				//printf("Receive Data...\n");
				udpSever.ReceiveData(udpSever.RecvBuf, &udpSever.RecvLen);//数据接收
				dataPack.PackAnalyze(udpSever.RecvBuf, udpSever.RecvLen, &udpSever.RecvOutput);//数据分析

				//Sleep(100);																				
																						
			}
			return 0;
		}


	}
}


