//-------------------------------------------------------------
//					ServerSocket.h
//-------------------------------------------------------------
//Definition of the ServerSocket class.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _SERVER_SOCKET_
#define _SERVER_SOCKET_

#include "Socket_t.h"

class ServerSocket_t : private Socket_t{
	
public:
	
	ServerSocket_t (int port, char IPAdr[]);
	ServerSocket_t (){};
	virtual ~ServerSocket_t(){};
	
	void accept (Socket_t&);                           //Connec' accept
	void listen() const;
	
private:
	
	ServerSocket_t(const ServerSocket_t&);
	void operator=(const ServerSocket_t&);
};
#endif
