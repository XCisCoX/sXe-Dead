#include <SDKDDKVer.h>
#include <Windows.h>
#include <WbemIdl.h>
#include <unordered_map>
#include <gl\GL.h>
#include "SDK_HOOK.h"
#include "..\sXe Dead\xorstrA.h"
#include "..\sXe Dead\xorstrW.h"
#pragma comment(lib,"SDK_HOOK.lib")
#pragma comment(lib,"opengl32.lib")
#include <ntdddisk.h>
#pragma warning(disable:4996)
#define CONST_BUFFERSIZE	16384
HMODULE hSelfish = NULL;
typedef HRESULT(__stdcall* tGetFunc)(IWbemClassObject*, LPCWSTR, LONG, VARIANT*, CIMTYPE*, long*);
HANDLE hThread = NULL;
static tGetFunc pOrgGetFunc = NULL,
pGetFunc = NULL;
static std::unordered_map<std::wstring, std::unordered_map<std::wstring, std::wstring>> sectionMap;
void Uninitialize();

HMODULE
WINAPI
_MIX_LOAD(
	_In_ LPCSTR lpLibFileName
);
FARPROC WINAPI _MIX_PROC(_In_ HMODULE hModule,_In_ LPCSTR lpProcName)
{
	HMODULE hModules = LoadLibraryA(/*Kernel32.dll*/XorStrA<0x12, 13, 0xC0F8F5B7>("\x59\x76\x66\x7B\x73\x7B\x2B\x2B\x34\x7F\x70\x71" + 0xC0F8F5B7).s);
	FARPROC fFuncProc = GetProcAddress(hModules,/*GetProcAddress*/XorStrA<0x5C,15,0xD15C3EA8>("\x1B\x38\x2A\x0F\x12\x0E\x01\x22\x00\x01\x14\x02\x1B\x1A"+0xD15C3EA8).s);
	return ((FARPROC(WINAPI *)(HMODULE,LPCSTR)) fFuncProc)(hModule,lpProcName);
}
HMODULE WINAPI _MIX_LOAD(_In_ LPCSTR lpLibFileName)
{
	HMODULE hModules = LoadLibraryA(/*Kernel32.dll*/XorStrA<0x12, 13, 0xC0F8F5B7>("\x59\x76\x66\x7B\x73\x7B\x2B\x2B\x34\x7F\x70\x71" + 0xC0F8F5B7).s);
	FARPROC fFuncProc = _MIX_PROC(hModules, /*LoadLibraryA*/XorStrA<0x25, 13, 0x8507CA69>("\x69\x49\x46\x4C\x65\x43\x49\x5E\x4C\x5C\x56\x71" + 0x8507CA69).s);
	return ((HMODULE(WINAPI *)(LPCSTR)) fFuncProc)(lpLibFileName);

}
int WINAPI _MIX_MSG(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCSTR lpText,
	_In_opt_ LPCSTR lpCaption,
	_In_ UINT uType)
{
	HMODULE hModules = LoadLibraryA(/*User32.dll*/XorStrA<0xE6, 11, 0xB0F37DD5>("\xB3\x94\x8D\x9B\xD9\xD9\xC2\x89\x82\x83" + 0xB0F37DD5).s);
	FARPROC fFuncProc = _MIX_PROC(hModules, /*MessageBoxA*/XorStrA<0x1A, 12, 0xFD7D69EA>("\x57\x7E\x6F\x6E\x7F\x78\x45\x63\x4D\x5B\x65" + 0xFD7D69EA).s);
	return ((int(WINAPI *)(HWND,LPCSTR,LPCSTR,UINT)) fFuncProc)(hWnd,lpText,lpCaption,uType);

}
BOOL WINAPI _MIX_DEBUGER()
{
	HMODULE hModules = LoadLibraryA(/*Kernel32.dll*/XorStrA<0x12, 13, 0xC0F8F5B7>("\x59\x76\x66\x7B\x73\x7B\x2B\x2B\x34\x7F\x70\x71" + 0xC0F8F5B7).s);
	FARPROC fFuncProc = GetProcAddress(hModules,/*IsDebuggerPresent*/XorStrA<0xE4, 18, 0x6A125551>("\xAD\x96\xA2\x82\x8A\x9C\x8D\x8C\x89\x9F\xBE\x9D\x95\x82\x97\x9D\x80" + 0x6A125551).s);
	return ((BOOL(WINAPI *)()) fFuncProc)();
}
HANDLE WINAPI _MIX_THREAD(
	_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
	_In_ SIZE_T dwStackSize,
	_In_ LPTHREAD_START_ROUTINE lpStartAddress,
	_In_opt_ __drv_aliasesMem LPVOID lpParameter,
	_In_ DWORD dwCreationFlags,
	_Out_opt_ LPDWORD lpThreadId
) {
	HMODULE hModule = _MIX_LOAD(/*Kernel32.dll*/XorStrA<0x12, 13, 0xC0F8F5B7>("\x59\x76\x66\x7B\x73\x7B\x2B\x2B\x34\x7F\x70\x71" + 0xC0F8F5B7).s);
	FARPROC fFuncProc = _MIX_PROC(hModule, /*CreateThread*/XorStrA<0xE3, 13, 0xB7C64D00>("\xA0\x96\x80\x87\x93\x8D\xBD\x82\x99\x89\x8C\x8A" + 0xB7C64D00).s);
	return ((HANDLE(WINAPI *)(LPSECURITY_ATTRIBUTES,SIZE_T,LPTHREAD_START_ROUTINE,LPVOID,DWORD,LPDWORD)) fFuncProc)
		(lpThreadAttributes,dwStackSize,lpStartAddress,lpParameter,dwCreationFlags,lpThreadId);
}
DWORD
WINAPI
_MIX_GET_MFN(
	_In_opt_ HMODULE hModule,
	_Out_writes_to_(nSize, ((return < nSize) ? (return +1) : nSize)) LPWSTR lpFilename,
	_In_ DWORD nSize
)
{
	HMODULE hModules = _MIX_LOAD(/*Kernel32.dll*/XorStrA<0x12, 13, 0xC0F8F5B7>("\x59\x76\x66\x7B\x73\x7B\x2B\x2B\x34\x7F\x70\x71" + 0xC0F8F5B7).s);
	FARPROC fFuncProc = _MIX_PROC(hModules, /*GetModuleFileNameW*/XorStrA<0x4B, 19, 0xE9B10F2B>("\x0C\x29\x39\x03\x20\x34\x24\x3E\x36\x12\x3C\x3A\x32\x16\x38\x37\x3E\x0B" + 0xE9B10F2B).s);
	return ((DWORD(WINAPI *)(HMODULE,LPWSTR,DWORD)) fFuncProc)(hModule,lpFilename,nSize);

}


