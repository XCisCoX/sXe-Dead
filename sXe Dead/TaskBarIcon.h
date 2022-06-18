#pragma once
#include "Includes.h"
class TaskbarProgress
{
public:
	void SetProgressState(HWND hwnd, TBPFLAG flag);
	void SetProgressValue(HWND hwnd, ULONGLONG ullCompleted, ULONGLONG ullTotal);
private:
	bool Init();
	ITaskbarList3* m_pITaskBarList3;
	bool m_bFailed;
};
