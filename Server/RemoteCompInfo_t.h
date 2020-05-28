// RemoteCompInfo.h: interface for the RemoteCompInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REMOTECOMPINFO_H__BDAF7EB9_C83F_4AA7_AE3C_91300E6E6174__INCLUDED_)
#define AFX_REMOTECOMPINFO_H__BDAF7EB9_C83F_4AA7_AE3C_91300E6E6174__INCLUDED_

#include "Global.h"
#include "RegistryManager_t.h"
#define _MAX_LEN_OF_STR_DRIVES_ 150
class RemoteCompInfo_t  
{
public:
	//Constructor
	RemoteCompInfo_t();
	//Destructor
	virtual ~RemoteCompInfo_t();

	//Get Remote computer name
	bool GetCompName(string &CName);

	//change the computer's name
	bool SetCompName(string &CName);
	
	//Get Remote computer user/Owner name
	bool GetOwnerName(string &UName);
	
	//Get Windows version
	bool GetWinVer(string &WinVer);
	
	//Get the windows system directory 
	bool GetSysDir(string &Sys);

	//Get Processor type
	bool GetProcType(string &Type);
	
	//Get Processor speed
	bool GetProcSpeed(string &Speed); 

	//Get Product ID
	bool GetProductID(string &PrID); 
	
	//get list of all drives
	bool GetListOfPCDevices(string &DeviceList);
	
	//get drive type - as int
	UINT GetDriveNameType(string &strDrive);
	
	//get a certain drive free space
	bool GetDriveFreeSpace(string &strDrive,int &FreeMB);

	
private:
	// no copy using copy c'tor
	RemoteCompInfo_t(const RemoteCompInfo_t&);
	// no copy using assignment operator
	void operator=(const RemoteCompInfo_t&);
	
	RegistryManager_t *RegMng;	

};

#endif // !defined(AFX_REMOTECOMPINFO_H__BDAF7EB9_C83F_4AA7_AE3C_91300E6E6174__INCLUDED_)
