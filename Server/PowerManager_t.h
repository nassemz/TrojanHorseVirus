// PowerManager.h: interface for the PowerManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POWERMANAGER_H__339378D2_318D_4393_8CC9_8DEBA17E3C7F__INCLUDED_)
#define AFX_POWERMANAGER_H__339378D2_318D_4393_8CC9_8DEBA17E3C7F__INCLUDED_

#include "Global.h"

class PowerManager_t  
{
public:
	//constructor
	PowerManager_t();
	
	//Destructor
	virtual ~PowerManager_t();
	
	//Logs off windows - (current user)
	bool LogOffWin();
	
	//Shuts down the computer - power off
	bool ShutDownPC();

	//Reboot/Restart the computer
	bool RebootPC();

private:
	// no copy using assignment operator
	void operator=(const PowerManager_t&);		
	
	// no copy using copy c'tor
	PowerManager_t(const PowerManager_t&){}

	BOOL SetPrivilege (HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);
};

#endif 
