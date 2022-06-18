#include "Memory.h"

bool ProtectMemWrite(HANDLE process, DWORD addr, PVOID input,int sizes)
{
	SIZE_T written;
	DWORD dwOrgProtect;
	VirtualProtect((LPVOID)addr, sizes, PAGE_READWRITE, &dwOrgProtect);
	int stat = WriteProcessMemory(process, (LPVOID)addr, (LPCVOID)input, sizes, &written);
	VirtualProtect((LPVOID)addr, sizes, dwOrgProtect, &dwOrgProtect);
	if (stat > 0)
		return true;
	else
		return false;
}
