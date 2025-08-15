#pragma once
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <vector>
#include <thread>

class ServerInit
{

private:
	
	SOCKET serverSocket, acceptSocket;
	int port;

	WSADATA wsaData;
	int wsaerror;

	WORD wVersionRequired;
	
	sockaddr_in service;

	char buffer[4069];
	int byteCount;

public:

	ServerInit();
	~ServerInit();

	void Startup();
	void Socket();
	void Bind();
	void Listen();
	void Accept();
	

	void ClientInteract(SOCKET clientSocket, std::vector<SOCKET>& clients);
};

