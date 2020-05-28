//-------------------------------------------------------------
//                  Socket_t.cpp
//-------------------------------------------------------------
#include "Socket_t.h"
#include "SocketException_t.h"
#include <iostream>
 
using namespace std;

//Construcor
Socket_t::Socket_t()  
{
	ZeroMemory(&m_addr, sizeof(m_addr));	
}

//Distructor
Socket_t::~Socket_t()
{
	if ( m_sock )
	::closesocket ( m_sock );
}

//Checking for and Initializing required Dynamic Link Libraries.
bool Socket_t::check()
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
bool Socket_t::create()
{
	if((m_sock = socket (AF_INET,SOCK_STREAM, 0 )) == INVALID_SOCKET)
		return false; 
	
	return true;
}

//Binding the Socket at a Port.
bool Socket_t::bind ( const int port, const char IPAdr[])
{

//	char tmp[IPLEN];

	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = inet_addr(IPAdr);
	m_addr.sin_port = htons ( port );
	
//	itoa(port,tmp,10);
//	MessageBox(NULL,tmp,"Socket bind",MB_OK); // for  testing
	int bind_return = ::bind ( m_sock,( struct sockaddr * ) &m_addr, sizeof ( m_addr ) );
	
	if ( bind_return == -1 )
		return false;
    
	return true;
}

//Listening to Socket.
bool Socket_t::listen() const
{
	int listen_return = ::listen ( m_sock, SOMAXCONN );
	
	if ( listen_return == -1 ){
		return false;
    }
	
	char hostname[MAXHOSTNAME];
	
	gethostname(hostname,MAXHOSTNAME);
	
	//cout<<endl<<"Host IP Address   : "<<inet_ntoa(m_addr.sin_addr);
	//cout<<endl<<"Listening on Host : "<<hostname<<endl;

	return true;
}

//Accepting Conection threw a socket.
bool Socket_t::accept ( Socket_t& new_socket ) const
{
	int addr_length = sizeof ( m_addr );
	
	new_socket.m_sock = ::accept(m_sock, (sockaddr*)&m_addr, &addr_length);
	
	if ( new_socket.m_sock <= 0 )
		return false;
	else
		return true;
}



//Send Function between server/client.
bool Socket_t::send (const string String) const
{ 
	int status;
	
	status = ::send (m_sock, String.c_str(), String.size(), 0);
	
	if (status == -1)
		return false;
	
	return true;
}

//Recieve Function between server/client.
int Socket_t::recv (string& String) const
{
	char buf [ MAXRECV + 1 ];
	
	String = "";
	memset ( buf, 0, MAXRECV + 1 );  //Setting how much the buffer can recieve
	
	int status = ::recv (m_sock, buf, MAXRECV, 0);
	
	if (status == -1)
	{
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
bool Socket_t::connect (const int port, const char IPAdr[])
{
	m_addr.sin_family = AF_INET;
	m_addr.sin_addr.s_addr = inet_addr(IPAdr);
	m_addr.sin_port = htons ( port );
	

	if(::connect(m_sock, (struct sockaddr *)&m_addr, sizeof(m_addr)) == SOCKET_ERROR)
		return false;

	return true;
}
	
//Overloaded "Send" operator for strings
const Socket_t& Socket_t::operator << (const string& String) const
{
	if (!Socket_t::send (String))
		throw SocketException_t ("Comunication Error 04 : Failed to WRITE to Socket.");
    
	return *this;
}

//Overloaded "Recieve" for strings
const Socket_t& Socket_t::operator >> (string& String) const
{
	if (!Socket_t::recv(String))
		throw SocketException_t ( "Comunication Error 05 : Failed to READ from socket." );
	
	return *this;
}
