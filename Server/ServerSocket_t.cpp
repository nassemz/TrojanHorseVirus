//-------------------------------------------------------------
//					ServerSocket.cpp
//-------------------------------------------------------------
//Implementation of the ServerSocket class.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
#include "ServerSocket_t.h"
#include "SocketException_t.h"

//Constructor
ServerSocket_t::ServerSocket_t(int port, char IPAddr[])
{
//	char tmp[IPLEN];
	if (!Socket_t::check())
		throw SocketException_t ("Comunication Error 00 : Failed to find a usable WinSock DLL");
	
	if (!Socket_t::create())
		throw SocketException_t ("Comunication Error 01 : Failed to CREAT Server Socket");
	
//	itoa(port,tmp,10);
//	MessageBox(NULL,tmp,"server Socket bind",MB_OK); // for  testing
	if (!Socket_t::bind(port,IPAddr))
		throw SocketException_t ("Comunication Error 02 : Failed to BIND Server Socket.");
	
}

//Accept a Connection from a Client.
void ServerSocket_t::accept (Socket_t& sock)
{
	if(!Socket_t::accept(sock))
		throw SocketException_t ( "Comunication Error 06 : Failed to ACCEPT socket." );
	
}
//Listen on socket
void ServerSocket_t::listen() const
{
	if (!Socket_t::listen())
		throw SocketException_t ("Comunication Error 03 : Failed to LISTEN to Server Socket.");
}
