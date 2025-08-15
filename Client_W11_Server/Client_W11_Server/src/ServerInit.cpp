#include "ServerInit.h"

ServerInit::ServerInit()
	: serverSocket(INVALID_SOCKET), acceptSocket(INVALID_SOCKET),
      port(55555), wsaData(), wsaerror(), wVersionRequired(), service(), buffer(), byteCount()
{
}

ServerInit::~ServerInit()
{
}

void ServerInit::Startup()
{
	wVersionRequired = MAKEWORD(2, 2);

	wsaerror = WSAStartup(wVersionRequired, &wsaData);

	if (wsaerror != 0) {
		
		std::cout << "The Winsock dll not found!" << std::endl;
	}

	else {

		std::cout << "The Winsock dll found!" << std::endl;
		std::cout << "The Status: " << wsaData.szSystemStatus << std::endl;
	}
}

void ServerInit::Socket()
{

	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (serverSocket == INVALID_SOCKET) {

		std::cout << "Error at socket()!" << WSAGetLastError() << std::endl;
		return;
	}

	else {

		std::cout << "socket() is OK!" << std::endl;
	}
}

void ServerInit::Bind()
{
	
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);

	service.sin_port = htons(port);

	if (bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		
		std::cout << "Error bind() failed!" << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return;
	}
	
	else {

		std::cout << "bind() is OK!" << std::endl;
	}
}

void ServerInit::Listen()
{
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		
		std::cout << "listen(): Error listening to socket " << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return;
	}

	else {

		std::cout << "listen() is OK, I'm waiting for connections..." << std::endl;
	}
}

void ServerInit::Accept()
{
	
	std::vector<SOCKET> clients;
	while (true) {
		
		acceptSocket = accept(serverSocket, NULL, NULL);

		if (acceptSocket == INVALID_SOCKET) {

			std::cout << "accept failed: " << WSAGetLastError() << std::endl;
			closesocket(serverSocket);
			WSACleanup();
			return;
		}
		
		SOCKET currentClient = acceptSocket;

		clients.push_back(currentClient);

		std::thread t1([this, currentClient, &clients]() {
			this->ClientInteract(currentClient, clients); 
		});

		t1.detach();
	}
}


void ServerInit::ClientInteract(SOCKET clientSocket, std::vector<SOCKET>& clients) {
	std::cout << "Client connected: " << clientSocket << std::endl;

	char buffer[4096];
	int byteCount;

	while (true) {
		byteCount = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

		if (byteCount > 0) {
			buffer[byteCount] = '\0';  // Null-terminate the string
			std::cout << "Message from client " << clientSocket << ": " << buffer << std::endl;

			// Broadcast to other clients
			for (auto client : clients) {
				if (client != clientSocket) {
					send(client, buffer, byteCount, 0);
				}
			}
		}
		else if (byteCount == 0) {
			std::cout << "Client " << clientSocket << " disconnected" << std::endl;
			break;
		}
		else {
			std::cout << "recv failed for client " << clientSocket << ": " << WSAGetLastError() << std::endl;
			break;
		}
	}

	// Remove client from list
	auto it = find(clients.begin(), clients.end(), clientSocket);
	if (it != clients.end()) {
		clients.erase(it);
	}

	closesocket(clientSocket);
}