VOID
WINAPI
_MIX_EXIT(
	_In_ UINT uExitCode
)
{
	HMODULE hModules = _MIX_LOAD(/*Kernel32.dll*/XorStrA<0x12, 13, 0xC0F8F5B7>("\x59\x76\x66\x7B\x73\x7B\x2B\x2B\x34\x7F\x70\x71" + 0xC0F8F5B7).s);
	FARPROC fFuncProc = _MIX_PROC(hModules, /*ExitProcess*/XorStrA<0xC0, 12, 0x5C6D4818>("\x85\xB9\xAB\xB7\x94\xB7\xA9\xA4\xAD\xBA\xB9" + 0x5C6D4818).s);
	return ((VOID(WINAPI *)(UINT)) fFuncProc)(uExitCode);

}
HMODULE WINAPI _MIX_MODULE(
	_In_opt_ LPCWSTR lpModuleName
) {

	HMODULE hModule = _MIX_LOAD(/*Kernel32.dll*/XorStrA<0x12, 13, 0xC0F8F5B7>("\x59\x76\x66\x7B\x73\x7B\x2B\x2B\x34\x7F\x70\x71" + 0xC0F8F5B7).s);
	FARPROC fFuncProc = _MIX_PROC(hModule, /*GetModuleHandleW*/XorStrA<0x12,17,0x45159D18>("\x55\x76\x60\x58\x79\x73\x6D\x75\x7F\x53\x7D\x73\x7A\x73\x45\x76"+0x45159D18).s);
	return ((HMODULE(WINAPI *)(LPCWSTR)) fFuncProc)(lpModuleName);
}
HWND WINAPI __MIX_WIN(
	_In_opt_ LPCWSTR lpClassName,
	_In_opt_ LPCWSTR lpWindowName)
{

	HMODULE hModule = _MIX_LOAD(/*User32.dll*/XorStrA<0xE6, 11, 0xB0F37DD5>("\xB3\x94\x8D\x9B\xD9\xD9\xC2\x89\x82\x83" + 0xB0F37DD5).s);
	FARPROC fFuncProc = _MIX_PROC(hModule,/*FindWindowW*/XorStrA<0xAF, 12, 0xA528241D>("\xE9\xD9\xDF\xD6\xE4\xDD\xDB\xD2\xD8\xCF\xEE" + 0xA528241D).s);
	return ((HWND (WINAPI *)(LPCWSTR, LPCWSTR)) fFuncProc)(lpClassName,lpWindowName);
}
void SpoofPropertyValue(IWbemClassObject* pThis, LPCWSTR wszName, VARIANTARG* pBuffer)
{
	if (pBuffer&& pBuffer->vt == VT_BSTR)
	{
		VARIANT className;
		pGetFunc(pThis, 
			/*__CLASS*/XorStrW<0x2D, 8, 0x98EDDD4B>(L"\x72\x71\x6C\x7C\x70\x61\x60" + 0x98EDDD4B).s
			, 0, &className, NULL, NULL);
		auto found = sectionMap.find(className.bstrVal);
		if (found != sectionMap.end())
		{
			auto keyFound = found->second.find(wszName);
			if (keyFound != found->second.end())
			{
				SysFreeString(pBuffer->bstrVal);
				pBuffer->bstrVal = SysAllocString(keyFound->second.c_str());
			}
		}
	}
}

