#include "TaskBarIcon.h"

void TaskbarProgress::SetProgressState(HWND hwnd, TBPFLAG flag)
{
	if (Init())
		m_pITaskBarList3->SetProgressState(hwnd, flag);
}

void TaskbarProgress::SetProgressValue(HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ullTotal)
{
	if (Init())
		m_pITaskBarList3->SetProgressValue(hwnd, ullCompleted, ullTotal);
}

bool TaskbarProgress::Init()
{
	if (m_pITaskBarList3)
		return true;
	if (m_bFailed)
		return false;
	CoInitialize(NULL);
	CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList3, (void **)&m_pITaskBarList3);
	if (m_pITaskBarList3)
		return true;
	m_bFailed = true;
	CoUninitialize();
	return false;
}
