#include "Includes.h"
#include "Theme.h"
#include "SteamSpoofer.h"
#include "ProcessFiles.h"
#include "TaskBarIcon.h"
#include "resource.h"
#include "sXe.h"
#include "AliasEnabler.h"
#include "VersionFinder.h"
#include "AntiScreen.h"
#include "apiHooking.h"
#include "Memory.h"
#include "GUI.h"
#include "SplashWindow.h"

int lblRed = 10; int lblGreen = 10; int lblBlue = 10;
RECT rcClient;
char sxe1[255];
char sxe2[255];
char sxe3[255];
static wstring tmpoldtxt;
BOOL checkedAlias = TRUE;
BOOL checkAio = TRUE;
HANDLE hMutex = NULL;
SECURITY_ATTRIBUTES secAttrib;
bool sXeRunning = FALSE;
bool CounterIsRunnig = TRUE;
bool IsReadyWav = TRUE;
//KLS
#define M  MessageBoxW
#define SS_OFF 0
#define SS_BLACK 1
#define SS_DONT_SEND 2
#define SS_BUTTON_PRESS 3
bool GuiIsRunning = FALSE;
int ss_status = 0;
DWORD dwGetModuleBaseAddress(DWORD dwProcID, TCHAR *szModuleName);

wstring randomNum(int len);
LRESULT CALLBACK wndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

void RZFree(void*pPath)
{
	pPath = malloc(sizeof(void*));
	free(pPath);
}
#define FREE(x); RZFree(&x);
BOOL AllOneHwid = TRUE;
extern CComModule _Module;
TaskbarProgress ts;
int CurrentProgressPos = 0;
DWORD pId;
bool CheckItNow = false;
RECT customAreaRect, minRect, maxRect, closeRect, coverMenuRect;
BOOL maximized;
void WavPlayer(int resId)
{
	if (IsReadyWav == true) {
		IsReadyWav = false;
		PlaySoundA(MAKEINTRESOURCEA(resId), hInst, SND_RESOURCE | SND_MEMORY);
		IsReadyWav = true;
	}

}
void playWav(int resId)
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)WavPlayer, (LPVOID)resId, 0, 0);
}
#define PLAY_WAV(x) playWav(x);
void SetError()
{
	ts.SetProgressState(hWnd, TBPF_ERROR);
	SendMessage(prgSteam, PBM_SETSTATE, PBST_ERROR, 0);
}
void SetErr()
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetError, 0, 0, 0);
}
#define ERROR SetErr();

#if UNICODE
#define SendTextMessage SendTextMessageW
#else
#define SendTextMessage SendTextMessageA
#endif
void ExtractData(LPCWSTR lpszOutputPath, int i, LPCWSTR DataType)
{
	HRSRC hrsrc = FindResource(NULL, MAKEINTRESOURCE(i), MAKEINTRESOURCE(DataType));
	HGLOBAL hLoaded = LoadResource(NULL, hrsrc);
	LPVOID lpLock = LockResource(hLoaded);
	DWORD dwSize = SizeofResource(NULL, hrsrc);
	HANDLE hFile = CreateFile(lpszOutputPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwByteWritten;
	WriteFile(hFile, lpLock, dwSize, &dwByteWritten, NULL);
	CloseHandle(hFile);
	FreeResource(hLoaded);
}
DWORD GetProcSize(void*Function, void*stubFunction)
{
	DWORD dwFunctionSize = 0, dwOldProtect;
	DWORD*fnA = 0, *fnB = 0;
	fnA = (DWORD*)Function;
	fnB = (DWORD*)stubFunction;
	dwFunctionSize = (fnB - fnA);
	VirtualProtect(fnA, dwFunctionSize,
		PAGE_EXECUTE_READWRITE, &dwOldProtect);
	return dwFunctionSize;
}
HMODULE GetModuleHandleProcess(DWORD dwProcID, TCHAR *szModuleName)
{
	HMODULE ModuleBaseAddress = 0;
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
					ModuleBaseAddress = ModuleEntry32.hModule;
					break;
				}
			} while (Module32Next(hSnapshot, &ModuleEntry32));
		}
		CloseHandle(hSnapshot);
	}
	return ModuleBaseAddress;
}

void ChangeSteam(char*steam)
{
	unsigned char *addr = NULL;
	bool addrf = false;
	char sss[255];
	pId = GetPID(TEXT("hl.exe"));
	sprintf(sss, "%s", steam);
	LogAddA("You Selected Steam Is :[%s]", sss);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	if (!hProcess)
	{
		RECT trc = rcClient;
		trc.bottom += 50;
		trc.top = trc.bottom - 50;
		InvalidateRect(hWnd, &trc, TRUE);
		LogAdd(L"ERROR CHANGE STEAM:Can't Find Counter Strike!");
		MessageBoxA(0, "Counter Strike Not Found!", "ERROR:CS_FOUND", MB_ICONERROR);
		ERROR
		return;
	}
	int sLog;
	while (1) {
		if (GetModuleHandleProcess(pId,
			/*vgui2.dll*/XorStrW<0xD4, 10, 0x4D14BDF9>(L"\xA2\xB2\xA3\xBE\xEA\xF7\xBE\xB7\xB0" + 0x4D14BDF9).s)
			)
		{
			break;
		}
		Sleep(10);
	}
	Sleep(1000);
	switch (CSVER)
	{

	case IS3266OPENGL: {
		DWORD	ModuleBaseAddress = dwGetModuleBaseAddress(GetPID(L"hl.exe"), _T("hl.exe"));
		DWORD	OrginaleAddress = (ModuleBaseAddress + 0x19B376A);
		sLog = STEAM_CHANGER(OrginaleAddress, sss); break;
	}

	case IS3266SOFTWARE: {
		DWORD	ModuleBaseAddress = dwGetModuleBaseAddress(GetPID(L"hl.exe"), _T("hl.exe"));
		DWORD	OrginaleAddress = (ModuleBaseAddress + 0x12E51AA);
		sLog = STEAM_CHANGER(OrginaleAddress, sss); break;

	}
	case IS4554OPENGL: {
		DWORD	ModuleBaseAddress = dwGetModuleBaseAddress(GetPID(L"hl.exe"),
			/*hw.dll*/XorStrW<0x47, 7, 0x57C2F7E6>(L"\x2F\x3F\x67\x2E\x27\x20" + 0x57C2F7E6).s
		);
		DWORD	OrginaleAddress = (ModuleBaseAddress + 0x102942A);
		sLog = STEAM_CHANGER(OrginaleAddress, sss); break;

	}
	case IS4554SOFTWARE: {
		LogAdd(L"ERROR CHANGE STEAM: IS SOFTWARE 4554 Version!");
		MessageBoxA(0, "Sorry Your Counter Version Is 4554 And SoftWare Graphic!\r\n You Can't Steam Because sXe Don't Support This Version!\r\nPlease Download Counter strike 3266 Version Or Change Your Graphic to Opengl or D3D! ",
			"", MB_ICONERROR);
		return;
	}
	default:
		LogAdd(L"ERROR CHANGE STEAM: UNK CS VERSION!");
		break;
	}
	switch (sLog)
	{
	case CANT_WRITE_PROCESS:
		LogAdd(L"ERROR CHANGE STEAM:Can't Hooking Process!");
		break;
	case IS_EMPTY_STRING:
		LogAdd(L"ERROR CHANGE STEAM:Empty Steam!");
		break;
	case SECCUSS_SET_STEAM:

		LogAdd(L"Change Steam Successfully!");
		break;
	case IS_NOT_NUMBER:
		LogAdd(L"ERROR CHANGE STEAM:Your Steam Is Not Number!");
		ERROR
			break;
	default:
		LogAdd(L"ERROR CHANGE STEAM:UKN ERROR [%i] [%i] [", GetLastError(), sLog);
		ERROR
			break;
	}

}