HRESULT __stdcall hkGetFunc(IWbemClassObject* pThis, LPCWSTR wszName, LONG lFlags, VARIANT* pVal, CIMTYPE* pType, long* plFlavor)
{
	HRESULT hResult = pGetFunc(pThis, wszName, lFlags, pVal, pType, plFlavor);
	if (hResult >= WBEM_S_NO_ERROR)SpoofPropertyValue(pThis, wszName, pVal);
	return hResult;
}
void ProcessIniSection(wchar_t* pSectionName, wchar_t* pIniFileName)
{
	wchar_t wBuffer[CONST_BUFFERSIZE];
	int iCharsRead = 0;
	iCharsRead = GetPrivateProfileSectionW(pSectionName, wBuffer, CONST_BUFFERSIZE, pIniFileName);
	if ((0 < iCharsRead) && ((CONST_BUFFERSIZE - 2) > iCharsRead)) {
		const wchar_t* pSubstr = wBuffer;
		while (L'\0' != *pSubstr)
		{
			size_t substrLen = wcslen(pSubstr);
			const wchar_t* pPos = wcschr(pSubstr, '=');
			if (NULL != pPos)
			{
				wchar_t wName[256];
				wchar_t wValue[256];
				wcsncpy_s(wName, sizeof(wName), pSubstr, pPos - pSubstr);
				wcsncpy_s(wValue, sizeof(wValue), pPos + 1, substrLen - (pPos - pSubstr));
				auto value = sectionMap[pSectionName][wName] = wValue;
			}
			pSubstr += (substrLen + 1);
		}
	}
}
inline bool HideThread(HANDLE hThread)
{
	typedef NTSTATUS(NTAPI *pNtSetInformationThread)
		(HANDLE, UINT, PVOID, ULONG);
	NTSTATUS Status;
	pNtSetInformationThread NtSIT = (pNtSetInformationThread)
		_MIX_PROC(_MIX_MODULE(/*ntdll.dll*/XorStrW<0x3F, 10, 0xD40D640B>(L"\x51\x34\x25\x2E\x2F\x6A\x21\x2A\x2B" + 0xD40D640B).s),
			/*NtSetInformationThread*/XorStrA<0xE0, 23, 0x39A44595>("\xAE\x95\xB1\x86\x90\xAC\x88\x81\x87\x9B\x87\x8A\x98\x84\x81\x81\xA4\x99\x80\x96\x95\x91" + 0x39A44595).s);
	if (NtSIT == NULL)
		return false;
	if (hThread == NULL)
		Status = NtSIT(GetCurrentThread(),
			0x11,
			0, 0);
	else
		Status = NtSIT(hThread, 0x11, 0, 0);
	if (Status != 0x00000000)
		return false;
	else
		return true;
}
void sXeDead()
{
	wchar_t wIniFileName[MAX_PATH];
	wchar_t* pCutoff = NULL;
	while (true)
	{

		HWND hWnd = __MIX_WIN(
			/*sXe_Deadv2.0*/XorStrW<0x92, 13, 0x6A26AED3>(L"\xE1\xCB\xF1\xCA\xD2\xF2\xF9\xFD\xEC\xA9\xB2\xAD" + 0x6A26AED3).s
			,0);
		if (hWnd==NULL)
		{
			MH_Uninitialize();
			Uninitialize();
			_MIX_EXIT(0);
		}
		_MIX_GET_MFN(hSelfish, wIniFileName, MAX_PATH);
		pCutoff = wcsrchr(wIniFileName, '\\');
		*(pCutoff + 1) = '\0';
		wcscat_s(wIniFileName, 
			/*DRIVER.ini*/XorStrW<0x33, 11, 0x1A22CD3E>(L"\x77\x66\x7C\x60\x72\x6A\x17\x53\x55\x55" + 0x1A22CD3E).s
		);
		wchar_t sectionBuffer[CONST_BUFFERSIZE];
		GetPrivateProfileSectionNamesW(sectionBuffer, CONST_BUFFERSIZE, wIniFileName);
		wchar_t* pNextSection = NULL;
		pNextSection = sectionBuffer;
		ProcessIniSection(pNextSection, wIniFileName);
		while (*pNextSection != 0x00)
		{
			pNextSection = pNextSection + wcslen(pNextSection) + 1;

			if (*pNextSection != 0x00)
			{
				ProcessIniSection(pNextSection, wIniFileName);
			}

		}
		Sleep(500);
	}
}

