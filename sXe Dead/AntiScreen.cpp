#include "AntiScreen.h"

bool BlockAPI(HANDLE hProcess, CHAR *libName, CHAR *apiName)
{
	CHAR __r[] = { 0xC3 };
	HINSTANCE __l = NULL;
	VOID *__a = NULL;
	BOOL __br = FALSE;
	DWORD __dr = 0;
	__l = LoadLibraryA(libName);
	if (__l) {
		__a = (VOID*)GetProcAddress(__l, apiName);
		if (__a) {
			if (WriteProcessMemory(hProcess,
				(LPVOID)__a,
				(LPCVOID)__r,
				sizeof(__r),
				&__dr)) {
				if (__dr) {
					__br = TRUE;
				}
			}
		}
		FreeLibrary(__l);
	}
	return __br;
}
BlackScreenFunc BlackScreen(HANDLE hProcess)
{
	if (BlockAPI(hProcess, 
		/*Opengl32.dll*/XorStrA<0x1F, 13, 0x51E68614>("\x50\x50\x44\x4C\x44\x48\x16\x14\x09\x4C\x45\x46" + 0x51E68614).s
		,/*glReadPixels*/XorStrA<0x93, 13, 0xE3EBE1E9>("\xF4\xF8\xC7\xF3\xF6\xFC\xC9\xF3\xE3\xF9\xF1\xED" + 0xE3EBE1E9).s
	) == true)
		return BlackScreenFunc::BlackSuccess;
	else
		return BlackScreenFunc::WriteMemErr;
}