static const char charecs[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuv";

int stringLength = sizeof(charecs) - 1;

char GenRandom() {

	return charecs[rand() % stringLength];
}
wchar_t szExeFileName[13];

bool IsRunAs()
{
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID SecurityIdentifier;
	if (!AllocateAndInitializeSid(&NtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&SecurityIdentifier))
		return 0;
	BOOL IsAdminMember;
	if (!CheckTokenMembership(NULL, SecurityIdentifier, &IsAdminMember))
		IsAdminMember = FALSE;
	FreeSid(SecurityIdentifier);
	return IsAdminMember;
}
std::ifstream::pos_type filesize(const char* filename)
{
	std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	return in.tellg();
}
INT APIENTRY GUI()
{
	MSG msg;
	if (filesize(
		/*CISCO_LOG.txt*/XorStrA<0x29, 14, 0x40BA6FFD>("\x6A\x63\x78\x6F\x62\x71\x63\x7F\x76\x1C\x47\x4C\x41" + 0x40BA6FFD).s
	) > 50000)
	{
		DeleteFileA(
			/*CISCO_LOG.txt*/XorStrA<0x29, 14, 0x40BA6FFD>("\x6A\x63\x78\x6F\x62\x71\x63\x7F\x76\x1C\x47\x4C\x41" + 0x40BA6FFD).s
		);
	}
	LogAdd(L"Starting VM...");
	wchar_t  szOrgFile[255];
	GetModuleFileName(hInst, szOrgFile, MAX_PATH);
	LogAdd(L"Starting Application...");

	wsprintfW(szExeFileName, L"%s", PathFindFileNameW(szOrgFile));
#if !_DEBUG
	if (!IsRunAs())
	{
		LogAdd(L"Need Run As Admin Strator ...");
		ShellExecute(hWnd, L"runas", szOrgFile, NULL, NULL, SW_SHOWDEFAULT);
		exit(0);
	}
#endif
	LogAdd(L"Is Running As Adminstrator.");
	if (wcscmp(
		/*sXe Dead.exe*/XorStrW<0x2E, 13, 0xEDE73839>(L"\x5D\x77\x55\x11\x76\x56\x55\x51\x18\x52\x40\x5C" + 0xEDE73839).s
		, szExeFileName))
	{
		LogAdd(L"Don't Change Name Of File! ORGINALE:[sXe Dead.exe] FAKE:[%s]", szExeFileName);
		GuiIsRunning = FALSE;
		LOG_EXIT
	}
	if (OpenMutexA(MUTEX_ALL_ACCESS, FALSE,
		/*CISCO_DRIVER*/XorStrA<0x28, 13, 0xECF1D80C>("\x6B\x60\x79\x68\x63\x72\x6A\x7D\x79\x67\x77\x61" + 0xECF1D80C).s
	))
	{
		SetForegroundWindow(FindWindow(APP_NAME, 0));
		LogAdd(L"Application Is Already Open  [MX]!");
		GuiIsRunning = FALSE;
		return EXIT_SUCCESS;
	}
	if (GetPID(szExeFileName) != GetCurrentProcessId()) {
		SetForegroundWindow(FindWindow(APP_NAME, 0));
		LogAdd(L"Application Is Already Open  [PN]!");
		GuiIsRunning = FALSE;
		return EXIT_SUCCESS;
	}
	LogAdd(L"\r\n\
--------------------------------------------------------------\r\n\
--========	 %s	    ========--\r\n\
--------------------------------------------------------------\r\n",
/**( SXE DEAD V2.0 BY CISCO_X )**/XorStrW<0x6E, 31, 0xAA51DE21>(L"\x44\x47\x50\x22\x2A\x36\x54\x31\x33\x36\x3C\x59\x2C\x49\x52\x4D\x5E\x3D\xD9\xA1\xC1\xCA\xD7\xC6\xC9\xD8\xD0\xA9\xA3\xA1" + 0xAA51DE21).s);
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;
	hMutex = CreateMutexA(NULL, FALSE,
		/*CISCO_DRIVER*/XorStrA<0x28, 13, 0xECF1D80C>("\x6B\x60\x79\x68\x63\x72\x6A\x7D\x79\x67\x77\x61" + 0xECF1D80C).s
	);
	LogAdd(L"Inestalling Driver...");
#if !_DEBUG
	if (InestallDriver())
		LogAdd(L"Driver Install Successfully!");
	else
	{
		LogAdd(L"Can't Install Driver!");
		GuiIsRunning = FALSE;
		LOG_EXIT
	}
#endif
	WNDCLASS wndClass;
	LogAdd(L"Init GUI...");
	InitCommonControls();
	wndClass.style = CS_DBLCLKS;
	wndClass.lpfnWndProc = wndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInst;
	wndClass.hIcon = static_cast<HICON>(::LoadImage(hInst,
		MAKEINTRESOURCE(IDI_ICON1),
		IMAGE_ICON,
		48, 48,
		LR_DEFAULTCOLOR));
	wndClass.hCursor = LoadCursor(hInst, IDC_ARROW);
	HPAINTBUFFER dc;
	HBITMAP hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	wndClass.hbrBackground = CreatePatternBrush(hBitmap);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = APP_NAME;
	SplashWindow sw(IDB_BITMAP2);
	if (!sw.isValidWindow())
	{
		GuiIsRunning = FALSE;
		return 1;
	}
	sw.showModalWindow(1);
	if (!RegisterClass(&wndClass))
	{
		LogAdd(L"Can't Init Graphic !");
		M(NULL, TEXT("Problem To Starting Program!"),
		APP_NAME, MB_ICONERROR);	GuiIsRunning = FALSE;
		LOG_EXIT
			return 0;
	}
	DWORD       dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE | WS_EX_TRANSPARENT;
	DWORD       dwStyle = dwStyle = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
		WS_MINIMIZEBOX | WS_EX_TRANSPARENT);
	LogAdd(L"Creating Windows...");
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	RECT rConsole;
	hWnd = CreateWindowEx(dwExStyle, APP_NAME,
		/*sXe Dead v2.0*/XorStrW<0xC3, 14, 0x76EFBED7>(L"\xB0\x9C\xA0\xE6\x83\xAD\xA8\xAE\xEB\xBA\xFF\xE0\xFF" + 0x76EFBED7).s
		,
		dwStyle,
		(GetSystemMetrics(SM_CXSCREEN)) / 2 - 200,
		((GetSystemMetrics(SM_CYSCREEN)) / 2) - 250
		, 400, 440, NULL, NULL, hInst, NULL);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	return msg.wParam;
}
INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nShowCmd)
{
	hInst = hInstance;
	return GUI();
}
DWORD WINAPI R_CS(LPVOID);
HWND g_HWND = NULL;
BOOL CALLBACK EnumWindowsProcMy(HWND hwnd, LPARAM lParam)
{
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(hwnd, &lpdwProcessId);
	if (lpdwProcessId == lParam)
	{
		g_HWND = hwnd;
		return FALSE;
	}
	return TRUE;
}
HWND EnumWin(DWORD pId)
{
	EnumWindows(EnumWindowsProcMy,
		GetPID(L"hl.exe")
	);
	return g_HWND;
}

