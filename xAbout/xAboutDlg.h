#pragma once
class CxAboutDlg : public CDialogEx
{
public:
	CxAboutDlg(CWnd* pParent = nullptr);
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_XABOUT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void PlayStateChangeOcx1(long NewState);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedMfcbutton1();
};
