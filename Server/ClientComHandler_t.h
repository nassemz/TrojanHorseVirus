// ClientComHandler_t.h: interface for the ClientComHandler_t class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ClientComHandler_t_H__CC308D21_3024_4AD9_83A8_ED74B3A5377B__INCLUDED_)
#define AFX_ClientComHandler_t_H__CC308D21_3024_4AD9_83A8_ED74B3A5377B__INCLUDED_

#include "PowerManager_t.h"
#include "RegistryManager_t.h"
#include "RemoteCompInfo_t.h"
#include "PracticOperts_t.h"
#include "FileManager_t.h"
#include "ProcessManager_t.h"


class ClientComHandler_t  
{
public:
	ClientComHandler_t();
	virtual ~ClientComHandler_t();


   //Handles the commands of the Power options coming from the client
	void PowerMngHandler(Socket_t *CLS);
	//Handles the commands of the computer information coming from the client
	void PCInfoHandler(Socket_t *CLS);
	//Handles the commands of the practical operations coming from the client
	void PracticOpertHandler(Socket_t *CLS);
	//Handles the commands of the registry coming from the client
	void RegisterMngrHandler(Socket_t *CLS);
	//Handles the commands of the file manager coming from the client
	void FileMngrHandler(Socket_t *CLS,string IP,string user,string pass);
	//Handles the commands of the process manager coming from the client
	void ProcessMngrHandler(Socket_t *CLS);
private:
	// no copy using copy c'tor
	ClientComHandler_t(const ClientComHandler_t&);
	// no copy using assignment operator
	void operator=(const ClientComHandler_t&);

	PowerManager_t PowMngr;
	RegistryManager_t RegMngr;
	RemoteCompInfo_t RCI;
	PracticOperts_t PracOper;
	FileManager_t FileMngr;
	ProcessManager_t ProcMngr;

};

#endif 