DWORD WINAPI K_CS(LPVOID)
{

a:
	EnableWindow(btnSetSteam, TRUE);
	EnableWindow(ComboAntiSs, FALSE);
	EnableWindow(ComboBox, FALSE);
	HANDLE	hProcess =
		OpenProcess(PROCESS_ALL_ACCESS,
			FALSE,
			GetPID(L"hl.exe")
		);

	if (!hProcess)
	{
		CounterIsRunnig = false;
		RECT trc = rcClient;
		trc.bottom += 50;
		trc.top = trc.bottom - 50;
		InvalidateRect(hWnd, &trc, TRUE);
		LogAdd(L"Counter Strike Is Closed!");
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		SetForegroundWindow(hWnd);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)R_CS, 0, 0, 0);
		return 0;
	}

	Sleep(500);
	goto a;
	return 0;
}


hook_t reg;

DWORD WINAPI R_CS(LPVOID)
{
b:
	HANDLE	hProcess = OpenProcess(PROCESS_ALL_ACCESS,
		FALSE,
		GetPID(L"hl.exe")
	);
	EnableWindow(ComboAntiSs, TRUE);
	EnableWindow(ComboBox, TRUE);
	EnableWindow(btnSetSteam, FALSE);

	char txt[30];
	if (hProcess)
	{
		CounterIsRunnig = true;
		LogAdd((L"Counter Strike Opening"));
		while (1) {
			EnumWin(GetPID(L"hl.exe"));
			GetWindowTextA(g_HWND,
				txt,
				30);

			if (strlen(txt) != 0)
			{

				break;
			}
		}
		ShowWindow(g_HWND, SW_HIDE);
		SetOpacity(g_HWND, 1);
		LogAdd(L"Find Version ...");
		Sleep(100);

		CSVER = CheckVersion(hProcess);

		if (checkedAlias == true)
		{
			switch (CSVER)
			{
			case IS3266OPENGL: {
				DWORD ModuleBaseAddress = dwGetModuleBaseAddress(GetPID(L"hl.exe"), _T("hl.exe"));
				DWORD OrginaleAddress = (ModuleBaseAddress + 0xABE964);//OpenGl32


				RECT trc = rcClient;
				trc.bottom += 50;
				trc.top = trc.bottom - 50;
				InvalidateRect(hWnd, &trc, TRUE);
				if (ReCevar(OrginaleAddress,
					/*Alias*/XorStrA<0x9C, 6, 0xEA1DA07C>("\xDD\xF1\xF7\xFE\xD3" + 0xEA1DA07C).s
				)) {
					LogAdd(L"Alias Hooked Successfully!");
				}
				else {
				
					LogAdd(L"Problem To Hooking Alias!");

				}

			}
							   break;
			case IS3266SOFTWARE: {
				DWORD ModuleBaseAddress = dwGetModuleBaseAddress(GetPID(L"hl.exe"), _T("hl.exe"));
				DWORD OrginaleAddress = (ModuleBaseAddress + 0xAA8914);//SoftWare

				if (ReCevar(OrginaleAddress,
					/*Alias*/XorStrA<0x9C, 6, 0xEA1DA07C>("\xDD\xF1\xF7\xFE\xD3" + 0xEA1DA07C).s
				)) {
					LogAdd(L"Alias Hooked Successfully!");

				}
				else {
				
						LogAdd(L"Problem To Hooking Alias!");
				}
			}
								 break;
			case IS4554OPENGL: {
				DWORD ModuleBaseAddress = dwGetModuleBaseAddress(GetPID(L"hl.exe"), _T("hw.dll"));
				DWORD OrginaleAddress = (ModuleBaseAddress + 0x16DD8C);

				if (ReCevar(OrginaleAddress,
					/*Alias*/XorStrA<0x9C, 6, 0xEA1DA07C>("\xDD\xF1\xF7\xFE\xD3" + 0xEA1DA07C).s
				)) {
					LogAdd(L"Alias Hooked Successfully!");
				}
				else {
						LogAdd(L"Problem To Hooking Alias!");
				}

			}break;
			case IS4554SOFTWARE: {
					MessageBoxA(0, "Sorry Your Counter Version Is 4554 And SoftWare Graphic!\r\n You Can't Steam Because sXe Don't Support This Version!\r\nPlease Download Counter strike 3266 Version Or Change Your Graphic to Opengl or D3D! ", "Error", MB_ICONERROR);
			}
			default:

				break;
			}
		}
		ShowWindow(hWnd, SW_MINIMIZE);
		ShowWindow(g_HWND, SW_SHOW);
		SetForegroundWindow(g_HWND);
		for (auto i = 0; i < 256; i++)
		{
			SetOpacity(g_HWND, i);
			Sleep(10);
		}
		switch (ss_status)
		{
		case SS_OFF:
			break;
		case SS_BLACK: {

			switch (BlackScreen(
				hProcess)
				)
			{
			case BlackScreenFunc::BlackSuccess:
				LogAdd(_T("Set Black ScreenShot Successfully!"));
				break;
			case BlackScreenFunc::LoadLibraryErr:
				LogAdd(_T("Problem To Load Library [BLACK SS]"));
				break;
			case BlackScreenFunc::WriteMemErr:
				LogAdd(_T("Problem To WriteMemory! [BLACK SS]"));
				break;
			case BlackScreenFunc::GetProcAdErr:
				LogAdd(_T("Problem To Get Func Address! [BLACK SS]"));
				break;
			}
		}break;
		default:
			break;
		}
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)K_CS, 0, 0, 0);
		return 0;
	}
	Sleep(500);
	goto b;
	return 0;

}

