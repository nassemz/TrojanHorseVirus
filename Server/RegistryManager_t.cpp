// RegistryManager_t.cpp: implementation of the RegistryManager_t class.
//
//////////////////////////////////////////////////////////////////////
 
#include "RegistryManager_t.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RegistryManager_t::RegistryManager_t()
{}

RegistryManager_t::~RegistryManager_t()
{}
//====================== ADD KEY =====================================
//Ex : AddKey(HKEY_CURRENT_USER,"AppEvents\\TEST")
bool RegistryManager_t::AddKey(HKEY hKey,string NewKeyName)
{
	if(RegCreateKeyEx(hKey,NewKeyName.c_str(),0,NULL,REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		NULL,
		&hKey,
		NULL))
		return false;
	
	if (RegCloseKey(hKey))
		return false;
	
	return true;
}
//====================== ADD VALUE TO KEY =============================
bool RegistryManager_t::AddValueToRegKey(HKEY hKey,string KeyPath,DWORD RegType,string RegDesc,string RegData)
{
	DWORD dwSize = _MAX_PATH;
	DWORD dw =0;
	int intTmp;
	
	//This opens the key we want to write to
	if (RegOpenKeyEx(hKey,KeyPath.c_str(),0,KEY_ALL_ACCESS,&hKey))
		return false;
		
	//This sets our value
	//According to the reg key type
	if (RegType == REG_DWORD)
	{
		intTmp = StringToInt(RegData);
		dw = (DWORD) intTmp;
		dwSize = sizeof(dw);
		
		if(RegSetValueEx(hKey,RegDesc.c_str(),0,RegType,(LPBYTE)&dw,dwSize))
			return false;
	}
	//if RegType == REG_SZ or REG_BINARY
	//if we pass the value Data for a binary key as a string it will autmatically be translated
	//to a binary number in the value Data 
	else 

	if(RegSetValueEx(hKey,RegDesc.c_str(),0,RegType,(const unsigned char*)RegData.c_str(),RegData.size()))
			return false;
		
	// This closes the key
	if(RegCloseKey(hKey))
		return false;
	
	return true;
}
//====================== DELETE KEY =====================================
bool RegistryManager_t::DeleteKey(HKEY hKey,string KeyName)
{
	if(RegDeleteKey(hKey,KeyName.c_str()))
		return false;

	return true;
}

//====================== VIEW VALUES OF KEY ==============================
bool RegistryManager_t::ViewValsOfKey(HKEY hKey, string KeyPath,list<string> &ValList)
									  
