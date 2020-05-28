// ClientComHandler_t.cpp: implementation of the ClientComHandler_t class.
//
//////////////////////////////////////////////////////////////////////

#include "ClientComHandler_t.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ClientComHandler_t::ClientComHandler_t()
{
	
}
//----------------------------------------------------------------
ClientComHandler_t::~ClientComHandler_t()
{
	
}
//----------------------------------------------------------------
void ClientComHandler_t::PowerMngHandler(Socket_t *CLS)
{
	string buff;
	
	while(1)
	{
		(*CLS)>>buff;
		sendAck(CLS);
		
		
		if (buff == "LOGOFF_")
		{
			getAck(CLS);
			if(PowMngr.LogOffWin())
				(*CLS)<<"SUCCESS_";
			else
				(*CLS)<<"FAIL_";
			getAck(CLS);
		}
		
		if (buff == "REBOOT_")
		{
			getAck(CLS);
			if(PowMngr.RebootPC())
				(*CLS)<<"SUCCESS_";
			else
				(*CLS)<<"FAIL_";
			getAck(CLS);
		}
		
		if (buff == "SHUTDOWN_")
		{
			getAck(CLS);
			if(PowMngr.ShutDownPC())
				(*CLS)<<"SUCCESS_";
			else
				(*CLS)<<"FAIL_";
			getAck(CLS);
		}
		if (buff == "BACK_TO_MAIN_")
			return;
	}
	
}
//----------------------------------------------------------------
void ClientComHandler_t::PCInfoHandler(Socket_t *CLS)
{
	string buff,tmpInfo;
	char* chBuff = new char;
	int i=0;
	CompInfo CInfo;
	
	while(1)
	{
		(*CLS)>>buff;
		sendAck(CLS);
		
		if (buff == "COMP_INFO_")
		{
			getAck(CLS);
			if(RCI.GetOwnerName(CInfo.OwnerName) && RCI.GetCompName(CInfo.CompName)
				&& RCI.GetProcSpeed(CInfo.ProcessorSpeed) 
				&& RCI.GetProcType(CInfo.ProcessorType)
				&& RCI.GetProductID(CInfo.WinID)
				&& RCI.GetSysDir(CInfo.SystemDir)
				&& RCI.GetWinVer(CInfo.WinVersion))
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
				(*CLS)<<CInfo.CompName;
				getAck(CLS);
				(*CLS)<<CInfo.OwnerName;
				getAck(CLS);
				(*CLS)<<CInfo.ProcessorSpeed;
				getAck(CLS);
				(*CLS)<<CInfo.ProcessorType;
				getAck(CLS);
				(*CLS)<<CInfo.SystemDir;
				getAck(CLS);
				(*CLS)<<CInfo.WinID;
				getAck(CLS);
				(*CLS)<<CInfo.WinVersion;
				getAck(CLS);	
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
			
		}
		
		if (buff == "FREE_DISK_SPACE_")
		{
			int space;
			//get drive name
			(*CLS)>>buff;
			sendAck(CLS);
			getAck(CLS);
			if(RCI.GetDriveFreeSpace(buff,space))
			{
				itoa(space,chBuff,10);
				tmpInfo = chBuff;
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
				(*CLS)<<tmpInfo;
				getAck(CLS);
				tmpInfo.erase(0,tmpInfo.length());
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		
		if (buff == "DEVICE_LIST_")
		{
			getAck(CLS);
			if(RCI.GetListOfPCDevices(tmpInfo))
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
				(*CLS)<<tmpInfo;
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
			
			int space;
			int DriveLen = tmpInfo.length();
			while (DriveLen!=i)
			{//get drive type
				sendAck(CLS);
				(*CLS)>>buff;
				sendAck(CLS);
				getAck(CLS);
				if(space = RCI.GetDriveNameType(buff))
				{
					itoa(space,chBuff,10);
					tmpInfo = chBuff;
					(*CLS)<<"SUCCESS_";
					getAck(CLS);
					(*CLS)<<tmpInfo;
					getAck(CLS);
					tmpInfo.erase(0,tmpInfo.length());
				}
				else
				{
					(*CLS)<<"FAIL_";
					getAck(CLS);
				}
				i++;
			}
			i=0;
		}
		if (buff == "BACK_TO_MAIN_")
			return;
}
delete chBuff;		
}
//----------------------------------------------------------------
void ClientComHandler_t::PracticOpertHandler(Socket_t *CLS)
{
	string buff,buff2,tmpInfo,WinAtt;
	char* chBuff = new char;
	int i=0,att;
	
	
	
	while (1)
	{
		(*CLS)>>buff;
		sendAck(CLS);
		
		if (buff == "TURN_ON_MON_")
		{
			getAck(CLS);
			if(PracOper.TurnOnMonitor())
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		
		if (buff == "TURN_OFF_MON_")
		{
			getAck(CLS);
			if(PracOper.TurnOffMonitor())
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		
		if (buff == "SHOW_START_MENU_")
		{
			getAck(CLS);
			if(PracOper.ShowStartMenu())
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		if (buff == "START_SCREEN_SAVER_")
		{
			getAck(CLS);
			if(PracOper.StartScreenSaver())
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		if (buff == "ENABLE_MK_")
		{
			getAck(CLS);
			if(PracOper.EnableMK())
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		
		if (buff == "DISABLE_MK_")
		{
			getAck(CLS);
			if(PracOper.DisableMK())
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		if (buff == "BEEP_PC_")
		{
			//get number of seconds
			(*CLS)>>buff;
			sendAck(CLS);
			getAck(CLS);
			
			if(PracOper.BeepPC(atoi(buff.c_str())))
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		if (buff == "ENABLE_TASK_MNGR_")
		{
			getAck(CLS);
			if(PracOper.EnableTaskMngr())
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		if (buff == "DISABLE_TASK_MNGR_")
		{
			getAck(CLS);
			if(PracOper.DisableTaskMngr())
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		
		if (buff == "OPEN_CD_ROM_")
		{
			//get the CD-ROM Drive
			(*CLS)>>buff;
			sendAck(CLS);
			getAck(CLS);
			
			if(PracOper.OpenCloseCDROM(true,buff.c_str()))
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		if (buff == "CLOSE_CD_ROM_")
		{
			//get the CD-ROM Drive
			(*CLS)>>buff;
			sendAck(CLS);
			getAck(CLS);
			
			if(PracOper.OpenCloseCDROM(false,buff.c_str()))
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		if (buff == "EXECUTE_FILE_")
		{
			//get file name
			(*CLS)>>buff;
			sendAck(CLS);
			getAck(CLS);
			
			// get params of the file (if no params then "")
			(*CLS)>>buff2;
			sendAck(CLS);
			getAck(CLS);
			
			if(buff2 == "_NON_")
				buff2="";
			// get window attribute (hide , show)
			(*CLS)>>WinAtt;
			sendAck(CLS);
			getAck(CLS);
			
			if (WinAtt == "0")
				att = 0;
			if (WinAtt == "1")
				att = 1;
			if(PracOper.ExecuteFile(buff,buff2,att))
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		if (buff == "BACK_TO_MAIN_")
			return;
		}
		delete chBuff;		
}
//-------------------------------------------------------------
void ClientComHandler_t::RegisterMngrHandler(Socket_t *CLS)
{
	string buff,path,desc,data,tmpStr,KeyVal,Data;
	int hkey,regtype,i=0;
	int res;
	list<string> tmpList;
	list<string>::iterator iter;
	char tmp[512];
	
	while (1)
	{
		(*CLS)>>buff;
		sendAck(CLS);
		//-----------------------ADD KEY-----------------------------		
		if (buff == "ADD_KEY_")
		{
			//get hkey 
			(*CLS)>>buff;
			sendAck(CLS);
			hkey = StringToInt(buff);
			//get key fullpath 
			(*CLS)>>buff;
			sendAck(CLS);
			getAck(CLS);
			
			switch(hkey){
			case(1):
				res = RegMngr.AddKey(HKEY_CLASSES_ROOT,buff);
				break;
			case(2):
				res = RegMngr.AddKey(HKEY_CURRENT_USER,buff);
				break;
			case(3):
				res = RegMngr.AddKey(HKEY_LOCAL_MACHINE,buff);
				break;
			case(4):
				res = RegMngr.AddKey(HKEY_USERS,buff);
				break;
			case(5):
				res = RegMngr.AddKey(HKEY_CURRENT_CONFIG,buff);
				break;
			default:
				res=0;
				break;
			}
			if(res)
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		//-----------------------DELETE KEY-----------------------------
		if (buff == "DEL_KEY_")
		{
			//get hkey 
			(*CLS)>>buff;
			sendAck(CLS);
			hkey = StringToInt(buff);
			//get key fullpath 
			(*CLS)>>buff;
			sendAck(CLS);
			getAck(CLS);
			
			switch(hkey){
			case(1):
				res = RegMngr.DeleteKey(HKEY_CLASSES_ROOT,buff);
				break;
			case(2):
				res = RegMngr.DeleteKey(HKEY_CURRENT_USER,buff);
				break;
			case(3):
				res = RegMngr.DeleteKey(HKEY_LOCAL_MACHINE,buff);
				break;
			case(4):
				res = RegMngr.DeleteKey(HKEY_USERS,buff);
				break;
			case(5):
				res = RegMngr.DeleteKey(HKEY_CURRENT_CONFIG,buff);
				break;
			default:
				res=0;
				break;
			}
			if(res)
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		//-----------------------ADD VALUE TO KEY-----------------------------
		if (buff == "ADD_VALUE_TO_KEY_")
		{
			//get hkey 
			(*CLS)>>buff;
			sendAck(CLS);
			hkey = StringToInt(buff);
			//get key fullpath 
			(*CLS)>>path;
			sendAck(CLS);
			//get reg type 
			(*CLS)>>buff;
			sendAck(CLS);
			regtype = StringToInt(buff);
			//get key description
			(*CLS)>>desc;
			sendAck(CLS);
			//get key data
			(*CLS)>>data;
			sendAck(CLS);
			
			getAck(CLS);
			switch(hkey){
			case(1):
				if(regtype ==1)
					res = RegMngr.AddValueToRegKey(HKEY_CLASSES_ROOT,path,REG_SZ,desc,data);
				if(regtype ==2)
					res = RegMngr.AddValueToRegKey(HKEY_CLASSES_ROOT,path,REG_DWORD,desc,data);
				if(regtype ==3)
					res = RegMngr.AddValueToRegKey(HKEY_CLASSES_ROOT,path,REG_BINARY,desc,data);
				break;
			case(2):
				if(regtype ==1)
					res = RegMngr.AddValueToRegKey(HKEY_CURRENT_USER,path,REG_SZ,desc,data);
				if(regtype ==2)
					res = RegMngr.AddValueToRegKey(HKEY_CURRENT_USER,path,REG_DWORD,desc,data);
				if(regtype ==3)
					res = RegMngr.AddValueToRegKey(HKEY_CURRENT_USER,path,REG_BINARY,desc,data);
				break;
			case(3):
				if(regtype ==1)
					res = RegMngr.AddValueToRegKey(HKEY_LOCAL_MACHINE,path,REG_SZ,desc,data);
				if(regtype ==2)
					res = RegMngr.AddValueToRegKey(HKEY_LOCAL_MACHINE,path,REG_DWORD,desc,data);
				if(regtype ==3)
					res = RegMngr.AddValueToRegKey(HKEY_LOCAL_MACHINE,path,REG_BINARY,desc,data);
				break;
			case(4):
				if(regtype ==1)
					res = RegMngr.AddValueToRegKey(HKEY_USERS,path,REG_SZ,desc,data);
				if(regtype ==2)
					res = RegMngr.AddValueToRegKey(HKEY_USERS,path,REG_DWORD,desc,data);
				if(regtype ==3)
					res = RegMngr.AddValueToRegKey(HKEY_USERS,path,REG_BINARY,desc,data);
				break;
			case(5):
				if(regtype ==1)
					res = RegMngr.AddValueToRegKey(HKEY_CURRENT_CONFIG,path,REG_SZ,desc,data);
				if(regtype ==2)
					res = RegMngr.AddValueToRegKey(HKEY_CURRENT_CONFIG,path,REG_DWORD,desc,data);
				if(regtype ==3)
					res = RegMngr.AddValueToRegKey(HKEY_CURRENT_CONFIG,path,REG_BINARY,desc,data);
				break;
			default:
				res=0;
				break;
			}
			if(res)
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		//-----------------------View Vals of KEY-----------------------------
		if (buff == "VIEW_VALUE_OF_KEY_")
		{
			//get hkey 
			(*CLS)>>buff;
			sendAck(CLS);
			hkey = StringToInt(buff);
			//get key fullpath 
			(*CLS)>>buff;
			sendAck(CLS);
			getAck(CLS);
			
			
			switch(hkey){
			case(1):
				res = RegMngr.ViewValsOfKey(HKEY_CLASSES_ROOT,buff,tmpList);
				break;
			case(2):
				res = RegMngr.ViewValsOfKey(HKEY_CURRENT_USER,buff,tmpList);
				break;
			case(3):
				res = RegMngr.ViewValsOfKey(HKEY_LOCAL_MACHINE,buff,tmpList);
				break;
			case(4):
				res = RegMngr.ViewValsOfKey(HKEY_USERS,buff,tmpList);
				break;
			case(5):
				res = RegMngr.ViewValsOfKey(HKEY_CURRENT_CONFIG,buff,tmpList);
				break;
			default:
				res=0;
				break;
			}
			
			if(res)
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
				
				itoa(tmpList.size(),tmp,10);
				buff.assign(tmp);
				(*CLS)<<tmp; //send list size
				getAck(CLS);
				
				for( iter=tmpList.begin(); i<tmpList.size(); iter++)	
				{
					i++;
					(*CLS)<<(*iter);
					(*CLS)<<"\n";
					getAck(CLS);
				}
				tmpList.clear();
				i=0;
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
			
		}
		//-----------------------View Subkeys of KEY-----------------------------
		if (buff == "VIEW_SUBKKEYS_")
		{
			//get hkey 
			(*CLS)>>buff;
			sendAck(CLS);
			hkey = StringToInt(buff);
			//get key fullpath 
			(*CLS)>>buff;
			sendAck(CLS);
			getAck(CLS);
			
			
			switch(hkey){
			case(1):
				res = RegMngr.ViewSubKeys(HKEY_CLASSES_ROOT,buff,tmpList);
				break;
			case(2):
				res = RegMngr.ViewSubKeys(HKEY_CURRENT_USER,buff,tmpList);
				break;
			case(3):
				res = RegMngr.ViewSubKeys(HKEY_LOCAL_MACHINE,buff,tmpList);
				break;
			case(4):
				res = RegMngr.ViewSubKeys(HKEY_USERS,buff,tmpList);
				break;
			case(5):
				res = RegMngr.ViewSubKeys(HKEY_CURRENT_CONFIG,buff,tmpList);
				break;
			default:
				res=0;
				break;
			}
			
			if(res)
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
				
				itoa(tmpList.size(),tmp,10);
				buff.assign(tmp);
				(*CLS)<<tmp; //send list size
				getAck(CLS);
				
				for( iter=tmpList.begin(); i<tmpList.size(); iter++)	
				{
					i++;
					(*CLS)<<(*iter);
					(*CLS)<<"\n";
					getAck(CLS);
				}
				tmpList.clear();
				i=0;
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
			tmpList.clear();
		}
		//-----------------------Get Value data-----------------------------
		if (buff == "GET_VALUE_DATA_")
		{
			//get hkey 
			(*CLS)>>buff;
			sendAck(CLS);
			hkey = StringToInt(buff);
			//get key fullpath 
			(*CLS)>>buff;
			sendAck(CLS);
			//get key value 
			(*CLS)>>KeyVal;
			sendAck(CLS);
			getAck(CLS);
			
			
			switch(hkey){
			case(1):
				res = RegMngr.GetValData(HKEY_CLASSES_ROOT,buff,KeyVal,Data);
				break;
			case(2):
				res = RegMngr.GetValData(HKEY_CLASSES_ROOT,buff,KeyVal,Data);
				break;
			case(3):
				res = RegMngr.GetValData(HKEY_CLASSES_ROOT,buff,KeyVal,Data);
				break;
			case(4):
				res = RegMngr.GetValData(HKEY_CLASSES_ROOT,buff,KeyVal,Data);
				break;
			case(5):
				res = RegMngr.GetValData(HKEY_CLASSES_ROOT,buff,KeyVal,Data);
				break;
			default:
				res=0;
				break;
			}
			
			if(res)
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
				
				(*CLS)<<Data; //send value data
				getAck(CLS);
				
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		//-----------------------Search for a key in the registery-----------------------------
		if (buff == "SEARCH_KEY_")
		{
			//get hkey 
			(*CLS)>>buff;
			sendAck(CLS);
			hkey = StringToInt(buff);
			//get key name 
			(*CLS)>>buff;
			sendAck(CLS);
			getAck(CLS);
			
			
			switch(hkey){
			case(1):
				res = RegMngr.SearchReg(HKEY_CLASSES_ROOT,buff,"",tmpStr,tmpList);
				break;
			case(2):
				res = RegMngr.SearchReg(HKEY_CURRENT_USER,buff,"",tmpStr,tmpList);
				break;
			case(3):
				res = RegMngr.SearchReg(HKEY_LOCAL_MACHINE,buff,"",tmpStr,tmpList);
				break;
			case(4):
				res = RegMngr.SearchReg(HKEY_USERS,buff,"",tmpStr,tmpList);
				break;
			case(5):
				res = RegMngr.SearchReg(HKEY_CURRENT_CONFIG,buff,"",tmpStr,tmpList);
				break;
			default:
				res=0;
				break;
			}
			
			if(res)
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
				
				itoa(tmpList.size(),tmp,10);
				buff.assign(tmp);
				(*CLS)<<tmp; //send list size
				getAck(CLS);
				
				for( iter=tmpList.begin(); i<tmpList.size(); iter++)	
				{
					i++;
					(*CLS)<<(*iter);
					(*CLS)<<"\n";
					getAck(CLS);
				}
				tmpList.clear();
				i=0;
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
			
		}
		if (buff == "BACK_TO_MAIN_")
			return;
	}
}
//-------------------------------------------------------------
void ClientComHandler_t::FileMngrHandler(Socket_t *CLS,string IP,string user,string pass)
{
	string buff,attrb,localf,remotef,ipadd;
	DWORD att;
	list<string> FList;
	list<string>::iterator iter;
	char tmp[512];
	int i=0;
	
	while (1)
	{
		(*CLS)>>buff;
		sendAck(CLS);
		//-----------------------Delete File-----------------------------		
		if (buff == "DEL_FILE_")
		{
			//get path
			(*CLS)>>buff;
			sendAck(CLS);
			getAck(CLS);
			
			if(FileMngr.DelFile(buff))
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
				
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		//-----------------------Delete Directory-----------------------------		
		if (buff == "DEL_DIR_")
		{
			//get path
			(*CLS)>>buff;
			sendAck(CLS);
			getAck(CLS);
			
			if(FileMngr.DelDir(buff))
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
				
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		//-----------------------Create Directory-----------------------------		
		if (buff == "NEW_DIR_")
		{
			//get path
			(*CLS)>>buff;
			sendAck(CLS);
			getAck(CLS);
			
			if(FileMngr.CreateDir(buff))
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
				
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		//-----------------------Get File From Server-----------------------------		
		if (buff == "DOWNLOAD_FILE_")
		{
			//get file name
			(*CLS)>>buff;
			sendAck(CLS);
			//get new file name
			(*CLS)>>remotef;
			sendAck(CLS);
			//buff = "Simple.txt";
			//remotef = "Simple.txt";
			
			//get file attribute
			(*CLS)>>attrb;
			sendAck(CLS);
			if (attrb == "1")
				att = FILE_ATTRIBUTE_NORMAL;
			if (attrb == "2")
				att = FILE_ATTRIBUTE_HIDDEN;
			
			
			(*CLS)>>ipadd;
			sendAck(CLS);
			
			getAck(CLS);
			
			
			
			if(FileMngr.GetFileFromServer(ipadd,user,pass,buff,remotef,att))
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
				
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		//-----------------------Put File On server-----------------------------		
		if (buff == "UPLOAD_FILE_")
		{
			//get Local File name on computer 
			(*CLS)>>localf;
			sendAck(CLS);
			//get remote File name to server
			(*CLS)>>remotef;
			sendAck(CLS);
			
			(*CLS)>>ipadd;
			sendAck(CLS);
			
			getAck(CLS);
			
			if(FileMngr.PutFileOnServer(ipadd,user,pass,localf,remotef))
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
				
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		//-----------------------List Files-----------------------------		
		if (buff == "LIST_FILES_")
		{
			//get path
			(*CLS)>>buff;
			sendAck(CLS);
			getAck(CLS);
			
			
			if(FileMngr.GetFilesList(buff,FList))
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
				
				itoa(FList.size(),tmp,10);
				buff.assign(tmp);
				(*CLS)<<tmp; //send list size
				getAck(CLS);
				
				for( iter=FList.begin(); i<FList.size(); iter++)	
				{
					i++;
					(*CLS)<<(*iter);
					(*CLS)<<"\n";
					getAck(CLS);
				}
				FList.clear();
				i=0;
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		if (buff == "BACK_TO_MAIN_")
			return;
	}
}
//-------------------------------------------------------------
void ClientComHandler_t::ProcessMngrHandler(Socket_t *CLS)
{
	string buff;
	
	list <Pros> ProcList;
	list <Pros>::iterator iter;
	char tmp[512];
	Pros Pr;
	int i=0;
	
	while (1)
	{
		(*CLS)>>buff;
		sendAck(CLS);
		
		//-----------------------kill process-----------------------------		
		if (buff == "KILL_PROCESS_")
		{
			//get PID
			(*CLS)>>buff;
			sendAck(CLS);
			getAck(CLS);
			
			
			if(ProcMngr.KillProcess(atoi(buff.c_str())))
			{
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
				
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		//-----------------------List processes-----------------------------		
		if (buff == "ENUM_PROCESSES_")
		{
			if(ProcMngr.ListProcesses(ProcList))
			{
				getAck(CLS);
				(*CLS)<<"SUCCESS_";
				getAck(CLS);
				
				itoa(ProcList.size(),tmp,10);
				buff.assign(tmp);
				(*CLS)<<tmp; //send list size
				getAck(CLS);
				
				for( iter=ProcList.begin(); i<ProcList.size(); iter++)	
				{
					i++;
					(*CLS)<<(*iter).name;
					(*CLS)<<"\n";
					getAck(CLS);
					(*CLS)<<(*iter).PID;
					(*CLS)<<"\n";
					getAck(CLS);
				}
				ProcList.clear();
				i=0;
			}
			else
			{
				(*CLS)<<"FAIL_";
				getAck(CLS);
			}
		}
		if (buff == "BACK_TO_MAIN_")
			return;
		
	}
}