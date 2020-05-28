// PowerManager.cpp: implementation of the PowerManager class.
//
//////////////////////////////////////////////////////////////////////

#include "PowerManager_t.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PowerManager_t::PowerManager_t()
{
	
}

PowerManager_t::~PowerManager_t()
{
	
}
//----------------------------------------------------------------------
bool PowerManager_t::LogOffWin()
{
	if (ExitWindowsEx(EWX_LOGOFF,0))
		return true;
	return false;
}
//----------------------------------------------------------------------
bool PowerManager_t::ShutDownPC()
{
	HANDLE  hp = GetCurrentProcess(); 
    HANDLE  tok; 
	
	
	if(OpenProcessToken (hp, TOKEN_READ|TOKEN_ADJUST_PRIVILEGES, &tok))
	{
		if(SetPrivilege (tok, SE_SHUTDOWN_NAME, TRUE))
		{
			if(ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE , 0))
			{
				//if (ExitWindowsEx(EWX_POWEROFF,0))
				CloseHandle (tok);
				return true;
			}
		}
		
	}
	CloseHandle (tok);
	return false;
}
//----------------------------------------------------------------------
bool PowerManager_t::RebootPC()
{
	
	HANDLE  hp = GetCurrentProcess(); 
    HANDLE  tok; 
	
	
	if(OpenProcessToken (hp, TOKEN_READ|TOKEN_ADJUST_PRIVILEGES, &tok))
	{
		if(SetPrivilege (tok, SE_SHUTDOWN_NAME, TRUE))
		{
			if(ExitWindowsEx(EWX_REBOOT | EWX_FORCE , 0))
			{
				CloseHandle (tok);
				return true;
			}
		}
		
	}
	CloseHandle (tok);
	return false;
	/*
	if (ExitWindowsEx(EWX_REBOOT | EWX_FORCE ,-1))
	return true;
	return false;*/
}
/////////////////////////////////////////////////////////////////// 
// takes:   hToken              - access token handle 
//          lpszPrivilege       - name of privilege to enable/disable 
//          bEnablePrivilege    - to enable or disable privilege 
/////////////////////////////////////////////////////////////////// 
BOOL PowerManager_t::SetPrivilege (HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege) 
{ 
    TOKEN_PRIVILEGES  tp; 
    LUID  luid; 


    if (!LookupPrivilegeValue (NULL, lpszPrivilege, &luid)) 
        return FALSE; 
    

    tp.PrivilegeCount = 1; 
    tp.Privileges[0].Luid = luid; 
    if (bEnablePrivilege) 
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
    else 
        tp.Privileges[0].Attributes = 0; 


    // Enable the privilege or disable all privileges. 
    AdjustTokenPrivileges (hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL); 

    // Call GetLastError to determine whether the function succeeded. 
    if (GetLastError() != ERROR_SUCCESS) 
	 return FALSE; 
     


    return TRUE; 


} 
