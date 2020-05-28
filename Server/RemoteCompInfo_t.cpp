// RemoteCompInfo.cpp: implementation of the RemoteCompInfo class.
//
//////////////////////////////////////////////////////////////////////
 
#include "RemoteCompInfo_t.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RemoteCompInfo_t::RemoteCompInfo_t()
{
	RegMng = new RegistryManager_t ;
}

RemoteCompInfo_t::~RemoteCompInfo_t()
{
	delete(RegMng);
}
//--------------------------------------------------------------------
bool RemoteCompInfo_t::GetCompName(string &CName)
{
	
	char Tmp[MAX_COMPUTERNAME_LENGTH+1];
	DWORD Size = sizeof(Tmp);

	if (GetComputerName(Tmp,&Size))
	{
		CName.assign(Tmp);
		return true;
	}
	return false;
}
//--------------------------------------------------------------------
bool RemoteCompInfo_t::GetOwnerName(string &UName)
{

	char Tmp[MAX_COMPUTERNAME_LENGTH+1];
	DWORD Size = sizeof(Tmp);

	
	if (GetUserName(Tmp,&Size))
	{
		UName.assign(Tmp);
		return true;
	}
	return false;
}
//--------------------------------------------------------------------
bool RemoteCompInfo_t::GetWinVer(string &WinVer)
{
	DWORD dwVersion,dwBuild,dwWindowsMajorVersion,dwWindowsMinorVersion;
	dwVersion = GetVersion();
	
	// Get the Windows version. - Low Order bits are the platform
	
	dwWindowsMajorVersion =  (DWORD)(LOBYTE(LOWORD(dwVersion)));
	dwWindowsMinorVersion =  (DWORD)(HIBYTE(LOWORD(dwVersion)));
	
	// Get the build number. - High order 
	if (dwVersion < 0x80000000)              
		dwBuild = (DWORD)(HIWORD(dwVersion));
	else                                     // Windows Me/98/95
		dwBuild =  0;

	
	
	if (dwWindowsMajorVersion == 6 && dwWindowsMinorVersion == 0)
		WinVer="Windows Vista";
	if (dwWindowsMajorVersion == 5 && dwWindowsMinorVersion == 2)
		WinVer="Microsoft Windows Server 2003";
	if (dwWindowsMajorVersion == 5 && dwWindowsMinorVersion == 1)
		WinVer="Microsoft Windows XP";
	if (dwWindowsMajorVersion == 5 && dwWindowsMinorVersion == 0)
		WinVer="Microsoft Windows 2000";
	if (dwWindowsMajorVersion == 4 && dwWindowsMinorVersion == 0)
		WinVer="Microsoft Windows 95";
	if (dwWindowsMajorVersion == 4 && dwWindowsMinorVersion == 10)
		WinVer="Microsoft Windows 98";
	if (dwWindowsMajorVersion == 4 && dwWindowsMinorVersion == 90)
		WinVer="Microsoft Windows Millennium Edition";
	if (dwWindowsMajorVersion <= 4)
		WinVer="Microsoft Windows NT";

	return true;
}
//--------------------------------------------------------------------
// takes affect after restarting the computer
bool RemoteCompInfo_t::SetCompName(string &CName)
{
	if (SetComputerName(CName.c_str()))
		return true;
	return false;
}
//--------------------------------------------------------------------
bool RemoteCompInfo_t::GetSysDir(string &Sys)
{
	char syst[MAX_PATH]; //buffer to hold the system32 directory.
	
	if ( GetSystemDirectory(syst,sizeof(syst)) )
	{
		Sys.assign(syst);
		return true;
	}
	return false;
}
//--------------------------------------------------------------------
bool RemoteCompInfo_t::GetProcSpeed(string &Speed)
{
	if(RegMng->GetValData(HKEY_LOCAL_MACHINE,"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
		"~MHz",
		Speed))
		return true;
	return false;
}
//--------------------------------------------------------------------
bool RemoteCompInfo_t::GetProcType(string &Type)
{
	if(RegMng->GetValData(HKEY_LOCAL_MACHINE,"HARDWARE\\DESCRIPTION\\System",
		"SystemBiosVersion",
		Type))
		return true;
	return false;
}
//--------------------------------------------------------------------
bool RemoteCompInfo_t::GetProductID(string &PrID)
{	
	if(RegMng->GetValData(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
		"ProductId",
		PrID))
		return true;
	return false;
}
//--------------------------------------------------------------------
//returns a list of the letters assigned for the devices drives
bool RemoteCompInfo_t::GetListOfPCDevices(string &DeviceList)
{
	//max logical name devices is 26 (english alphabets) * the device name pattern
	//name pattern : "A:\\"+'\0' = 5 chars (we define 150 for convenience)
	char devices[_MAX_LEN_OF_STR_DRIVES_];
	int i=0;
	
	if (!GetLogicalDriveStrings(_MAX_LEN_OF_STR_DRIVES_,devices)) //if zero,failed
		return false;
	
	while (devices[i]!='\0')
	{
		while (devices[i]!='\0')
		{
			if (devices[i]!=':' && devices[i]!='\\')
				DeviceList+=devices[i];
			i++;
		}
		i++;
	}
	return true;
}
//--------------------------------------------------------------------
//returns the drive type 
UINT RemoteCompInfo_t::GetDriveNameType(string &strDrive)
{
	return  GetDriveType(strDrive.c_str());
/*	
0 DRIVE_UNKNOWN 	The drive type cannot be determined.
1 DRIVE_NO_ROOT_DIR 	The root path is invalid; for example, there is no volume is mounted at the path.
2 DRIVE_REMOVABLE 	The drive has removable media; for example, a floppy drive or flash card reader.
3 DRIVE_FIXED 	The drive has fixed media; for example, a hard drive, flash drive, or thumb drive.
4 DRIVE_REMOTE 	The drive is a remote (network) drive.
5 DRIVE_CDROM 	The drive is a CD-ROM drive.
6 DRIVE_RAMDISK 	The drive is a RAM disk.
*/
}
//--------------------------------------------------------------------
//returns Free space of a given drive in MB
bool RemoteCompInfo_t::GetDriveFreeSpace(string &strDrive,int &FreeMB)
{
    ULARGE_INTEGER uliFreeBytesAvailableToCaller;
    ULARGE_INTEGER uliTotalNumberOfBytes;
    ULARGE_INTEGER uliTotalNumberOfFreeBytes;
	
    if(GetDiskFreeSpaceEx(strDrive.c_str(),
		&uliFreeBytesAvailableToCaller,
		&uliTotalNumberOfBytes,
		&uliTotalNumberOfFreeBytes) == TRUE)
	{
		FreeMB = (int)(uliFreeBytesAvailableToCaller.QuadPart /(1024 *1024));
		return true;
	}
	return false;
    
}
