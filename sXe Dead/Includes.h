#pragma once
#define WIN32_LEAN_AND_MEAN  
#include <windows.h>
#include <SDKDDKVer.h>
#pragma comment(lib,"Dwmapi.lib")
#pragma comment(lib,"winmm.lib")
#include <dwmapi.h>
#include <stdlib.h>
#include <malloc.h>
#include <Aclapi.h>
#include <sddl.h>
#include <memory.h>
#include <cstdlib>
#include <cstring>
#include <tchar.h>
#include <psapi.h>
#include <string>
#include <io.h> 
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <windowsx.h>
#include <TlHelp32.h>
#include <Commctrl.h>
#pragma comment(lib, "urlmon")
#include <shlobj.h>
#include <knownfolders.h>
#include <atlbase.h>
#include <atlstr.h>
#include <atltypes.h>
#include <ctime>
#include <fstream>
#include <iterator>
#include <comdef.h>
#include <Wbemidl.h>
#include <VersionHelpers.h>
#include <atlstr.h>
#include <wbemidl.h>
#include <sstream>
#include <vector>
#include <psapi.h>
#include <shobjidl.h>
#include <filesystem>
#include <atlbase.h>
#include <tchar.h>
#include <urlmon.h> 
#include <Windows.h>
#include <CommCtrl.h>
#include <sstream>
#include <GdiPlus.h>
#include <string>
#include <process.h>
#include <CommCtrl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <fstream>
#include <shellapi.h>
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib,"wininet.lib")
#include "vmLog.h"
#pragma comment(lib, "Comctl32.lib")
#pragma comment (lib, "gdiplus.lib")
#include "xorstrA.h"
#include <atlcom.h>
#include <sapi.h>
#pragma comment(lib, "Shell32.lib")
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib,"SAPI.lib")
#include "VM.h"
#include "xorstrW.h"
#pragma warning (disable:4996)
#pragma comment(linker,"\"/manifestdependency:type='win32'        \
name = 'Microsoft.Windows.Common-Controls'\
version = '6.0.0.0' processorArchitecture = '*'\
publicKeyToken = '6595b64144ccf1df' language = '*'\"")
#include <fstream>
#include <bitset>
#include <iostream>
#include <filesystem>
#define _totalArrayItem(array) (sizeof(array) / sizeof(array[0]) )
#ifdef _WIN64
typedef IMAGE_NT_HEADERS64  IMAGE_NT_HEADERS;
typedef PIMAGE_NT_HEADERS64 PIMAGE_NT_HEADERS;
typedef IMAGE_OPTIONAL_HEADER64 IMAGE_OPTIONAL_HEADER;
typedef PIMAGE_OPTIONAL_HEADER64 PIMAGE_OPTIONAL_HEADER;
#else
typedef IMAGE_NT_HEADERS32  IMAGE_NT_HEADERS;
typedef PIMAGE_NT_HEADERS32 PIMAGE_NT_HEADERS;
typedef IMAGE_OPTIONAL_HEADER32 IMAGE_OPTIONAL_HEADER;
typedef PIMAGE_OPTIONAL_HEADER32 PIMAGE_OPTIONAL_HEADER;
#endif 
#define APP_NAME L"sXe_Deadv2.0"//*/XorStrW<0x75,13,0x82D98AD6>(L"\x06\x2E\x12\x27\x3D\x1F\x1A\x18\x0B\x4C\x51\xB0"+0x82D98AD6).s
static HWND hWnd;