{
    
	DWORD    cValues=0;  // number of values for key 
	DWORD i, retCode; 
	TCHAR  achValue[MAX_VALUE_NAME]; 
    DWORD cchValue = MAX_VALUE_NAME; 
	
	if (RegOpenKeyEx(hKey,KeyPath.c_str(),0,KEY_ALL_ACCESS,&hKey))
		return false;
	
	// Get the class name and the value count. 
    retCode = RegQueryInfoKey(
        hKey,                    // key handle 
        NULL,                // buffer for class name 
        NULL,           // size of class string 
        NULL,                    // reserved 
        NULL,               // number of subkeys 
        NULL,            // longest subkey size 
        NULL,            // longest class string 
        &cValues,                // number of values for this key 
        NULL,            // longest value name 
        NULL,         // longest value data 
        NULL,   // security descriptor 
        NULL);       // last write time 
	
	// Enumerate the key values. 
	
    if (cValues) 
    {
        
        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) 
        { 
            cchValue = MAX_VALUE_NAME; 
            achValue[0] = '\0'; 
            retCode = RegEnumValue(hKey, i, 
                achValue, 
                &cchValue, 
                NULL, 
                NULL,
                NULL,
                NULL);
			
            if (retCode == ERROR_SUCCESS ) 
            { 
                ValList.push_back(achValue);
            } 
        }
    }
	
	return true;
}
//====================== VIEW NAMES OF SUBKEYS ==============================
bool RegistryManager_t::ViewSubKeys(HKEY hKey, string KeyPath,list<string> &SubKList)
{
    
	DWORD    cSubKeys=0;               // number of subkeys 
	DWORD i, retCode; 
	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
	
	if (RegOpenKeyEx(hKey,KeyPath.c_str(),0,KEY_ALL_ACCESS,&hKey))
		return false;
	
	// Get the class name and the value count. 
    retCode = RegQueryInfoKey(
        hKey,            // key handle 
        NULL,            // buffer for class name 
        NULL,            // size of class string 
        NULL,            // reserved 
        &cSubKeys,       // number of subkeys 
        NULL,            // longest subkey size 
        NULL,            // longest class string 
        NULL,            // number of values for this key 
        NULL,            // longest value name 
        NULL,            // longest value data 
        NULL,            // security descriptor 
        NULL);           // last write time 
	
	// Enumerate the subkeys, until RegEnumKeyEx fails.
    
    if (cSubKeys)
    {
        for (i=0; i<cSubKeys; i++) 
        { 
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
                     achKey, 
                     &cbName, 
                     NULL, 
                     NULL, 
                     NULL, 
                     NULL); 
            if (retCode == ERROR_SUCCESS) 
            {
				SubKList.push_back(achKey);	
            }
        }
    } 
 
	
	return true;
}
//=================== SEARCH THE REGISTRY FOR A GIVEN KEY ======================
int RegistryManager_t::SearchReg(HKEY hKey, 
										   string KeyName, 
										   string KeyPath,
										   string fullPath,
										   list <string> &PList)
{
	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys=0;               // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
    FILETIME ftLastWriteTime;      // last write time 
    DWORD i, retCode; 
	string tmp;
    DWORD cchValue = MAX_VALUE_NAME; 
	
    
	if (RegOpenKeyEx(hKey,KeyPath.c_str(),0,KEY_ALL_ACCESS,&hKey))
		return false;
	
	// Get the class name and the value count. 
    if (RegQueryInfoKey(
        hKey,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime) != ERROR_SUCCESS)       // last write time 
		return false;
	
    // Enumerate the subkeys, until RegEnumKeyEx fails.
	if (cSubKeys)
    {
		for (i=0; i<cSubKeys; i++) 
        { 
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
				achKey, 
				&cbName, 
				NULL, 
				NULL, 
				NULL, 
				&ftLastWriteTime); 
			tmp = achKey;
            if (retCode == ERROR_SUCCESS) 
            {
				fullPath=fullPath +"\\"+ achKey;
				
				if (KeyName == achKey)
				{
					PList.push_back(fullPath);
					return PList.size();
				}
				else	
					SearchReg(hKey,KeyName,achKey,fullPath,PList);	
					
            }
		fullPath.erase((fullPath.length()-tmp.length()-1),tmp.length()+1);	
        }
		
    } 
	
	return PList.size();
}
//=================== GET THE DATA FOR A GIVEN REG KEY VALUE (string) ======================
bool RegistryManager_t::GetValData(HKEY hKey, 
								string KeyPath,
								string KeyValue,
								string &VData)
{	
	char str[_MAX_PATH];
	DWORD strSize = sizeof(str);
	DWORD dwSize = _MAX_PATH;
	DWORD dw =0 ;
	DWORD RegType;
//	int intTmp;

	
	if (RegOpenKeyEx(hKey,KeyPath.c_str(),0,KEY_QUERY_VALUE,&hKey))
		return false;
	
	//According to the reg key type
	if(RegQueryValueEx(hKey,KeyValue.c_str(),NULL,&RegType,NULL,NULL))
		return false;
	
	if (RegType == REG_DWORD)
	{
		if(RegQueryValueEx(hKey,KeyValue.c_str(),NULL,&RegType,(LPBYTE) &dw,&dwSize))
			return false;
		else
		{
			VData.assign(itoa(dw,str,10));
			return true;
		}
	}
	if (RegType == REG_BINARY)
	{
		if(RegQueryValueEx(hKey,KeyValue.c_str(),NULL,&RegType,(LPBYTE) &dw,&dwSize))
			return false;
		else
		{
			VData.assign(itoa(dw,str,16));
			return true;
		}
	}
	//if RegType == REG_SZ or other
	else 

	if(RegQueryValueEx(hKey,KeyValue.c_str(),NULL,&RegType,(unsigned char *)str,&strSize))
			return false;
	
	if (RegCloseKey(hKey))
		return false;

	VData.assign(str);
	return true;
}