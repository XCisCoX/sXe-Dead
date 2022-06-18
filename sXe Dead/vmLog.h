#pragma once
#include "Includes.h"
#if UNICODE
#define LogAdd LogAddW
#else
#define LogAdd LogAddA
#endif
#define LOG_EXIT LoggerExit();
void LoggerExit();
EXTERN_C {
	__declspec(dllexport) 
	void LogAddW(const wchar_t *txt, ...);
	__declspec(dllexport)
	void LogAddA(const char *txt, ...);
}
