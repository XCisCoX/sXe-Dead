#include "VersionFinder.h"
#include "ProcessFiles.h"
DWORD dwGetModuleBaseAddress(DWORD dwProcID, TCHAR *szModuleName)
{
	DWORD dwModuleBaseAddress = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID);
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ModuleEntry32;
		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapshot, &ModuleEntry32))
		{
			do
			{
				if (_tcsicmp(ModuleEntry32.szModule, szModuleName) == 0)
				{
					dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnapshot, &ModuleEntry32));
		}
		CloseHandle(hSnapshot);
	}
	return dwModuleBaseAddress;
}

int CheckVersion(HANDLE hProcess)
{
	char Is3266Opengl[] = "";
	char Is3266SoftWare[] = "";
	char Is4554Opengl[] = "";
	char Is4554SoftWare[] = "";
	DWORD ModuleBaseAddress3266OG;
	DWORD OrginaleAddress3266OG;
	DWORD ModuleBaseAddress3266SW;
	DWORD OrginaleAddress3266SW;
	DWORD ModuleBaseAddress4554OG;
	DWORD OrginaleAddress4554OG;
	DWORD ModuleBaseAddress4554SW;
	DWORD OrginaleAddress4554SW;
	ModuleBaseAddress3266OG = dwGetModuleBaseAddress(GetPID(L"hl.exe"), _T("hl.exe"));
	OrginaleAddress3266OG = (ModuleBaseAddress3266OG + 0x973E17);
	ReadProcessMemory(hProcess, (LPCVOID)OrginaleAddress3266OG, &Is3266Opengl, sizeof Is3266Opengl, NULL);//Is 3266

	if (Is3266Opengl[0] == 'M')
	{
		CSVER = IS3266OPENGL;
		LogAdd(L" Opengl [3266] DETECTED!");
		return IS3266OPENGL;
	}
	ModuleBaseAddress3266SW = dwGetModuleBaseAddress(GetPID(L"hl.exe"), _T("hl.exe"));
	OrginaleAddress3266SW = (ModuleBaseAddress3266SW + 0x95BFC9);
	ReadProcessMemory(hProcess, (LPCVOID)OrginaleAddress3266SW, &Is3266SoftWare, sizeof Is3266SoftWare, NULL);//Is 3266
	if (Is3266SoftWare[0] == 'M')
	{
		CSVER = IS3266SOFTWARE;
		LogAdd(L" SoftWare [3266] DETECTED!");
		return IS3266SOFTWARE;
	}
	ModuleBaseAddress4554SW = dwGetModuleBaseAddress(GetPID(L"hl.exe"), _T("sw.dll"));
	OrginaleAddress4554SW = (ModuleBaseAddress4554SW + 0x65E59);
	ReadProcessMemory(hProcess, (LPCVOID)OrginaleAddress4554SW, &Is4554SoftWare, sizeof Is4554SoftWare, NULL);//Is 3266
	if (Is4554SoftWare[0] == 'M')
	{
		CSVER = IS4554SOFTWARE;
		LogAdd(L" SoftWare [4554] DETECTED!");
		return IS4554SOFTWARE;
	}
	ModuleBaseAddress4554OG = dwGetModuleBaseAddress(GetPID(L"hl.exe"), _T("hw.dll"));
	OrginaleAddress4554OG = (ModuleBaseAddress4554OG + 0x7ECC7);
	ReadProcessMemory(hProcess, (LPCVOID)OrginaleAddress4554OG, &Is4554Opengl, sizeof Is4554Opengl, NULL);//Is 3266
	if (Is4554Opengl[0] == 'M')
	{
		CSVER = IS4554OPENGL;
		LogAdd(L" Opengl [4554] DETECTED!");
		return IS4554OPENGL;
	}
	return 0;
}
bool IsMatchMemory(HANDLE hProcess, DWORD Address, char*Your)
{
	char org[] = "";
	ReadProcessMemory(hProcess, (LPCVOID)Address, &org, sizeof org, NULL);
	if (strcmp(org, Your) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}