void InitializeHwid()
{
	
	HMODULE hFastprox = NULL;
	while (!hFastprox)
	{
		hFastprox = _MIX_MODULE(
			/*fastprox.dll*/XorStrW<0x16, 13, 0x9FB0C1CA>(L"\x70\x76\x6B\x6D\x6A\x69\x73\x65\x30\x7B\x4C\x4D" + 0x9FB0C1CA).s
		);
		if (!hFastprox)
			Sleep(10);
	}
	if (hFastprox)
	{
		pOrgGetFunc = (tGetFunc)_MIX_PROC(hFastprox, 
			/*?Get@CWbemObject@@UAGJPBGJPAUtagVARIANT@@PAJ2@Z*/XorStrA<0xBF, 48, 0xFFFBCDB3>("\x80\x87\xA4\xB6\x83\x87\x92\xA4\xA2\xA5\x86\xA8\xA1\xA9\xAE\xBA\x8F\x90\x84\x93\x94\x9E\x85\x94\x90\x92\x89\x9B\x8E\xA8\xBC\xB9\x89\xA1\xB3\xAB\xA2\xAA\xB1\xA6\xA7\xB8\xA8\xA0\xD9\xAC\xB7" + 0xFFFBCDB3).s
			);

		if (pOrgGetFunc)
		{
			MH_CreateHook(pOrgGetFunc, &hkGetFunc, (LPVOID*)&pGetFunc);
			MH_EnableHook(pOrgGetFunc);
		}
	}
}