DWORD WINAPI S_ICON(LPVOID)
{

	HICON hIcons[4];
	long nIndex = 0;
	hIcons[0] = static_cast<HICON>(::LoadImage(GetModuleHandle(NULL),
		MAKEINTRESOURCE(IDI_ICON1),
		IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR));
	hIcons[1] = static_cast<HICON>(::LoadImage(GetModuleHandle(NULL),
		MAKEINTRESOURCE(IDI_ICON2),
		IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR));
	hIcons[2] = static_cast<HICON>(::LoadImage(GetModuleHandle(NULL),
		MAKEINTRESOURCE(IDI_ICON3),
		IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR));
	hIcons[3] = static_cast<HICON>(::LoadImage(GetModuleHandle(NULL),
		MAKEINTRESOURCE(IDI_ICON4),
		IMAGE_ICON, 48, 48, LR_DEFAULTCOLOR));

	bool IsMainIcon = TRUE;
	while (1) {
		if (IsIconic(hWnd)) {
			
				SetClassLong(hWnd, GCL_HICON, (long)hIcons[nIndex++ % _totalArrayItem(hIcons)]);
				RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE);
			
			IsMainIcon = FALSE;

			if (nIndex == 4)
				nIndex = 0;

		}
		else if (IsMainIcon == FALSE)
		{
			SetClassLong(hWnd, GCL_HICON, (long)hIcons[0]);
			RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE);
			IsMainIcon = true;
		}
		Sleep(1000);
	}

}
DWORD WINAPI P_TRD(LPVOID)
{
c:
	if (!IsIconic(hWnd)) {
		char text[10];
		wchar_t wText[10];
		char v[25];
		GetWindowTextA(hWnd, v, 25);
		if (strlen(v) > 0)
		{
			ERROR
		}
		GetDlgItemTextA(hWnd, TXT_STEAM, text, 100);
		CurrentProgressPos = strlen(text);
		SendMessage(prgSteam, PBM_SETPOS, (WPARAM)CurrentProgressPos, 0);
		if (strlen(text) > 0) {
			if ((text[0] == '2' || text[0] == '1') && (
				text[1] == '1') && (text[2] == '1' || text[2] == '2' ||
					text[2] == '3' || text[2] == '4'))
			{
				SendMessage(txtSetSteam, EM_SETLIMITTEXT, 10, 0);
				ts.SetProgressValue(hWnd, CurrentProgressPos, 10);
				SendMessage(prgSteam, PBM_SETRANGE, 0, MAKELPARAM(0, 10));    //0->min value; 10->max value				
			}
			else {
				SendMessage(txtSetSteam, EM_SETLIMITTEXT, 9, 0);
				ts.SetProgressValue(hWnd, CurrentProgressPos, 9);
				SendMessage(prgSteam, PBM_SETRANGE, 0, MAKELPARAM(0, 9));    //0->min value; 10->max value
			}
		}
		else
		{
			CurrentProgressPos = 0;
		}
		Sleep(100);
	}
	else
	{
		Sleep(1000);
	}
	goto c;
}

wstring randomNum(int len)
{
	wchar_t wRet[14];
	wchar_t *cList = L"1234567890";
	for (size_t i = 0; i < len; i++)
	{
		wRet[i] = cList[rand() % wcslen(cList)];
	}
	return wRet;
}

void RandomSteam()
{
#pragma region RandomSteamFunc 

	char*HEX = "0123456789";
	string text = "";
	int lent = 9;

	for (int i = 0; i < lent; i++)
	{
		char t = '0';

		if (i == 0)

			while (t == '0')
			{
				t = HEX[rand() % strlen(HEX)];
			}
		if (i != 0)
			t = HEX[rand() % strlen(HEX)];
		text += t;
		if ((text[0] == '2' || text[0] == '1') && (
			text[1] == '1') && (text[2] == '1' || text[2] == '2' ||
				text[2] == '3' || text[2] == '4'))
			lent = 10;
		SetDlgItemTextA(hWnd, GetDlgCtrlID(txtSetSteam),
			text.c_str());
	}
#pragma endregion
}

void C_STEAM(char* lpText)
{
	ChangeSteam(lpText);
}
DWORD WINAPI T_SET(LPVOID)
{
	while (true)
	{
		HWND hw = FindWindow(NULL, L"sXe Dead v2.0");
		if (hw == hWnd)
		{
			break;
		}
		Sleep
		(300);
	}
	LogAdd(L"Reading Config setting...");
	FILE * file = fopen("Setting.ini", "r");
	char str[400];
	char Txt1[18],
		Txt2[18],
		Txt3[18],
		steam[11],
		allOne[4],
		Aliass[4],
		ssState[8];
	char* pch = NULL;
	if (file != NULL) {
		fread(str, sizeof(str), 1, file);
		fclose(file);
	}
	pch = strtok(str, "-==#$#==-");
	int i = 1;
	while (pch != NULL)
	{
		if (i == 1)
		{
			strcpy(Txt1, pch);
		}
		if (i == 2)
		{
			strcpy(Txt2, pch);
		}
		if (i == 3)
		{
			strcpy(Txt3, pch);
		}
		if (i == 4)
		{
			strcpy(steam, pch);
		}
		if (i == 5)
		{
			strcpy(allOne, pch);
		}
		if (i == 6)
		{
			strcpy(Aliass, pch);
		}
		if (i == 7)
		{
			strcpy(ssState, pch);
		}
		i++;
		pch = strtok(NULL, "-==#$#==-");
	}
	LogAddA("-------------[SETTING]------------\r\n\
			STEAM:%s\r\n\
			SXE1:%s\r\n\
			SXE2:%s\r\n\
			SXE3:%s\r\n\
			ALL_ONE:%s\r\n\
			ALIAS ENALE:%s\r\n\
			SS_STATE:%s\r\n"
		, steam
		, Txt1
		, Txt2
		, Txt3
		, (allOne[0] == 'T') ? "TRUE" : "FALSE"
		, (Aliass[0] == 'T') ? "TRUE" : "FALSE"
		, ((strcmp("BLACK", ssState) == 0) ?
			"BLACK" : "OFF"));
	if (strcmp("BLACK", ssState) == 0)
	{
		SendMessage(ComboAntiSs, CB_SETCURSEL, (WPARAM)1, (LPARAM)0);
	}
	SetDlgItemTextA(hWnd, TXT_STEAM, steam);
	if (strcmp(Txt1, "EMPTY"))
		SetDlgItemTextA(hWnd, TXT_SXE1, Txt1);
	if (strcmp(Txt2, "EMPTY"))
		SetDlgItemTextA(hWnd, TXT_SXE2, Txt2);
	if (strcmp(Txt3, "EMPTY"))
		SetDlgItemTextA(hWnd, TXT_SXE3, Txt3);
	if (allOne[0] == 'T')
	{
		CheckDlgButton(
			hWnd,
			CHECK_AIO,		 // check ComboBox Alias
			BST_CHECKED
		);
	}
	else
	{
		CheckDlgButton(
			hWnd,
			CHECK_AIO,		 // check ComboBox Alias
			BST_UNCHECKED
		);
	}
	if (Aliass[0] == 'T')
	{
		CheckDlgButton(
			hWnd,
			CHECK_ALAIS,		 // check ComboBox Alias
			BST_CHECKED
		);
	}
	else
	{
		CheckDlgButton(
			hWnd,
			CHECK_ALAIS,		 // check ComboBox Alias
			BST_UNCHECKED
		);
	}
	return 0;
}
HWND SetFont(HWND hWnd, const TCHAR* fontName, const long nFontSize,
	BOOL Bold, BOOL Italic, BOOL Underline, BOOL StrikeOut)
{
	HDC hdc = GetDC(hWnd);
	LOGFONT logFont = { 0 };
	logFont.lfHeight = -MulDiv(nFontSize, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	logFont.lfWeight = Bold ? FW_BOLD : FW_NORMAL;
	logFont.lfUnderline = Underline;
	logFont.lfItalic = Italic;
	logFont.lfStrikeOut = StrikeOut;
	_tcscpy_s(logFont.lfFaceName, fontName);
	HFONT s_hFont = CreateFontIndirect(&logFont);
	ReleaseDC(hWnd, hdc);
	SendMessage(hWnd, WM_SETFONT, (WPARAM)s_hFont, (LPARAM)MAKELONG(TRUE, 0));
	return hWnd;
}
DWORD WINAPI R_SXE(LPVOID);
DWORD WINAPI K_SXE(HWND h_sXe)
{
e:
	HANDLE	hProcess = OpenProcess(PROCESS_ALL_ACCESS,
		FALSE,
		GetPID(L"Injected.exe")
	);
	if (!hProcess)
	{
		sXeRunning = FALSE;
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)R_SXE, 0, 0, 0);
		return 0;
	}
	else
	{
		sXeRunning = TRUE;
	}
	Sleep(500);
	goto e;
	return 0;
}
HWND g_sXe = NULL;
BOOL CALLBACK EnumWindowsProcMysXe(HWND hwnd, LPARAM lParam)
{
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(hwnd, &lpdwProcessId);
	if (lpdwProcessId == lParam)
	{
		g_sXe = hwnd;
		return FALSE;
	}
	return TRUE;
}
HWND EnumsXe()
{
	EnumWindows(EnumWindowsProcMysXe,
		GetPID(L"Injected.exe")
	);
	return g_sXe;
}

