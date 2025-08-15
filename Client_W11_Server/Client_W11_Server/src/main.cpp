#include "ServerInit.h"
#include <thread>
#include <vector>

int main() {

// -----------------------------------------Setting up the DLL------------------------------
	ServerInit server;

	std::cout << "\n==========Setting up the DLL==========\n" << std::endl;

	server.Startup();
//--------------------------------------------------------------------------------------------------

	//--------------------------------------Setting up Server Socket--------------------------------

	std::cout << "\n==========Setting up Server Socket==========\n" << std::endl;

	server.Socket();

	//------------------------------------------------------------------------------------------------

	//----------------------------Binding the socket to the given IP address--------------------------

	std::cout << "\n==========Binding the socket==========\n" << std::endl;
	
	server.Bind();
	//------------------------------------------------------------------------------------------------

	//---------------------------Listening to the socket--------------------------------
	
	std::cout << "\n==========Listening to the socket==========\n" << std::endl;

	server.Listen();
	//--------------------------------------------------------------------
	
	//------------------------------Accepting the connection---------------------
	std::cout << "\n==========Accepting the conenction==========\n" << std::endl;
	
	server.Accept();

	system("pause");
	WSACleanup();
	return 0;
	//---------------------------------------------------------------------------
} 