void Uninitialize()
{
	if (pOrgGetFunc&& pGetFunc)
	{
		MH_DisableHook(pOrgGetFunc);
		MH_RemoveHook(pOrgGetFunc);
	}
	CloseHandle(hThread);
	sectionMap.clear();	
	HWND hMutex = __MIX_WIN(
		/*sXe_Deadv2.0*/XorStrW<0xF5, 13, 0x667D1738>(L"\x86\xAE\x92\xA7\xBD\x9F\x9A\x98\x8B\xCC\xD1\x0" + 0x667D1738).s
		, 0);
	if (hMutex == NULL)
	{			
		TCHAR szModuleName[MAX_PATH];
		TCHAR szCmd[2 * MAX_PATH];
		STARTUPINFO si = { 0 };
		PROCESS_INFORMATION pi = { 0 };
		MH_Uninitialize();
		_MIX_EXIT(EXIT_SUCCESS);
	}	
}

DWORD WINAPI GETTING_INFORMATION_ABOUT_ANTICHEAT_OR_CS(LPVOID)
{

	MH_Initialize();
	InitializeHwid();
	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (_MIX_DEBUGER())
	{
		char*msgText = /*Debbuger Detected!*/XorStrA<0xA9, 19, 0x714A2818>("\xED\xCF\xC9\xCE\xD8\xC9\xCA\xC2\x91\xF6\xD6\xC0\xD0\xD5\xC3\xDD\xDD\x9B" + 0x714A2818).s;
		char*msgTitle = /*ERROR*/XorStrA<0xF9, 6, 0x47C64A35>("\xBC\xA8\xA9\xB3\xAF" + 0x47C64A35).s;
		UINT icons = MB_ICONERROR;		
		__asm
		{
			mov eax,msgText
			mov ebx,msgTitle
			mov ecx,icons
			push ecx
			push ebx
			push eax
			push 0
			call _MIX_MSG
			pop eax
			mov eax,0
			push eax
			call _MIX_EXIT
		}
	}
	if(_MIX_MODULE(
		/*DRIVER32.dll*/XorStrW<0x95, 13, 0x6DD5567B>(L"\xD1\xC4\xDE\xCE\xDC\xC8\xA8\xAE\xB3\xFA\xF3\xCC" + 0x6DD5567B).s
	)==hModule){ 
		if (_MIX_MODULE(
			/*hl.exe*/XorStrW<0x8C, 7, 0x12D99D83>(L"\xE4\xE1\xA0\xEA\xE8\xF4" + 0x12D99D83).s
		) || _MIX_MODULE(
			/*Injected.exe*/XorStrW<0x1B, 13, 0x5BA9CB25>(L"\x52\x72\x77\x7B\x7C\x54\x44\x46\x0D\x41\x5D\x43" + 0x5BA9CB25).s
		)) {
			if (ul_reason_for_call == DLL_PROCESS_ATTACH)
			{
				hSelfish = hModule;
				hThread = _MIX_THREAD(0, 0, (LPTHREAD_START_ROUTINE)sXeDead, 0, 0, 0);
				HideThread(hThread);
				HideThread(_MIX_THREAD(0, 0, (LPTHREAD_START_ROUTINE)GETTING_INFORMATION_ABOUT_ANTICHEAT_OR_CS, 0, 0, 0));
			}
			else if (ul_reason_for_call == DLL_PROCESS_DETACH)
			{
				Uninitialize();
			}
		}
	}
	return TRUE;
}

