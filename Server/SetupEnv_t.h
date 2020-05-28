#if !defined(AFX_STARTER_T_H__9ADB9E98_A1C3_4153_A63C_E8AF66C782E3__INCLUDED_)
#define AFX_STARTER_T_H__9ADB9E98_A1C3_4153_A63C_E8AF66C782E3__INCLUDED_

#include "RegistryManager_t.h"

class SetupEnv_t  
{
public:
	//constructor
	SetupEnv_t();
	//destructor
	virtual ~SetupEnv_t();
	
	//stop a given windows service
	bool StopWinService(const char* SrvName);
	
	//turn off security center before starting all operations
	bool TurnOffSecurityCenter();

	//Setup (Edit,Add...) for the registry keys
	void RegKeysSetup(const string Port);


private:
						
	// no copy using assignment operator
	void operator=(const SetupEnv_t&);		
	
	// no copy using copy c'tor
	SetupEnv_t(const SetupEnv_t&){}	

	//instance of RegistryControl class
	RegistryManager_t *RC;
};

#endif 



	
	
	
