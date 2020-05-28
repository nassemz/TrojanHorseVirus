//-------------------------------------------------------------
//                  Socket.h
//-------------------------------------------------------------
#ifndef SOCKET_H
#define SOCKET_H

//The Definition of the socket Class.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <windows.h>
#include <string.h>
#include <string>
#include <iostream>
#include <list>

using namespace std;

//Constants
const int MAXHOSTNAME = 100;  // Max size of a Hostname
const int IPLEN = 16;         // Max ip len'
const int MAXRECV = 300;      // Max buffer size to used for Transmission
const int DEFAULTPORT = 8001; // The Default port to use in case no port has been supplied.
const char DEFAULTIP[] = "127.0.0.1";

class Socket_t{
private:
	SOCKET m_sock;
	struct sockaddr_in m_addr;

public:
	Socket_t();
	~Socket_t();  //Use of this class only with Inheritation. 
	
	//Function for Server initialization
	bool check();
	bool create();
	bool bind ( const int port, const char IPAdr[] );
	bool listen() const;
	bool accept ( Socket_t& ) const;
	
	//Functions for Client initialization
	bool connect (const int port, const char IPAdr[]);
	
	//Functions for Data Transmission
	bool send ( const std::string ) const;
	int recv ( std::string& ) const;

	const Socket_t& operator << (const string&) const; //send opr'
	const Socket_t& operator >> (string&) const;       //Recieve opr'

private:
	
	Socket_t(const Socket_t&);
	void operator=(const Socket_t&);
};



#endif