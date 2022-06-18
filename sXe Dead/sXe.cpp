
#include "sXe.h"
#pragma warning (disable:4996)
#include <WbemIdl.h>
#include <unordered_map>
#include <TlHelp32.h>
#include <iostream>
#include <windows.h>
#include <time.h>
#include <string>   
#include <ctime>
#include <sys/stat.h>
#include <shlwapi.h>
#include <stdio.h>
#include "VM.h"
#include "vmLog.h"
#include "VersionFinder.h"
#include "resource.h"
#include "Memory.h"
#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "Shlwapi.lib")
DWORD GetModuleBase(HANDLE hSnapshot, TCHAR *szModuleName)
{
	DWORD dwModuleBaseAddress = 0;
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

bool memSender(HANDLE hProcess,DWORD Address,LPCVOID NewVal,SIZE_T sizes)
{
	
	return WriteProcessMemory(hProcess, (LPVOID)Address,
		NewVal, sizes, 0);

}
static const char charecs[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuv";

static int stringLength = sizeof(charecs) - 1;

static char GenRandom() {

	return charecs[rand() % stringLength];
}
bool  MemHacking(HANDLE hProcess)
{
	bool result = TRUE;
#define MemSender(x,y,z) ProtectMemWrite(hProcess,x,(PVOID)y,z)
	if (!MemSender(0x004BCBD4,
		(/*Telegram ID*/XorStrA<0x33, 12, 0x0303E404>("\x67\x51\x59\x53\x50\x4A\x58\x57\x1B\x75\x79" + 0x0303E404).s)
		, 13))
	{
	
		result = false;
	}
	if(!MemSender( 0x004B00B0,
		(/*http://cisco.spirit-team.ir/cisco/Img.php*/XorStrW<0x5B, 42, 0x5D861A28>(L"\x33\x28\x29\x2E\x65\x4F\x4E\x01\x0A\x17\x06\x09\x49\x1B\x19\x03\x19\x05\x19\x43\x1B\x15\x10\x1F\x5D\x1D\x07\x59\x14\x11\x0A\x19\x14\x53\x34\x13\x18\xAE\xF1\xEA\xF3" + 0x5D861A28).s)
		, 397))
	{

		result = false;
	}
	if(!MemSender( 0x004BC9CC,
		(/*CODER:-==(CISCO_X)==--*/XorStrA<0x7F, 23, 0xE13E7003>("\x3C\xCF\xC5\xC7\xD1\xBE\xA8\xBB\xBA\xA0\xCA\xC3\xD8\xCF\xC2\xD1\xD7\xB9\xAC\xAF\xBE\xB9" + 0xE13E7003).s)
		, 29))
	{
		result = false;
	}
	if(!MemSender( 0x004BCAD0,
		(/*https://t.me/CISCO_X */ XorStrA<0xDF, 21, 0x27B28C94>("\xB7\x94\x95\x92\x90\xDE\xCA\xC9\x93\xC6\x84\x8F\xC4\xAF\xA4\xBD\xAC\xBF\xAE\xAA" + 0x27B28C94).s)
		,29))
	{
		result = false;
	}
	if(!MemSender( 0x005F7274,
		(/*This Anti Cheat Has Been Hacked With\nsXe Dead v2.0 (BY CISCO_X) !*/XorStrW<0x3E, 66, 0x93D36AF3>(L"\x6A\x57\x29\x32\x62\x02\x2A\x31\x2F\x67\x0B\x21\x2F\x2A\x38\x6D\x06\x2E\x23\x71\x10\x36\x31\x3B\x76\x1F\x39\x3A\x31\x3E\x38\x7D\x09\x36\x14\x09\x68\x10\x3C\x00\x46\x23\x0D\x08\x0E\x4B\x1A\x5F\x40\x5F\x50\x59\x30\x2A\x54\x36\x3F\x24\x3B\x36\x25\x23\x55\x5D\x5F" + 0x93D36AF3).s)
		, 140))
	{
		result = false;
	}
	if(!MemSender(0x004BCCE8, "", 27))
	{
		result = false;
	}
	char buff[255];
	srand(time(0));
	string random1;
	for (unsigned int i = 0; i < 5; ++i)
	{
		random1 += GenRandom();
	}
	sprintf(buff, 
		/*Hacked By CISCO_X %s*/XorStrA<0xD9, 21, 0xDB91EE95>("\x91\xBB\xB8\xB7\xB8\xBA\xFF\xA2\x98\xC2\xA0\xAD\xB6\xA5\xA8\xB7\xB1\xCA\xCE\x9F" + 0xDB91EE95).s
		,random1.c_str());
	if (!MemSender(0x0052B620, buff, 28))
	{
		result = false;
	}
	return result;
}


	HKEY OpenKey(HKEY hRootKey, wchar_t* strKey)
	{
		HKEY hKey;
		LONG nError = RegOpenKeyEx(hRootKey, strKey, 512, KEY_ALL_ACCESS, &hKey);

		if (nError == ERROR_FILE_NOT_FOUND)
		{
			nError = RegCreateKeyEx(hRootKey, strKey, NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
		}

		if (nError)
			LogAdd(L"ERROR:Acess Denied!");

		return hKey;
	}
	bool SetValString(HKEY hKey, LPCTSTR lpValue, std::wstring data);
	bool UnistallDriver()
	{
		HKEY rgApp =
			OpenKey(HKEY_LOCAL_MACHINE,
				/*SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Windows*/XorStrW<0x86, 53, 0x67E9DAE3>(L"\xD5\xC8\xCE\xDD\xDD\xCA\xDE\xC8\xD2\xC2\xF9\xF2\xE0\xFC\xE7\xFA\xF0\xE3\xC4\xCE\xF3\xF5\xF8\xF2\xE9\xEC\x80\xEF\xF6\xFF\xE7\xD0\xD4\xD5\xCD\xC7\xDE\xFD\xC9\xDF\xDD\xC6\xDF\xDF\xEE\xE4\xDD\xDB\xD2\xD8\xCF\xCA" + 0x67E9DAE3).s
			);
		if (!rgApp) {
			return false;
		}
		SetValString(
			rgApp,
			/*AppInit_DLLs*/XorStrW<0xC9, 13, 0xA860FB3F>(L"\x88\xBA\xBB\x85\xA3\xA7\xBB\x8F\x95\x9E\x9F\xA7" + 0xA860FB3F).s,
			L""
		);
		return true;
	}

	bool SetValString(HKEY hKey, LPCTSTR lpValue, std::wstring data)
	{
		LONG nError = RegSetValueEx(hKey, lpValue,NULL, REG_SZ, (BYTE *)data.c_str(), (data.size() + 1) * sizeof(wchar_t));
		if (nError)
			return false;
		else
			return true;
	}
	bool SetValDword(HKEY hKey, LPCTSTR lpValue, DWORD data)
	{
		LONG nError = RegSetValueEx(hKey, lpValue, NULL, REG_DWORD, (LPBYTE)&data, sizeof(DWORD));
		if (nError)
			return false; else
			return true;
	}
	wstring GetValString(HKEY hKey, LPCTSTR lpValue)
	{
		wstring data; DWORD size = sizeof(data);	DWORD type = REG_SZ;
		LONG nError = RegQueryValueEx(hKey, lpValue, NULL, &type, (LPBYTE)&data, &size);

		if (nError == ERROR_FILE_NOT_FOUND)
			data	 =	L"NOT_FOUND";
		else if (nError)
			data	=	L"UNK_ERROR";

		return data;
	}
	bool dirExists(const std::wstring& dirName_in)
	{
		DWORD ftyp = GetFileAttributesW(dirName_in.c_str());
		if (ftyp == INVALID_FILE_ATTRIBUTES)
			return false; 

		if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
			return true;   

		return false;   
	}


    bool SpoofingDriverHWID(char*sXe1, char*sXe2, char*sXe3)
	{
		wchar_t wIniFileName[MAX_PATH];
		wsprintfW(wIniFileName,L"%s",
			/*C:\\CDRIVER\\DRIVER.ini*/XorStrW<0x49, 22, 0x10AFA2D7>(L"\x0A\x70\x17\x0F\x09\x1C\x06\x06\x14\x00\x0F\x10\x07\x1F\x01\x1D\x0B\x74\x32\x32\x34" + 0x10AFA2D7).s
		);
	try{	
		ofstream file;
		SetFileAttributes(
			/*C:\\CDRIVER\\DRIVER.ini*/XorStrW<0x49, 22, 0x10AFA2D7>(L"\x0A\x70\x17\x0F\x09\x1C\x06\x06\x14\x00\x0F\x10\x07\x1F\x01\x1D\x0B\x74\x32\x32\x34" + 0x10AFA2D7).s
			, FILE_ATTRIBUTE_NORMAL);
		file.open(wIniFileName);
		if (!file.is_open())
			return false;
		file << "[Win32_Processor]\rProcessorId = " << sXe1 <<endl<<

			"[Win32_DiskDrive]\rSerialNumber = " << sXe2 <<endl<<

			"[Win32_BaseBoard]\rSerialNumber = " << sXe3<<endl;

		file.close();
		SetFileAttributes(
			/*C:\\CDRIVER\\DRIVER.ini*/XorStrW<0x49, 22, 0x10AFA2D7>(L"\x0A\x70\x17\x0F\x09\x1C\x06\x06\x14\x00\x0F\x10\x07\x1F\x01\x1D\x0B\x74\x32\x32\x34" + 0x10AFA2D7).s
			, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
	}
	catch (const std::exception& ex)
	{
		MessageBoxA(0, ex.what(), "ERROR", MB_ICONERROR);
	}
		return true;
	}
	void Extract(LPCWSTR lpszOutputPath,int i)
	{
		HRSRC hrsrc = FindResource(NULL, MAKEINTRESOURCE(i), MAKEINTRESOURCE(RT_RCDATA));
		HGLOBAL hLoaded = LoadResource(NULL, hrsrc);
		LPVOID lpLock = LockResource(hLoaded);
		DWORD dwSize = SizeofResource(NULL, hrsrc);
		HANDLE hFile = CreateFile(lpszOutputPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD dwByteWritten;
		WriteFile(hFile, lpLock, dwSize, &dwByteWritten, NULL);
		CloseHandle(hFile);
		FreeResource(hLoaded);
	}
#include "Includes.h"

	bool InestallDriver()
	{
	
		bool IsOk = TRUE;	
	
		if (CreateDirectory(
			/*C:\\CDRIVER*/XorStrW<0xC2, 11, 0x13A11DBB>(L"\x81\xF9\x98\x86\x82\x95\x81\x9F\x8F\x99" + 0x13A11DBB).s
			, NULL) ||
			ERROR_ALREADY_EXISTS == GetLastError())
		{
			SetFileAttributes(
				/*C:\\CDRIVER*/XorStrW<0xC2, 11, 0x13A11DBB>(L"\x81\xF9\x98\x86\x82\x95\x81\x9F\x8F\x99" + 0x13A11DBB).s
				, FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM);
		
			DeleteFile(
				/*C:\\CDRIVER\\DRIVER32.dll*/XorStrW<0x6E, 24, 0x2AA5E866>(L"\x2D\x55\x2C\x32\x36\x21\x3D\x23\x33\x25\x24\x3D\x28\x32\x2A\x38\x2C\x4C\xB2\xAF\xE6\xEF\xE8" + 0x2AA5E866).s
			);
			Extract(
				/*C:\\CDRIVER\\DRIVER32.dll*/XorStrW<0x6E, 24, 0x2AA5E866>(L"\x2D\x55\x2C\x32\x36\x21\x3D\x23\x33\x25\x24\x3D\x28\x32\x2A\x38\x2C\x4C\xB2\xAF\xE6\xEF\xE8" + 0x2AA5E866).s
				, IDR_RCDATA1);
			SetFileAttributes(
				/*C:\\CDRIVER\\DRIVER32.dll*/XorStrW<0x6E, 24, 0x2AA5E866>(L"\x2D\x55\x2C\x32\x36\x21\x3D\x23\x33\x25\x24\x3D\x28\x32\x2A\x38\x2C\x4C\xB2\xAF\xE6\xEF\xE8" + 0x2AA5E866).s
				, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_READONLY);
		}
		else
		{
	
		}
		
		Sleep(300);
		
		Sleep(500);
		HKEY rgApp =
			OpenKey(HKEY_LOCAL_MACHINE,
				/*SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Windows*/XorStrW<0x34, 53, 0x95B179E3>(L"\x67\x7A\x70\x63\x6F\x78\x68\x7E\x60\x70\x57\x5C\x32\x2E\x31\x2C\x22\x31\x1A\x10\x21\x27\x2E\x24\x3B\x3E\x6E\x01\x04\x0D\x11\x26\x26\x27\x33\x39\x2C\x0F\x3F\x29\x2F\x34\x31\x31\x3C\x36\x0B\x0D\x00\x0A\x11\x14" + 0x95B179E3).s
				);

		if (rgApp == NULL)
			IsOk = FALSE;
	
		if (!SetValString(
			rgApp,
			/*AppInit_DLLs*/XorStrW<0xAE, 13, 0x44449A14>(L"\xEF\xDF\xC0\xF8\xDC\xDA\xC0\xEA\xF2\xFB\xF4\xCA" + 0x44449A14).s,
			/*C:\\CDRIVER\\DRIVER32.dll*/XorStrW<0x6E, 24, 0x2AA5E866>(L"\x2D\x55\x2C\x32\x36\x21\x3D\x23\x33\x25\x24\x3D\x28\x32\x2A\x38\x2C\x4C\xB2\xAF\xE6\xEF\xE8" + 0x2AA5E866).s
		))
			IsOk = FALSE;


		if (!SetValDword(
			rgApp,
			/*LoadAppInit_DLLs*/XorStrW<0x3D, 17, 0x06FC0099>(L"\x71\x51\x5E\x24\x00\x32\x33\x0D\x2B\x2F\x33\x17\x0D\x06\x07\x3F" + 0x06FC0099).s,
			1))
			IsOk = FALSE;
		if (!SetValDword(
			rgApp,
			/*RequireSignedAppInit_DLLs*/XorStrW<0x20, 26, 0x5FC24AAC>(L"\x72\x44\x53\x56\x4D\x57\x43\x74\x41\x4E\x44\x4E\x48\x6C\x5E\x5F\x79\x5F\x5B\x47\x6B\x71\x7A\x7B\x4B" + 0x5FC24AAC).s,
			0))
			IsOk = FALSE;

		RegCloseKey(rgApp);
		return IsOk;
	}

 