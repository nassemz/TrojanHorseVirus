// Implementation of the ClientSocket class
#include "stdafx.h"
#include "ClientSocket.h"
#include "SocketException.h"

// main constructor
ClientSocket::ClientSocket(int port, const char *IPAdr)
{
	if (!Socket::check())
		throw SocketException("Comunication Error 00 : Failed to find a usable WinSock DLL");

	if (!Socket::create())
		throw SocketException("Comunication Error 01 : Failed to CREATE client socket.");
	
	if (!Socket::connect(port,IPAdr))
		throw SocketException("Comunication Error 02 : Failed to BIND Port.");
}


// send operator
const ClientSocket& ClientSocket::operator << (const string& String) const
{
	if (!Socket::send(String))
		throw SocketException("Comunication Error 03 : Failed to WRITE to socket.");
	return *this;
}

// recv operator
const ClientSocket& ClientSocket::operator >> (string& String) const
{
	if (!Socket::recv (String))
		throw SocketException ( "Comunication Error 04 : Failed to READ from socket." );
	return *this;
}
