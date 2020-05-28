// Implementation of the ClientSocket class

#include "ClientMailSocket_t.h"
#include "SocketException_t.h"

// main constructor
ClientMailSocket_t::ClientMailSocket_t(int port, const char *IPAdr)
{
	if (!Socket_SMTP::check())
		throw SocketException_t("Comunication Error 00 : Failed to find a usable WinSock DLL");

	if (!Socket_SMTP::create())
		throw SocketException_t("Comunication Error 01 : Failed to CREATE client socket.");
	
	if (!Socket_SMTP::connect(port,IPAdr))
		throw SocketException_t("Comunication Error 02 : Failed to BIND Port.");
}


// send operator
const ClientMailSocket_t& ClientMailSocket_t::operator << (const string& String) const
{
	if (!Socket_SMTP::send(String))
		throw SocketException_t("Comunication Error 03 : Failed to WRITE to socket.");
	return *this;
}

// recv operator
const ClientMailSocket_t& ClientMailSocket_t::operator >> (string& String) const
{
	if (!Socket_SMTP::recv (String))
		throw SocketException_t ( "Comunication Error 04 : Failed to READ from socket." );
	return *this;
}
