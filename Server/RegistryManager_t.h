// RegistryManager_t.h: interface for the RegistryControl_t class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGISTRYCONTROL_T_H__1F6FFB45_DC11_44DE_B47E_BF1E04EC4487__INCLUDED_)
#define AFX_REGISTRYCONTROL_T_H__1F6FFB45_DC11_44DE_B47E_BF1E04EC4487__INCLUDED_

#include "Global.h"

class RegistryManager_t  
{

public:
	//Constructor
	RegistryManager_t();
	//Destructor
	virtual ~RegistryManager_t();
	
	//Add/Edit a value to an existing registry key
	bool AddValueToRegKey(HKEY,string KeyPath,DWORD ,string RegDesc,string RegData);
	
	//Add Key
	bool AddKey(HKEY hKey,string NewKeyName);
	
	//Delete key
	bool DeleteKey(HKEY hKey,string KeyName);
	
	//View all values to a given Key
	bool ViewValsOfKey(HKEY hKey, string KeyPath,list<string> &ValList);
	
	//View all subkeys of a given Key
	bool ViewSubKeys(HKEY hKey, string KeyPath,list<string> &SubKList);
	
	//Search the registry for a given key
	int SearchReg(HKEY hKey, string KeyName, string KeyPath,string fullPath,list <string> &PList);
	
	//Get Data of a given Value of a Reg Key 
	bool GetValData(HKEY hKey, 
								string KeyPath,
								string KeyValue,
								string &VData);
private:
	// no copy using assignment operator
	void operator=(const RegistryManager_t&);		
	
	// no copy using copy c'tor
	RegistryManager_t(const RegistryManager_t&){}	
	
	
};

#endif 