DWORD WINAPI sXePatching()
{
	EnumsXe();
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetPID(L"Injected.exe"));
	ProtectMemWrite(hProcess, 0x004B2064, (PVOID)
		/*sXe Dead V2.0 [CISCO_X]*/XorStrA<0x5F, 24, 0xB090F373>("\x2C\x38\x04\x42\x27\x01\x04\x02\x47\x3E\x5B\x44\x5B\x4C\x36\x2D\x26\x23\x32\x3D\x2C\x2C\x28" + 0xB090F373).s
		, 25);
	if (!MemHacking(hProcess))
	{
		LogAdd(L"MEM_HACKING:PB[%i]",GetLastError());
	}
	char txt[255];
	GetWindowTextA(g_sXe, txt, 255);
	if (txt > 0)
		Sleep(3000);
	return 0;

}

DWORD WINAPI R_SXE(LPVOID)
{
f:
	HANDLE	hProcess = OpenProcess(PROCESS_ALL_ACCESS,
		FALSE,
		GetPID(L"Injected.exe")
	);
	if (hProcess) {
		LogAdd((L"sXe-Injected Opening"));
		while (true)
		{

			HWND h_sXe = FindWindow(0, L"sXe Dead V2.0 [CISCO_X]");

			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)sXePatching, 0, 0, 0);


			if (h_sXe)
			{

				EnumsXe();
				sXeRunning = TRUE;
				Sleep(100);
				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)K_SXE, h_sXe, 0, 0);
				return 0;
			}
			Sleep(50);
		}
	}
	Sleep(500);
	goto f;
	return 0;
}

bool StartingThreading()
{

	if (!CreateThread(0,
		0,
		(LPTHREAD_START_ROUTINE)P_TRD,
		0,
		0,
		0
	) ||
		!CreateThread(0,
			0,
			(LPTHREAD_START_ROUTINE)S_ICON,
			0,
			0,
			0
		) ||
		!CreateThread(0,
			0,
			(LPTHREAD_START_ROUTINE)R_CS,
			0,
			0,
			0
		) ||
		!CreateThread(0,
			0,
			(LPTHREAD_START_ROUTINE)R_SXE,
			0,
			0,
			0
		) ||
		!CreateThread(0,
			0,
			(LPTHREAD_START_ROUTINE)T_SET,
			0,
			0,
			0
		))
		return false;
	else
		return true;
}


bool isNumberCheck(std::wstring str)
{
	std::wistringstream iss(str);
	int f;
	wchar_t wc;
	if (str.length() > 0)
		if (!(iss >> f) || iss.get(wc))
			return false;
	return true;
}
void onEditChange(HWND hDlg, int ctrlID)
{
	HWND hEdit = GetDlgItem(hDlg, ctrlID);
	size_t len = GetWindowTextLength(hEdit) + 1;
	wchar_t* cstr = new wchar_t[len];
	GetWindowText(hEdit, cstr, len);
	std::wstring wstr(cstr);
	if (!(isNumberCheck(wstr)))
	{
		SetDlgItemText(hDlg, ctrlID, L"");
		EDITBALLOONTIP bln;
		bln.cbStruct = sizeof(EDITBALLOONTIP);
		bln.pszTitle = L"Error";
		bln.pszText = L"Please Just Add Number!";
		bln.ttiIcon = TTI_ERROR;
		Edit_ShowBalloonTip(hEdit, &bln);
	}
	delete[] cstr;
}
LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	HDC hDC;
	static HTHEME hTheme = 0;
	static HFONT hFont = 0;
	TCHAR A[17];
	GetClientRect(hWnd, &rcClient);
	int  k = 0;
	PAINTSTRUCT Ps;
	LRESULT lRet = 0;
	bool fCallDWP = true;
