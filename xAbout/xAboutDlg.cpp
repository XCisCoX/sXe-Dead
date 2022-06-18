#include "stdafx.h"
#include "xAbout.h"
#include "xAboutDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CxAboutDlg::CxAboutDlg(CWnd* pParent)
	: CDialogEx(IDD_XABOUT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CxAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CxAboutDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CxAboutDlg::OnBnClickedMfcbutton1)
END_MESSAGE_MAP()


#pragma comment (lib, "Dwmapi.lib")
#include <dwmapi.h>
#pragma comment (lib, "uxtheme.lib")
BOOL CxAboutDlg::OnInitDialog()
{
		CDialogEx::OnInitDialog();
		SetIcon(m_hIcon, TRUE);			
		SetIcon(m_hIcon, FALSE);		
		return TRUE;
	
}
HRESULT Aero(HWND hWnd, int Left, int Right, int Bottom, int Top)
{
	HRESULT hr = S_OK;
	MARGINS margins = { Left,Right,Bottom,Top };
	if (SUCCEEDED(DwmExtendFrameIntoClientArea(hWnd, &margins)))
	{
		return hr;
	}
	return hr;
}

void CxAboutDlg::OnPaint()
{
	Aero(AfxGetMainWnd()->m_hWnd,5, 5,5, 25);
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CxAboutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CxAboutDlg, CDialogEx)
	ON_EVENT(CxAboutDlg, IDC_OCX1, 5101, CxAboutDlg::PlayStateChangeOcx1, VTS_I4)
END_EVENTSINK_MAP()
void CxAboutDlg::PlayStateChangeOcx1(long NewState)
{
	if (NewState == 0)
	{
		ExitProcess(EXIT_SUCCESS);
	}
	if (NewState == 1)
	{
		ExitProcess(EXIT_SUCCESS);
	}
	if (NewState == 2)
	{
		ExitProcess(EXIT_SUCCESS);
	}
	if (NewState == 4||NewState==5)
	{
		ExitProcess(EXIT_SUCCESS);
	}
	if (NewState == 8)
	{
		ExitProcess(EXIT_SUCCESS);
	}
	if (NewState == 9)
	{
		ExitProcess(EXIT_SUCCESS);
	}
}
void CxAboutDlg::OnBnClickedButton1()
{
}
void CxAboutDlg::OnBnClickedMfcbutton1()
{
	ExitProcess(EXIT_SUCCESS);
}
