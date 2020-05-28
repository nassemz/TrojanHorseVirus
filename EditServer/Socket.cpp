#include "stdafx.h"
#include "Socket.h"
#include <iostream>
#include <string.h>

using namespace std;


//Construcor
Socket::Socket()  
{
	ZeroMemory(&m_addr, sizeof(m_addr));	
}

//Distructor
Socket::~Socket()
{
	if ( m_sock )
	::closesocket ( m_sock );
}

//Checking for and Initializing required Dynamic Link Libraries.
bool Socket::check()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD(2,2);
	
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return false;
	}

	return true;
}

//Creating the Socket.
bool Socket::create()
{
	if((m_sock = socket (AF_INET,SOCK_STREAM, 0 )) == INVALID_SOCKET)
		return false; 
		
	return true;
}

//Binding the Socket at a Port.
bool Socket::bind ( const int port, const char IPAdr[])
{
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = inet_addr(IPAdr);
	m_addr.sin_port = htons ( port );
	
	int bind_return = ::bind ( m_sock,( struct sockaddr * ) &m_addr, sizeof ( m_addr ) );
	
	if ( bind_return == -1 )
		return false;
    
	return true;
}

//Listening to Socket.
bool Socket::listen() const
{
	int listen_return = ::listen ( m_sock, SOMAXCONN );
	
	if ( listen_return == -1 ){
		return false;
    }
	
	char hostname[MAXHOSTNAME];
	
	gethostname(hostname,MAXHOSTNAME);
	
	cout<<endl<<"Host IP Address   : "<<inet_ntoa(m_addr.sin_addr);
	cout<<endl<<"Listening on Host : "<<hostname<<endl;

	return true;
}

//Accepting Conection thru a socket.
bool Socket::accept ( Socket& new_socket ) const
{
	int addr_length = sizeof ( m_addr );
	
	new_socket.m_sock = ::accept(m_sock, (sockaddr*)&m_addr, &addr_length);
	
	if ( new_socket.m_sock <= 0 )
		return false;
	else
		return true;
}



//Send Function between server/client.
bool Socket::send (const string String) const
{ 
	int status;
	
	status = ::send (m_sock, String.c_str(), String.size(), 0);
	
	if (status == -1)
		return false;
	
	return true;
}

//Recieve Function between server/client.
int Socket::recv (string& String) const
{
	char buf [ MAXRECV + 1 ];
	
	String = "";
	memset ( buf, 0, MAXRECV + 1 );  //Setting how much the buffer can recieve
	
	int status = ::recv (m_sock, buf, MAXRECV, 0);
	
	if (status == -1)
	{
		std::cout << "status == -1  in Socket::recv\n";  //internal check
		return 0;
	}
	
	else if (status == 0)
		return 0;
	
	else
	{
		String = buf;
		return 1;
	}
}


//Connect func' for the user to connect to the host/server.
bool Socket::connect (const int port,const char* Host)
{
	struct hostent *H;
	H=gethostbyname(Host);
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = *((unsigned long *) H->h_addr);//;inet_addr(IPAdr);
	m_addr.sin_port = htons (port);
	

	if(::connect(m_sock, (struct sockaddr *)&m_addr, sizeof(m_addr)) == SOCKET_ERROR)
		return false;
	

	return true;
}

const string Socket::Get_IP()
{
	SOCKADDR_IN SockAddr;
	
	char strHost[50];
	memset(strHost, 0 , 50);
	gethostname(strHost, 50);
	
	hostent* HostInfo = gethostbyname(strHost);
//	hostent* HostInfo = gethostbyname("mail.telhai.ac.il");
	memcpy(&(SockAddr.sin_addr),HostInfo->h_addr,HostInfo->h_length);
	
	char* pIP = inet_ntoa(SockAddr.sin_addr);
	string p=pIP;


	return p;
}