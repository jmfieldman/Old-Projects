#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include "socket.h"

unsigned ThreadAddr;
unsigned ThreadAdd;
SOCKET listenSocket;
DWORD listenThreadHandle;
DWORD serverThreadHandle;
DWORD clientThreadHandle;
HANDLE listenThreadExit;
HANDLE serverThreadExit;
HANDLE clientThreadExit;

int serving = 0;
int clienting = 0;

unsigned _stdcall listenThread(void* arg);
unsigned _stdcall pollClient(void* arg);

void initSockets()
{
	WORD wVersionRequested = WINSOCK_VERSION;
	WSADATA wsaData;
	int nRet;

	nRet = WSAStartup(wVersionRequested, &wsaData);
	if (nRet)
	{
		WSACleanup();
		return;
	}

	if (wsaData.wVersion != wVersionRequested)
	{		
		WSACleanup();
		return;
	}	
}


void closeSockets()
{	
	closesocket(listenSocket);
	WSACleanup();
}

void addText(char* str);

void startServer()
{
	if (serving || clienting)
	{
		addText("Already busy.\n");
		return;
	}

	SOCKADDR_IN		saServer;			
	char*			szBuf;		
	char*			szAddress;
    int				nRet;				

	szBuf = new char[256];
	szAddress = new char[80];

	listenSocket = socket(AF_INET, 
						  SOCK_STREAM, 
						  IPPROTO_TCP);

	
	saServer.sin_port = htons(GAMEPORT);	
	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = INADDR_ANY;

	nRet = bind(listenSocket, 
				(LPSOCKADDR)&saServer, 
				sizeof(struct sockaddr));
	
	nRet = listen(listenSocket, SOMAXCONN);
	if (nRet == SOCKET_ERROR)
	{
		addText("Server error.\n");
		return;
	}

	listenThreadHandle = _beginthreadex(
							NULL,
							0,	
							listenThread,
							&listenThreadExit,	 
							0,			 
							&ThreadAddr);


}



SOCKET socketClient[2];

unsigned _stdcall pollClient(void* arg);
unsigned _stdcall listenThread(void* arg)
{

	addText("Server ready...\n");
	serving = 1;

	SOCKADDR_IN	SockAddr;	
	int nLen;

	int * player = new int(0);
	int * player2 = new int(1);


	nLen = sizeof(SOCKADDR_IN);
		
	socketClient[0] = accept(listenSocket,
							  (LPSOCKADDR)&SockAddr,
							  &nLen);

	addText("Waiting for connection...\n");

	socketClient[1] = accept(listenSocket,
							  (LPSOCKADDR)&SockAddr,
							  &nLen);


	addText("Client connecting...\n");

	
	int temp1 = _beginthreadex(
							NULL,
							0,	
							pollClient,
							player,	 
							0,			 
							&ThreadAddr);

	player++;
	int temp2 = _beginthreadex(
							NULL,
							0,	
							pollClient,
							player2,	 
							0,			 
							&ThreadAddr);


	return 0;
}



unsigned _stdcall pollClient(void* arg)
{
	int* pr = (int*)arg;
	int player = *pr;
	delete arg;
	int op = 0;
	if (player == 0) op = 1;

	char packet[PACKETSIZE];

	int connected = 1;

	while(connected)
	{	
		packet[0] = 0;
		
		int returnval = recv(socketClient[player],packet,PACKETSIZE,0);

		if (!returnval || packet[0] == 0)
		{
			return 0;
		}

		send(socketClient[op],packet,PACKETSIZE,0);

	}

	return 0;
}

SOCKET connection;

void handlePacket(char* packet);

unsigned _stdcall pollServer(void* arg)
{
	char packet[PACKETSIZE];
	
	while (1)
	{
		packet[0] = 0;
		
		int returnval = recv(connection,packet,PACKETSIZE,0);

		if (!returnval || packet[0] == 0)
		{
			char pack[PACKETSIZE];
			pack[0] = 'D'; pack[1] = 'I'; pack[2] = 'S'; pack[3] = 'C';
			handlePacket(pack);
			return 0;
		}

		handlePacket(packet);
	}
}

void sendData(char* packet)
{
 	send(connection,packet,PACKETSIZE,0);
}

void clientConnect(char* addr)
{
	LPHOSTENT lpHostEntry;
	lpHostEntry = gethostbyname(addr);
	
	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
	sa.sin_port = htons(GAMEPORT);	

	SOCKADDR_IN saBind;
	saBind.sin_family = AF_INET;
	saBind.sin_addr.s_addr = INADDR_ANY;
	saBind.sin_port = htons(0);	

	connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	

	int nRet = bind(connection, 
				(LPSOCKADDR)&saBind, 
				sizeof(struct sockaddr));

	nRet = connect(connection, 
	               (LPSOCKADDR)&sa, 
				   sizeof(SOCKADDR_IN));	

	if (nRet) {closesocket(connection); return ;}	
	
	addText("Succesfully connected...\n");
	clienting = 1;

	clientThreadHandle = _beginthreadex(
							NULL,
							0,	
							pollServer,
							&clientThreadExit,	 
							0,			 
							&ThreadAdd);

	return;
}

