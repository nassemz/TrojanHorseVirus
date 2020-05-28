#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H
// Definition of the ClientSocket class

#include "Socket.h"

class ClientSocket : public Socket
{
public:
	
	ClientSocket (int port, const char IPAdr[]);
	virtual ~ClientSocket(){};
	
	const ClientSocket& operator << ( const std::string& ) const; //recv
	const ClientSocket& operator >> ( std::string& ) const;       //send
};
#endif