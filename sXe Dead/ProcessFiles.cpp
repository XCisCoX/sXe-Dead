#include "Includes.h"
#include "Process.h"

DWORD GetPID(wchar_t *process)
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (_wcsicmp(entry.szExeFile, process) == 0)
			{
				return(entry.th32ProcessID);
			}
		}
	}

	CloseHandle(snapshot);
}
