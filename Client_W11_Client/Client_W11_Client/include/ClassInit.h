#pragma once
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <thread>
#include <sstream>

class ClassInit
{

private:

	SOCKET clientSocket;
	int port;

	WSADATA wsaData;
	int wsaerror;
	
	WORD wVersionRequired;

	sockaddr_in clientService;

	char buffer[200];
	
	int byteCount;

public:
	
	ClassInit();
	~ClassInit();

	void Startup();
	void ClientSocket();
	void Connect();
	void Send(SOCKET clientSocket);
	void Recv(SOCKET clientSocket);
};

