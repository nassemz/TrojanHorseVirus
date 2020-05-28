// ProcessManager_t.cpp: implementation of the ProcessManager_t class.
//
//////////////////////////////////////////////////////////////////////

#include "ProcessManager_t.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ProcessManager_t::ProcessManager_t()
{

}
//--------------------------------------------------------------------
ProcessManager_t::~ProcessManager_t()
{

}
//--------------------------------------------------------------------
bool ProcessManager_t::ListProcesses(list<Pros> &PsList)
{
	
	list<Pros>::iterator iter;
	Pros insP;
	char tmp[32];
   
	// Get the list of process identifiers.
    DWORD aProcesses[1024], cbNeeded, cProcesses;
	ULONG lCpuusage = 0;
    UINT index;
   
	if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
        return false;

	// Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);
	if(cProcesses > 100)
		return false;
		
		
	for ( iter=PsList.begin(),index = 0; index < cProcesses; index++, iter++ )
	{
		
		itoa(aProcesses[index],tmp,10);
		insP.PID.assign(tmp);
		GetProsName(aProcesses[index],insP.name);
		PsList.push_back(insP);
		 
	}

	return true;
}
//--------------------------------------------------------------------
bool ProcessManager_t::GetProsName( DWORD processID, string &name )
{
    char szProcessName[MAX_PATH] = "unknown";

   //PID = 0 is always system idle process
	if (processID == 0)
	{
		name.assign("System Idle Process");
		return true;
	}
	//PID = 4 is system process for XP and newer versions 
	//PID = 8 is system process for win versions older than xp
	if (processID == 4 || processID == 8)
	{
		name.assign("System");
		return true;
	}
	
	// Get a handle to the process.
	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );


    // Get the process name.
    if ( hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
             &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName, 
                               sizeof(szProcessName) );
			name.assign(szProcessName);
			CloseHandle( hProcess );
			return true;
        }
    }

    CloseHandle( hProcess );
	return false;
}
//--------------------------------------------------------------------
bool ProcessManager_t::KillProcess(DWORD processID)
{
	DWORD exitCode;
	// Get a handle to the process.
	HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS,FALSE, processID );//PROCESS_TERMINATE
	if ( hProcess )
    {
		GetExitCodeProcess(hProcess,&exitCode);
		if (exitCode == STILL_ACTIVE)
		{	//process still active , force it to termination
			if(TerminateProcess(hProcess,0))
			{
				CloseHandle( hProcess );
				return true;
			}
		}
		else
			if(TerminateProcess(hProcess,exitCode))
			{
				CloseHandle( hProcess );
				return true;
			}
	}
	DWORD g=GetLastError();
	CloseHandle( hProcess );
	return false;
}