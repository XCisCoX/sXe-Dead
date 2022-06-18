#pragma once
#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif
#include "resource.h"		
class CxAboutApp : public CWinApp
{
public:
	CxAboutApp();
public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};
extern CxAboutApp theApp;
