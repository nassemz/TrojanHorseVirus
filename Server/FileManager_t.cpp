// FileManager_t.cpp: implementation of the FileManager_t class.
//
/////////////////////////////////////////////////////////////////////

#include "FileManager_t.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FileManager_t::FileManager_t()
{

}

FileManager_t::~FileManager_t()
{

}
//-----------------------------------------------------------------
bool FileManager_t::DelFile(string fullPath)
{
	if(DeleteFile(fullPath.c_str()))
		return true;
	return false;
}
//-----------------------------------------------------------------
bool FileManager_t::DelDir(const string Name)
{
	string tmpStr = "";
	struct _finddata_t tmpFile;
	long RetValFrom;
	char fullPath[_MAX_PATH];
	
	strcpy(fullPath,Name.c_str());
	_chdir(Name.c_str());
	RetValFrom = _findfirst( "*.*", &tmpFile );
	
	while( _findnext(RetValFrom, &tmpFile ) == 0 )
	{
		//if the object is a sub directory.
		if( tmpFile.attrib & _A_SUBDIR )
		{
			if ((strcmp(tmpFile.name,".")==0) || (strcmp(tmpFile.name,"..")==0));
			else					
			{
				_chdir(fullPath);
				tmpStr.assign(fullPath);
				tmpStr+= "\\";	
				tmpStr+= tmpFile.name;	
				DelDir(tmpStr);
			}
		}
		//the object is a file
		else					
		{
			tmpStr.assign(fullPath);
			tmpStr+= "\\";
			tmpStr+= tmpFile.name;	
			DeleteFile(tmpStr.c_str());	
		}
		tmpStr = "";
	}
	_findclose( RetValFrom );
	_chdir("..\\");
	if(rmdir(Name.c_str())==0)
		return true;
	
	return false;
	
}
//-----------------------------------------------------------------
bool FileManager_t::CreateDir(string fullPath)
{
	
	if(!mkdir(fullPath.c_str()))
		return true;
	return false;
}
//-----------------------------------------------------------------
bool FileManager_t::GetFileFromServer(string IPAdr, string UserName, string PassW,
									  string FileName,
									  string NewFile,
									  DWORD FileAttrb)
{
	HINTERNET HOpen;
	HINTERNET HConnect;
	/*
	//if((HOpen = InternetOpen("",INTERNET_OPEN_TYPE_PROXY,"ftp","<local>",0) )== NULL)
	if((HOpen = InternetOpen("",PRE_CONFIG_INTERNET_ACCESS,NULL,INTERNET_INVALID_PORT_NUMBER,0))== NULL)
		return false;	
//	if ((HConnect = InternetConnect(HOpen,IPAdr.c_str(),INTERNET_DEFAULT_FTP_PORT,UserName.c_str(),PassW.c_str(),INTERNET_SERVICE_FTP,INTERNET_FLAG_PASSIVE,0)) == NULL)
	if ((HConnect = InternetConnect(HOpen,IPAdr.c_str(),INTERNET_INVALID_PORT_NUMBER,UserName.c_str(),PassW.c_str(),INTERNET_SERVICE_FTP,0,0)) == NULL)	
		return false;
	if(FtpGetFile(HConnect,FileName.c_str(),NewFile.c_str(),FALSE,FileAttrb,FTP_TRANSFER_TYPE_BINARY,0) == FALSE)
		return false;*/
		if((HOpen = InternetOpen("",INTERNET_OPEN_TYPE_PROXY,"ftp","<local>",0))== NULL)
		return false;
	if ((HConnect = InternetConnect(HOpen,IPAdr.c_str(),INTERNET_DEFAULT_FTP_PORT,UserName.c_str(),PassW.c_str(),INTERNET_SERVICE_FTP,INTERNET_FLAG_PASSIVE,0)) == NULL)
		return false;
	if(FtpGetFile(HConnect,FileName.c_str(),NewFile.c_str(),FALSE,FileAttrb,FTP_TRANSFER_TYPE_BINARY,0) == FALSE)
		return false;
	
	//FILE_ATTRIBUTE_NORMAL
	//FILE_ATTRIBUTE_HIDDEN
	InternetCloseHandle(HOpen);
	InternetCloseHandle(HConnect);
	return true;
}
//-----------------------------------------------------------------
bool FileManager_t::PutFileOnServer(string IPAdr, string UserName, string PassW,
									string localFile,
									string RemoteFile)
{
	HINTERNET HOpen;
	HINTERNET HConnect;
	
	if((HOpen = InternetOpen("",INTERNET_OPEN_TYPE_PROXY,"ftp","<local>",0))== NULL)
		return false;
	if ((HConnect = InternetConnect(HOpen,IPAdr.c_str(),INTERNET_DEFAULT_FTP_PORT,UserName.c_str(),PassW.c_str(),INTERNET_SERVICE_FTP,INTERNET_FLAG_PASSIVE,0)) == NULL)
		return false;
	if(FtpPutFile(HConnect,localFile.c_str(),RemoteFile.c_str(),FTP_TRANSFER_TYPE_BINARY,0) == FALSE)
		return false;

	InternetCloseHandle(HOpen);
	InternetCloseHandle(HConnect);
	return true;
}
//-----------------------------------------------------------------
bool FileManager_t::GetFilesList(string PathName,list<string> &FilesList )
{
	WIN32_FIND_DATA Fdata;
	HANDLE  Hfile;
	DWORD dwerror;
	list<string>::iterator iter;

	Hfile = FindFirstFile(PathName.c_str(),&Fdata);
	if (Hfile == INVALID_HANDLE_VALUE)
		return false;

	
	while (FindNextFile(Hfile,&Fdata) != 0)
		FilesList.push_back(Fdata.cFileName);
	
	dwerror = GetLastError();
	if (dwerror != ERROR_NO_MORE_FILES)
		return false;
	FindClose(Hfile);
	
	return true;	
}