#include "ClassInit.h"

ClassInit::ClassInit()
	:clientSocket(INVALID_SOCKET), port(55555), wsaData(), wsaerror(), wVersionRequired(),
	clientService(), buffer(), byteCount()
{
}

ClassInit::~ClassInit()
{
}

void ClassInit::Startup()
{

	port = 55555;

	wVersionRequired = MAKEWORD(2, 2);

	wsaerror = WSAStartup(wVersionRequired, &wsaData);

	if (wsaerror != 0) {
		
		std::cout << "Winsock dll not found!" << std::endl;
		return;
	}

	else {

		std::cout << "The Winsock dll found!" << std::endl;
		std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
	}
}

void ClassInit::ClientSocket()
{
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (clientSocket == INVALID_SOCKET) {
		
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return;
	}

	else {

		std::cout << "socket() is OK!" << std::endl;
	}
}

void ClassInit::Connect()
{

	clientService.sin_family = AF_INET;

	InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);

	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService))) {

		std::cout << "Client: connect()- Failed to connect." << std::endl;
		closesocket(clientSocket);
		WSACleanup();
	}

	else {

		std::cout << "Client: connect() is OK!" << std::endl;
		std::cout << "Client can start sending and recieving data" << std::endl;
	}

	SOCKET currentSocket = clientSocket;

	std::thread senderthread([this, currentSocket]() { this->Send(currentSocket); });
	std::thread rcvrthread([this, currentSocket]() { this->Recv(currentSocket); });

	senderthread.join();
	rcvrthread.join();
}

void ClassInit::Send(SOCKET clientSocket) {

	std::cout << "Enter your name: ";
	std::string name;
	std::getline(std::cin, name);
	

	while (true) {

		std::string message;
				
		std::getline(std::cin, message);

		std::string msg = name + " : " + message;

		byteCount = send(clientSocket, msg.c_str(), msg.size(), 0);
		
		if (byteCount > 0) {

			std::cout << " Message Sent... " << std::endl;
		}

		if (message == "quit") {
			
			std::cout << "Stopping the application..." << std::endl;
			break;
		}
	}
	
	closesocket(clientSocket);
	WSACleanup();
}

void ClassInit::Recv(SOCKET clientSocket) {
	
	char buffer[4069];
	int recvLength;

	std::string msg = "";
		
	while (true) {
		
		recvLength = recv(clientSocket, buffer, sizeof(buffer), 0);

		if (recvLength <= 0) {
			
			std::cout << "Disconnected from the server..." << std::endl;
			break;
		}

		else {

			msg = std::string(buffer, recvLength);
			std::cout << msg << std::endl;
		}
	}
	
	closesocket(clientSocket);
	WSACleanup();
}
