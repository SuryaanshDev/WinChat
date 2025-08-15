#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include "ClassInit.h"

int main() {
	
	ClassInit client;
//------------------Setting up the dll----------------------
	std::cout << "\n==========Setting up the DLL==========\n" << std::endl;
	
	client.Startup();
	
	//-------------------------------------------------------------------------------

//-----------------------------------Setting up the Client Socket--------------------
	std::cout << "\n==========Setting up the server==========\n" << std::endl;
	
	client.ClientSocket();

//-----------------------------------------------------------------------------------
	
//-------------------------------------Connecting the socket to server----------------
	std::cout << "\n==========Connecting to the server==========\n" << std::endl;

	client.Connect();

	system("pause");
	WSACleanup();
	return 0;
//------------------------------------------------------------------------------------
}