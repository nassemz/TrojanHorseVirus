// FileManager_t.h: interface for the FileManager_t class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_FILEMANAGER_T_H__D26CAF0C_B2D7_4D62_91ED_1E1B21533A4A__INCLUDED_)
#define AFX_FILEMANAGER_T_H__D26CAF0C_B2D7_4D62_91ED_1E1B21533A4A__INCLUDED_

#include "Global.h"

class FileManager_t  
{
public:
	
	FileManager_t();
	
	virtual ~FileManager_t();
	
	//delete a given file
	bool DelFile(string fullPath);
	
	//delete a given directory
	bool DelDir(const string Name);
	
	//create a directory
	bool CreateDir(string fullPath);
	
	//get file from server to the remote computer 
	bool GetFileFromServer(string IPAdr, string UserName, string PassW,
									  string FileName,
									  string NewFile,
									  DWORD FileAttrb);

	//get file from remote computer and put on the server
	bool PutFileOnServer(string IPAdr, string UserName, string PassW,
									string localFile,
									string RemoteFile);

	//list file on a certain path on remote computer
	bool GetFilesList(string PathName,list<string> &FilesList );

private:
	// no copy using assignment operator
	void operator=(const FileManager_t&);		
	
	// no copy using copy c'tor
	FileManager_t(const FileManager_t&){}
};

#endif 
