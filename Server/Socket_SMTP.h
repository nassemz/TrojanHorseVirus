#ifndef SOCKET_SMTP_H_
#define SOCKET_SMTP_H_

//The Definition of the socket Class.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <windows.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;
//Constants
const int  MAXRECV_SMTP = 300;      // Max buffer size to used for Transmission
const int  MAXHOSTNAME_SMTP = 100;  // Max size of a Hostname
const int  IPLEN_SMTP = 16;         // Max ip len'
const int  DEFAULTPORT_SMTP = 25; // The Default port to use in case no port has been supplied.
const char DEFAULTIP_SMTP[] = "127.0.0.1";

class Socket_SMTP{

private:
	SOCKET m_sock;
	struct sockaddr_in m_addr;

public:
	Socket_SMTP();
	virtual ~Socket_SMTP()=0;  //Use of this class only with Inheritation. 
	
	//Function for Server initialization
	bool check();
	bool create();
	bool bind ( const int port, const char IPAdr[] );
	bool listen() const;

	bool accept ( Socket_SMTP& ) const;
	
	
	bool connect (const int port,const char* Host);
	
	//Functions for Client initialization
//	bool connect (const int port, const char IPAdr[]);
	
	//Functions for Data Transmission
	bool send ( const std::string ) const;
	int recv ( std::string& ) const;

	//const IN_ADDR Get_IP()const {return m_addr.sin_addr;}

	const string GetIP();

};



#endif