#pragma endregion
	checkAio =
		IsDlgButtonChecked(hWnd, CHECK_AIO);
	checkedAlias =
		IsDlgButtonChecked(hWnd, CHECK_ALAIS);
	UNREFERENCED_PARAMETER(lParam);
	int wmId = LOWORD(wParam);
	switch (msg)
	{
	case WM_DWMCOMPOSITIONCHANGED: {
		if (IsCompositionActive())
		{

			Aero(hWnd,
				10,
				10,
				5,
				50);
		}

	}
	case WM_THEMECHANGED:
	{  LOGFONT lf;
	BOOL bLogFontValid = FALSE;

	if (hTheme) CloseThemeData(hTheme);
	hTheme = OpenThemeData(hWnd, TEXT("globals"));
	if (hTheme) {
		bLogFontValid = SUCCEEDED(GetThemeSysFont(hTheme, 805, &lf));
	}
	else {
		NONCLIENTMETRICS ncm = { sizeof(ncm) };
		if (SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, FALSE)) {
			lf = ncm.lfMessageFont;
			bLogFontValid = TRUE;
		}
	}
	if (bLogFontValid) {
		lf.lfHeight *= 3;
		if (hFont) DeleteObject(hFont);
		hFont = CreateFontIndirect(&lf);
	}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		RECT rc;
		if (GetClientRect(hWnd, &rc) && BeginPaint(hWnd, &ps)) {
			rc.top = rc.bottom - 50;
			if (hFont) {
				SelectObject(ps.hdc, hFont);
			}
			DrawTextComposited(hTheme, 0, 0, ps.hdc,/*sXe Dead v2.0 By [CISCO_X]*/XorStrW<0x9A, 27, 0x3FE35F97>(L"\xE9\xC3\xF9\xBD\xDA\xFA\xC1\xC5\x82\xD5\x96\x8B\x96\x87\xEA\xD0\x8A\xF0\xEF\xE4\xFD\xEC\xFF\xEE\xEA\xEE" + 0x3FE35F97).s,
				-1, DT_SINGLELINE | DT_CENTER | DT_VCENTER, &rc, 10);
			EndPaint(hWnd, &ps);
		}
		HDC dc = GetDC(hWnd);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		RECT rect;
		GetClientRect(hWnd, &rect);
		int x = 320;
		int y = 310;
		DrawIcon(dc, x, y,
			static_cast<HICON>(::LoadImage(hInst,
				MAKEINTRESOURCE(IDI_ICON1),
				IMAGE_ICON,
				800, 800,
				LR_DEFAULTCOLOR))
		);
		SetFocus(hWnd);
	}
	break;
	case WM_NOTIFY:
	{
		ThemeButton(lParam);
		return CDRF_DODEFAULT;
	}
	break;
	case WM_CREATE:
	{
		if (!StartingThreading())
		{
			LogAdd(L"Problem To Running All Threads...!");
		}
		else
		{
			LogAdd(L"T_START Now...");
		}
		INITCOMMONCONTROLSEX icc;
		icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icc.dwICC = ICC_TAB_CLASSES;
		InitCommonControlsEx(&icc);
		SetTimer(hWnd, IDT_TIMER1, 200, (TIMERPROC)NULL);
		SendMessage(hWnd, WM_THEMECHANGED, 0, 0);
		SendMessage(hWnd, WM_DWMCOMPOSITIONCHANGED, 0, 0);
		OnPaint(hWnd);
		LogAdd(L"Creating Objects...");
		if (OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetPID(L"hl.exe")))
		{

			LogAdd(L"Counter Strike Is Open! Closing HL.exe..");
			if (TerminateProcess(
				OpenProcess(PROCESS_TERMINATE,
					FALSE,
					GetPID(L"hl.exe")
				),
				EXIT_SUCCESS
			))
				LogAdd(L"Kill hl.exe Successfully!");
			else {
				LogAdd(L"Problem To Kill hl.exe");
				LOG_EXIT
					return 0;
			}
		}
		if (OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetPID(L"Injected.exe")))
		{

			LogAdd(L"sXe Injected Is Open! Closing Injected.exe..");
			if (TerminateProcess(
				OpenProcess(PROCESS_TERMINATE,
					FALSE,
					GetPID(L"Injected.exe")),
				EXIT_SUCCESS))
				LogAdd(L"Kill Injected.exe Successfully!");
			else {
				LogAdd(L"Problem To Kill Injected.exe");
				LOG_EXIT
					return 0;
			}

		}

