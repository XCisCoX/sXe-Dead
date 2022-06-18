#include "stdafx.h"
#include "xAbout.h"
#include "xAboutDlg.h"
#include "..\sXe Dead\xorstrA.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
BEGIN_MESSAGE_MAP(CxAboutApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()
CxAboutApp::CxAboutApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}
CxAboutApp theApp;
BOOL CxAboutApp::InitInstance()
{
	const char* pszCmdline = (const char*)GetCommandLineA();
	if (!OpenMutexA(MUTEX_ALL_ACCESS, FALSE,
		/*CISCO_DRIVER*/XorStrA<0x19, 13, 0xFAD7C7AA>("\x5A\x53\x48\x5F\x52\x41\x5B\x72\x68\x74\x66\x76" + 0xFAD7C7AA).s
	))
	{
		char* pPath = new char[MAX_PATH];
		GetModuleFileNameA(0, pPath, MAX_PATH);
		pPath[strrchr(pPath, '\\') - pPath + 1] = 0;
		strcat(pPath,
			/*sXe Dead.exe*/XorStrA<0xE7, 13, 0xD2C73ADB>("\x94\xB0\x8C\xCA\xAF\x89\x8C\x8A\xC1\x95\x89\x97" + 0xD2C73ADB).s
		);
		ShellExecuteA(0,
			/*runas*/XorStrA<0xB9, 6, 0xD371BD88>("\xCB\xCF\xD5\xDD\xCE" + 0xD371BD88).s
			, pPath, 0, 0, SW_SHOW);
		ExitProcess(0);
	}
	if (strcmp(pszCmdline, 
		/*-Video*/XorStrA<0xC0, 7, 0x93115D13>("\xED\x97\xAB\xA7\xA1\xAA" + 0x93115D13).s
		)) {
		char* pPath = new char[MAX_PATH];
		GetModuleFileNameA(0, pPath, MAX_PATH);
		pPath[strrchr(pPath, '\\') - pPath + 1] = 0;
		strcat(pPath, 
			/*sXe Dead.exe*/XorStrA<0xE7, 13, 0xD2C73ADB>("\x94\xB0\x8C\xCA\xAF\x89\x8C\x8A\xC1\x95\x89\x97" + 0xD2C73ADB).s
			);
		ShellExecuteA(0,
			/*runas*/XorStrA<0xB9, 6, 0xD371BD88>("\xCB\xCF\xD5\xDD\xCE" + 0xD371BD88).s
			, pPath, 0, 0, SW_SHOW);
		ExitProcess(0);
	}
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	CShellManager *pShellManager = new CShellManager;
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CxAboutDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}
	else if (nResponse == -1)
	{
	}
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif
	return FALSE;
}

