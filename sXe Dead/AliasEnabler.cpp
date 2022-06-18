#include "AliasEnabler.h"

bool HookedsWriteProcessMemory(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer,
	SIZE_T sizes, SIZE_T*stsize)
{
	HMODULE hModule = LoadLibraryA(
		/*kernel32.dll*/XorStrA<0x28, 13, 0x5CBFDF27>("\x43\x4C\x58\x45\x49\x41\x1D\x1D\x1E\x55\x5E\x5F" + 0x5CBFDF27).s
	);
	FARPROC fFuncProc = GetProcAddress(hModule,
		/*WriteProcessMemory*/XorStrA<0x6A, 19, 0x504CF319>("\x3D\x19\x05\x19\x0B\x3F\x02\x1E\x11\x16\x07\x06\x3B\x12\x15\x16\x08\x02" + 0x504CF319).s
	);
	return ((bool (WINAPI *)(HANDLE, LPVOID, LPCVOID,
		SIZE_T, SIZE_T*)) fFuncProc)(hProcess, lpBaseAddress, lpBuffer, sizes, stsize);
}

BOOL ReCevar(DWORD Address,char*newvalue){
	DWORD pId = GetPID(
		L"hl.exe"
	);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE, pId);
	if (!hProcess)
		return false;
	DWORD flNewProtect;
	VirtualProtectEx(hProcess, &Address,sizeof(newvalue),PAGE_READWRITE,&flNewProtect);
	SIZE_T*st=NULL;
if (!WriteProcessMemory(hProcess, (LPVOID)Address, newvalue, strlen(newvalue),st))
		return false;
VirtualProtectEx(hProcess, &Address, sizeof(newvalue), PAGE_NOACCESS,&flNewProtect);

	return true;
}