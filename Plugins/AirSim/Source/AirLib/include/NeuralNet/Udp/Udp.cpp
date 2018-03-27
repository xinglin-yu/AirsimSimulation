
#include "Udp.h"

UdpSever::UdpSever()
{
	UdpSever::Init();
}

void UdpSever::Init()
{
	//the version bit of Winsock  
	int version_a = 1;//low bit  
	int version_b = 1;//high bit  

					  //makeword  
	WORD versionRequest = MAKEWORD(version_a, version_b);
	WSAData wsaData;
	int error;
	error = WSAStartup(versionRequest, &wsaData);

	if (error != 0) {
		printf("ERROR!");
		return;
	}
	//check whether the version is 1.1, if not print the error and cleanup wsa?  
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		printf("WRONG WINSOCK VERSION!");
		WSACleanup();
		return;
	}
	//build a sockeet   
	socServer = socket(AF_INET, SOCK_DGRAM, 0);
	//addrSrv.sin_addr.S_un.S_addr = inet_addr(HOST_IP);        //set the host IP 
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	//set the host IP 设置为本机ip
	addrSrv.sin_family = AF_INET;     //set the protocol family  
	addrSrv.sin_port = htons(MODEL_PORT);      //set the port number  

											   //bind socket to  the host  
	bind(socServer, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
}


void UdpSever::Close()
{
	//close the socket and cleanup the wsadata  
	closesocket(socServer);
	WSACleanup();
}


/////////////////////////////////////////////////////////////////////////////////////
//// server 发送和接收
void UdpSever::SendData(char *dataToSend, char length)
{
	sendto(socServer, (char*)dataToSend, length, 0, (SOCKADDR*)&addr_Clt, sizeof(SOCKADDR));
}

void UdpSever::ReceiveData(char *dataRecv, char *length)
{
	int fromlen = sizeof(SOCKADDR);
	*length = recvfrom(socServer, (char*)dataRecv, 100, 0, (SOCKADDR*)&addr_Clt, &fromlen);
}
