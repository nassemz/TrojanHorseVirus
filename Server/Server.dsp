# Microsoft Developer Studio Project File - Name="Server" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Server - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Server.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Server.mak" CFG="Server - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Server - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Server - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Server - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40d /d "NDEBUG"
# ADD RSC /l 0x40d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Server - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40d /d "_DEBUG"
# ADD RSC /l 0x40d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib Winmm.lib Wininet.lib Psapi.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Server - Win32 Release"
# Name "Server - Win32 Debug"
# Begin Group "Trojan Server - Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ClientComHandler_t.h
# End Source File
# Begin Source File

SOURCE=.\ClientMailSocket_t.h
# End Source File
# Begin Source File

SOURCE=.\FileManager_t.h
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# Begin Source File

SOURCE=.\PowerManager_t.h
# End Source File
# Begin Source File

SOURCE=.\PracticOperts_t.h
# End Source File
# Begin Source File

SOURCE=.\ProcessManager_t.h
# End Source File
# Begin Source File

SOURCE=.\RegistryManager_t.h
# End Source File
# Begin Source File

SOURCE=.\RemoteCompInfo_t.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\ServerFunctions.h
# End Source File
# Begin Source File

SOURCE=.\ServerSocket_t.h
# End Source File
# Begin Source File

SOURCE=.\SetupEnv_t.h
# End Source File
# Begin Source File

SOURCE=.\Socket_SMTP.h
# End Source File
# Begin Source File

SOURCE=.\Socket_t.h
# End Source File
# Begin Source File

SOURCE=.\SocketException_t.h
# End Source File
# End Group
# Begin Group "Trojan Server - Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ClientComHandler_t.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientMailSocket_t.cpp
# End Source File
# Begin Source File

SOURCE=.\FileManager_t.cpp
# End Source File
# Begin Source File

SOURCE=.\Global.cpp
# End Source File
# Begin Source File

SOURCE=.\PowerManager_t.cpp
# End Source File
# Begin Source File

SOURCE=.\PracticOperts_t.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcessManager_t.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistryManager_t.cpp
# End Source File
# Begin Source File

SOURCE=.\RemoteCompInfo_t.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\ServerSocket_t.cpp
# End Source File
# Begin Source File

SOURCE=.\SetupEnv_t.cpp
# End Source File
# Begin Source File

SOURCE=.\Socket_SMTP.cpp
# End Source File
# Begin Source File

SOURCE=.\Socket_t.cpp
# End Source File
# End Group
# Begin Group "Trojan Server - Main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ServerMain.cpp
# End Source File
# End Group
# Begin Group "Trojan Server - Header Main"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\configs.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Icon1.rc
# End Source File
# Begin Source File

SOURCE=.\Report.ico
# End Source File
# End Target
# End Project