#pragma region Objects_Form

		/* Steam Progress Bar  */
		prgSteam = CreateWindowEx(
			0,
			PROGRESS_CLASS,
			NULL,
			WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
			40, 80, 300, 22,
			hWnd,
			NULL,
			hInst,
			NULL
		);

		SendMessage(prgSteam,
			PBM_SETRANGE,
			0,
			MAKELPARAM(0, 10)
		);
		ts.SetProgressState(hWnd, TBPF_ERROR);


		/*  Button Exit Application  */
		btnExit = CreateWindowEx(
			0,
			L"Button",
			L"Exit",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			30, 310, 85, 30,
			hWnd,
			(HMENU)EXIT_APP,
			0,
			NULL
		);


		/*  Button Set Steam   */
		btnSetSteam = CreateWindowEx(
			0,
			L"Button",
			L"Set Steam",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			40, 40, 85, 30,
			hWnd,
			(HMENU)SET_STEAM,
			0,
			NULL
		);


		/*  Button Random HWID   */
		btnRandomHwid = CreateWindowEx(
			0,
			L"Button",
			L"Random",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			280, 160, 85, 30,//	270, 130, 85, 30,
			hWnd,
			(HMENU)BTN_RANDOM_HWID,
			0,
			NULL
		);

		/*  Alias Check Box*/
		CheckBoxAlias = CreateWindowEx(
			WS_EX_TRANSPARENT,
			L"Button",
			L"Alias Enable",
			WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
			250, 263, 110, 30,
			hWnd,
			(HMENU)CHECK_ALAIS,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL
		);


		/*  AIO Check Box*/
		CheckBoxAIO = CreateWindowEx(
			WS_EX_TRANSPARENT,
			L"Button",
			L"All One",
			WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
			265, 193, 90, 30,
			hWnd,
			(HMENU)CHECK_AIO,
			((LPCREATESTRUCT)lParam)->hInstance,
			NULL
		);


		CheckDlgButton(hWnd, CHECK_ALAIS, BST_CHECKED);

		/*  TextBox sXe1   */
		txtSxe1 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"Edit",
			0,
			WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
			80, 130, 180, 23,
			hWnd,
			(HMENU)TXT_SXE1,
			0,
			NULL
		);

		/*  TextBox sXe2   */
		txtSxe2 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"Edit",
			0,
			WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
			80, 160, 180, 23,
			hWnd,
			(HMENU)TXT_SXE2,
			0,
			NULL
		);


		/*  TextBox sXe3   */
		txtSxe3 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"Edit",
			0,
			WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
			80, 190, 180, 23,
			hWnd,
			(HMENU)TXT_SXE3,
			0,
			NULL
		);

		/*  Lable sXe 1   */
		lblSxe1 = CreateWindowEx(
			WS_EX_TRANSPARENT,
			L"STATIC",
			L"sXe 1:",
			WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
			30, 135, 50, 23,
			hWnd,
			0,
			hInst,
			NULL);


		/*  Lable sXe 2   */
		lblSxe2 = CreateWindowEx(
			WS_EX_TRANSPARENT,
			L"STATIC",
			L"sXe 2:",
			WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
			30, 165, 50, 23,
			hWnd,
			0,
			hInst,
			NULL);


		/*  Lable sXe 1   */
		lblSxe3 = CreateWindowEx(
			WS_EX_TRANSPARENT,
			L"STATIC",
			L"sXe 3:",
			WS_CHILD | WS_VISIBLE | SS_LEFT | WS_SYSMENU,
			30, 195, 50, 23,
			hWnd,
			0,
			hInst,
			NULL);


		/* Button Random Steam   */
		btnRandomsteam = CreateWindowEx(
			0,
			L"Button",
			L"Random",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			260, 40, 85, 30,
			hWnd,
			(HMENU)BTN_RANDOM_STEAM,
			0,
			NULL
		);

		/*  Button Set HWID  */
		btnSetHWID = CreateWindowEx(
			0,
			L"Button",
			L"Set HWID",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			280, 130, 85, 30,
			hWnd,
			(HMENU)BTN_SET_HWID,
			0,
			NULL
		);

		/*  Button About  */
		btnAbout = CreateWindowEx(
			0,
			L"Button",
			L"About",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			130, 310, 85, 30,
			hWnd,
			(HMENU)BTN_ABOUT,
			0,
			NULL
		);

		/* TextBox Input Steam  */
		txtSetSteam = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"Edit",
			0,
			WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
			130, 43, 125, 23,
			hWnd,
			(HMENU)TXT_STEAM,
			0,
			NULL
		);

		/* GroupBox sXe HWID  */
		GroupBoxsXe = CreateWindow(L"Button",
			L"sXe HWID Changer",
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX | BS_BITMAP,
			20, 115, 350, 120,
			hWnd,
			0,
			hInst,
			0
		);

		/* GroupBox Steam Changer  */
		GroupBoxSteam = CreateWindow(L"Button",
			L"Steam Changer",
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX | BS_BITMAP,
			20, 10, 350, 100,
			hWnd,
			0,
			hInst,
			0
		);

		/* GroupBox Anti Screen Shot  */
		GroupBoxSs = CreateWindow(L"Button",
			L"Anti ScreenShot",
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX | BS_BITMAP,
			20, 240, 200, 60,
			hWnd,
			0,
			hInst,
			0);

		/* GroupBox Alias Enabler  */
		GroupBoxAlias = CreateWindow(L"Button",
			L"Alias Enabler",
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX | BS_BITMAP,
			230, 240, 140, 60,
			hWnd,
			0,
			hInst,
			0
		);
		TCHAR ListAntiSs[4][33] =
		{
		TEXT("OFF"),	TEXT("BLACK SS")
		};
		TCHAR A[39];
		int  k = 0;
		ComboAntiSs = CreateWindow(WC_COMBOBOX, TEXT(""),
			CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
			30, 270, 160, 60,
			hWnd,
			(HMENU)COMBO_SS,
			hInst,
			NULL);
		memset(&A, 0, sizeof(A));
		for (k = 0; k < 2; k++)
		{
			wcscpy_s(A, sizeof(A) / sizeof(TCHAR), (TCHAR*)ListAntiSs[k]);
			// Add string to combobox.
			SendMessage(ComboAntiSs, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
		}
		SendMessage(ComboAntiSs, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
#pragma endregion

#pragma region Fonts
		hFontVerdana =
			CreateFont(14,
				0,
				0,
				0,
				FW_DONTCARE,
				FALSE,
				FALSE,						  // Creating New Font
				FALSE,
				ANSI_CHARSET,
				OUT_TT_PRECIS,
				CLIP_TT_ALWAYS,
				DEFAULT_QUALITY,
				FF_DONTCARE,
				L"tahoma"
			);
		SendMessage(
			lblSendMessage,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			ComboAntiSs,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			txtSxe1,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			txtSxe2,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			CheckBoxAlias,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			txtSxe3,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			GroupBoxAlias,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			btnRandomHwid,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			lblSxe1,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			lblSxe2,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			lblSxe3,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			GroupBoxsXe,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			btnInjectCheat,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			btnSetHWID,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			btnAbout,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			GroupBoxSs,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			btnAntiSs,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			btnSetSteam,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0);
		SendMessage(
			txtSetSteam,
			WM_SETFONT,
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			btnExit,
			WM_SETFONT,              // Set Btn Exit Font
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			btnRandomsteam,
			WM_SETFONT,            // Set btn Random Steam Font
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			ComboBox,
			WM_SETFONT,            // Set Cobmobox Font
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			GroupBoxSteam,
			WM_SETFONT,            // Set Steam Group Box Font
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			CheckBoxAlias,
			WM_SETFONT,            // Set Steam Group Box Font
			(WPARAM)hFontVerdana,
			0
		);
		SendMessage(
			CheckBoxAIO,
			WM_SETFONT,            // Set Steam Group Box Font
			(WPARAM)hFontVerdana,
			0
		);
		SetTimer(hWnd, IDT_TIMER1, 200, (TIMERPROC)NULL);
		SendMessage(prgSteam, PBM_SETSTATE, PBST_ERROR, 0);
#pragma endregion
	}
	case WM_CTLCOLORBTN:
		if ((HWND)lParam)
		{
			HBRUSH hbr = (HBRUSH)DefWindowProc(
				hWnd,
				msg,
				wParam,
				lParam
			);
			return (BOOL)hbr;
		}
		return FALSE;
	case WM_CTLCOLORMSGBOX:
		break;
	case WM_CTLCOLORSTATIC:
	{
		(BOOL)GetSysColorBrush(COLOR_MENU);
		HBRUSH hbr = (HBRUSH)DefWindowProc(hWnd, msg, wParam, lParam);
		::DeleteObject(hbr);
		SetTextColor(
			(HDC)wParam,
			RGB(
				255,
				255,		//Set Text Color
				255
			)
		);
		SetBkMode((HDC)wParam, TRANSPARENT);

	}
	return (LRESULT)GetStockObject(NULL_BRUSH);
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
#pragma region btnEvents
		case COMBO_SS:
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
					(WPARAM)0, (LPARAM)0);
				if (ItemIndex == 0)
				{
					ss_status = SS_OFF;
				}
				if (ItemIndex == 1)
				{
					ss_status = 1;
				}
				if (ItemIndex == 2)
				{
					ss_status = 2;
				}
				if (ItemIndex == 3)
				{

					ss_status = 3;
				}
			}
			break;
		case CHECK_AIO:
			if (checkAio) {

				CheckDlgButton(
					hWnd,
					CHECK_AIO,             // Uncheck ComboBox Alias
					BST_UNCHECKED);
			}
			else {

				CheckDlgButton(
					hWnd,
					CHECK_AIO,		 // check ComboBox Alias
					BST_CHECKED
				);
			}
			break;
		case CHECK_ALAIS:
			if (checkedAlias) {

				CheckDlgButton(
					hWnd,
					CHECK_ALAIS,             // Uncheck ComboBox Alias
					BST_UNCHECKED
				);

			}
			else {

				CheckDlgButton(
					hWnd,
					CHECK_ALAIS,		 // check ComboBox Alias
					BST_CHECKED
				);
			}
			break;
		case BTN_SET_HWID: {
			char
				Txt1[100],
				Txt2[100],
				Txt3[100];
			GetDlgItemTextA(
				hWnd,
				TXT_SXE1,
				Txt1,
				100
			);
			GetDlgItemTextA(
				hWnd,
				TXT_SXE2,
				Txt2,
				100
			);
			GetDlgItemTextA(
				hWnd,
				TXT_SXE3,
				Txt3,
				100
			);
		
				RECT trc = rcClient;
				trc.bottom += 50;
				trc.top = trc.bottom - 50;
				InvalidateRect(hWnd, &trc, TRUE);
				if (SpoofingDriverHWID(
					Txt1,
					Txt2,
					Txt3
				)) {
					LogAddA("Change HWID to [(%s)-(%s)-(%s)]"
						, Txt1, Txt2, Txt3);
				}
				else {
					LogAdd(L"Problem To Change HWID!");
				
				}
		
			Sleep(400);
		}
	  break;

		case EXIT_APP:
			LogAdd(L"EXIT...");
			exit(0);
			break;
		case SET_STEAM:
			char text[20];
			GetDlgItemTextA(
				hWnd,
				TXT_STEAM,
				text,
				100
			);
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)C_STEAM, &text, 0, 0);
			Sleep(800);
			break;
		case BTN_ABOUT:
		{

			wstring  data2 =
				/*C:\\Windows\\Temp\\CIS.mp4*/XorStrW<0x56, 24, 0x9EEA1B39>(L"\x15\x6D\x04\x0E\x33\x35\x38\x32\x29\x2C\x3C\x35\x07\x0E\x14\x39\x25\x2E\x3B\x47\x07\x1B\x58" + 0x9EEA1B39).s;
			ExtractData(data2.c_str(), IDR_RCDATA2, RT_RCDATA);
			data2.clear();
			wchar_t* pPath = new wchar_t[MAX_PATH];
			GetModuleFileNameW(hInst, pPath, MAX_PATH);
			pPath[wcsrchr(pPath, L'\\') - pPath + 1] = 0;
			wcscat(pPath,
				/*sXe_Disabler.exe*/XorStrW<0x09, 17, 0xF37A4BF9>(L"\x7A\x52\x6E\x53\x49\x67\x7C\x71\x73\x7E\x76\x66\x3B\x73\x6F\x7D" + 0xF37A4BF9).s
			);
			ExtractData(pPath, IDR_RCDATA3, RT_RCDATA);
			PROCESS_INFORMATION piProcInfo;
			STARTUPINFO siStartInfo;
			ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
			ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
			siStartInfo.cb = sizeof(STARTUPINFO);
			ShowWindow(hWnd, SW_HIDE);
			HWND hwnd = GetDesktopWindow();
			HDC hdc = GetWindowDC(hwnd);
			RECT rekt;
			GetWindowRect(hwnd, &rekt);
			int w = rekt.right - rekt.left;
			int h = rekt.bottom - rekt.top;
			int x1 = rand() % (w - 400);
			int y1 = rand() % (h - 400);
			int x2 = rand() % (w - 400);
			int y2 = rand() % (h - 400);
			int width = rand() % 400;
			int height = rand() % 400;
			PLAY_WAV(IDR_WAVE3)
				BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, DSTINVERT);
			//SRCPAINT
			if (CreateProcessW(pPath,
				/*-Video*/XorStrW<0x48, 7, 0x4FB1715E>(L"\x65\x1F\x23\x2F\x29\x22" + 0x4FB1715E).s
				, NULL, NULL, TRUE, CREATE_SUSPENDED, NULL, NULL, &siStartInfo, &piProcInfo))
			{

				ResumeThread(piProcInfo.hThread);
				WaitForSingleObject(piProcInfo.hProcess, INFINITE);
				CloseHandle(piProcInfo.hProcess);
				CloseHandle(piProcInfo.hThread);

				ShowWindow(hWnd, SW_SHOW);
			}

		}
		break;
		case TXT_STEAM:

			if (HIWORD(wParam) == EN_CHANGE)
			{
				onEditChange(hWnd, TXT_STEAM);
			}
			break;

		case BTN_RANDOM_STEAM:

			wchar_t buf[255];
			GetDlgItemText(
				hWnd,
				TXT_STEAM,
				buf,
				10
			);
			wsprintf(
				buf,
				L"New Steam:%s",
				buf
			);
			RandomSteam();

			break;
		case BTN_RANDOM_HWID:
			srand(time(0));
			string random1, random2, random3;
			int length = 17;
			for (unsigned int i = 0; i < length; ++i)
			{
				if (checkAio) {
					random1 += GenRandom();
					random2 = random1;
					random3 = random1;
				}
				else
				{
					random1 += GenRandom();
					random2 += GenRandom();
					random3 += GenRandom();
				}
			}
			SetDlgItemTextA(
				hWnd,
				TXT_SXE1,
				random1.c_str()
			);
			SetDlgItemTextA(
				hWnd,
				TXT_SXE2,
				random2.c_str()
			);
			SetDlgItemTextA(
				hWnd,
				TXT_SXE3,
				random3.c_str()
			);

			break;
