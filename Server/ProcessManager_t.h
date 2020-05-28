// ProcessManager_t.h: interface for the ProcessManager_t class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROCESSMANAGER_T_H__E09B4D16_F610_459C_A3CC_D8EC6AD4E4E9__INCLUDED_)
#define AFX_PROCESSMANAGER_T_H__E09B4D16_F610_459C_A3CC_D8EC6AD4E4E9__INCLUDED_

#include "Global.h"


class ProcessManager_t  
{
public:
	ProcessManager_t();
	virtual ~ProcessManager_t();
	
	//List processes on computer.
	bool ListProcesses(list<Pros> &PsList);
	
	//Get Process name by a given PID
	bool GetProsName( DWORD processID, string &name );

	//Kill a given process.
	bool KillProcess(DWORD processID);

private:
	// no copy using assignment operator
	void operator=(const ProcessManager_t&);		
	
	// no copy using copy c'tor
	ProcessManager_t(const ProcessManager_t&){}

};

#endif 
