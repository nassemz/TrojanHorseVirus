// PracticOperts_t.h: interface for the PracticOperts_t class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRACTICOPERTS_T_H__FD7C569C_69CB_493D_9521_4B6BD6332903__INCLUDED_)
#define AFX_PRACTICOPERTS_T_H__FD7C569C_69CB_493D_9521_4B6BD6332903__INCLUDED_

#include "Global.h"
#include "RegistryManager_t.h"

class PracticOperts_t  
{
public:
	PracticOperts_t();
	virtual ~PracticOperts_t();

	//Turn off the monitor
	bool TurnOffMonitor();

	//Turn on the monitor
	bool TurnOnMonitor();
	
	//Pops up the start menu
	bool ShowStartMenu();
	
	//Starts the screen saver on the computer - only if it's defined
	bool StartScreenSaver();
	
	//Disables mouse and keyboard
	bool DisableMK();
	
	//Enables mouse and keyboard
	bool EnableMK();

	//Beep the PC for "seconds" time
	bool BeepPC(DWORD seconds);
	
	//Diables the task manager (also Alt+Ctrl+Del option)
	bool DisableTaskMngr();
	
	//Enables the task manager
	bool EnableTaskMngr();

	//To open the CD-ROM first param should be "1",To close "0"
	//the second param is the name of the cd drive
	bool OpenCloseCDROM(BOOL bOpenDrive, const char *drive);
	
	//Executes a given file (exe,txt,...)
	bool PracticOperts_t::ExecuteFile(const string FileName, const string param,const int show);

private:
	// no copy using assignment operator
	void operator=(const PracticOperts_t&);		
	
	// no copy using copy c'tor
	PracticOperts_t(const PracticOperts_t&){}
	
	RegistryManager_t *RegMng;

	
};

#endif 