#pragma endregion

		}
		break;


	case WM_CLOSE: {
		if (sXeRunning == true && CounterIsRunnig == true) {
			int i = MessageBox(hWnd, L"Do you want to exit the program?\
				if you exit the application, the Counter-Strike and sXe will be closed!", L"Warning", MB_ICONQUESTION | MB_YESNO);
			if (i == IDNO)
			{
				return 0;
			}
		}




		LogAdd(L"EXIT 0");
		DestroyWindow(hWnd);

	}
				   break;
	case WM_QUIT:

		break;
	case WM_DESTROY:
		char Txt1[18],
			Txt2[18],
			Txt3[18],
			steam[11],
			*allOne = "TRUE";
		GetDlgItemTextA(hWnd, TXT_SXE1, Txt1, 18);
		GetDlgItemTextA(hWnd, TXT_SXE2, Txt2, 18);
		GetDlgItemTextA(hWnd, TXT_SXE3, Txt3, 18);
		GetDlgItemTextA(hWnd, TXT_STEAM, steam, 11);
		FILE *outfile;
		outfile = fopen("Setting.ini", "wb");
		char buff[sizeof(Txt1) + sizeof(Txt2) + sizeof(Txt3) + sizeof(steam) + sizeof(allOne) + 200];
		sprintf(buff, "%s-==#$#==-%s-==#$#==-%s-==#$#==-%s-==#$#==-%s-==#$#==-%s-==#$#==-%s-==#$#==-",
			(Txt1[0] == '\0') ? "EMPTY" : Txt1, (Txt2[0] == '\0') ? "EMPTY" : Txt2, (Txt3[0] == '\0') ? "EMPTY" : Txt3,
			(steam[0] == '\0') ? "EMPTY" : steam,
			checkAio ? "T" : "F", checkedAlias ? "T" : "F", (ss_status == 0) ? "OFF" : "BLACK");
		fwrite(buff, sizeof(buff), 1, outfile);
		FREE(buff)
			FREE(Txt1)
			FREE(Txt2)
			FREE(Txt3)
			FREE(steam)
			fclose(outfile);
		LogAdd(L"Unistalling Driver...");

		if (UnistallDriver())
			LogAdd(L"Unistall Driver Successfully!");
		else
			LogAdd(L"Unistall Driver Problem!");

		CloseHandle(hMutex);
		PlaySoundA(MAKEINTRESOURCEA(IDR_WAVE1), hInst, SND_RESOURCE | SND_MEMORY);
		GuiIsRunning = FALSE;
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
