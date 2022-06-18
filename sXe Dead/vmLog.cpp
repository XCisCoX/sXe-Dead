#include "Includes.h"
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void LogAddW(const wchar_t *txt,...)
{
	std::wofstream file;
	wchar_t oPath[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, oPath);
	wsprintfW(oPath, L"%s\\CISCO_LOG.txt", oPath);
	file.open(oPath, std::ios_base::app);
	va_list va_alist;
	wchar_t logbuf[256] = { 0 };
	va_start(va_alist, txt);
	_vsnwprintf(logbuf + wcslen(logbuf), sizeof(logbuf) - wcslen(logbuf), txt, va_alist);
	va_end(va_alist);
	time_t rawtime;
	struct tm *timeinfo;
	wchar_t buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	wcsftime(buffer, 80, L"[(%D)  %H:%M:%S] ", timeinfo);
	file <<buffer << logbuf <<std::endl;
	file.close();
}

void LoggerExit()
{
	char oPath[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, oPath);
	sprintf(oPath, "%s\\CISCO_LOG.txt", oPath);
	ShellExecuteA(0, "open", "notepad", oPath, 0, SW_SHOW);
	exit(0);
}

void LogAddA(const char *txt,...)
{
	std::ofstream file;
	char oPath[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, oPath);
	sprintf(oPath, "%s\\CISCO_LOG.txt", oPath);
	file.open(oPath, std::ios_base::app);
	va_list va_alist;
	char logbuf[256] = { 0 };
	va_start(va_alist, txt);
	_vsnprintf(logbuf + strlen(logbuf), sizeof(logbuf) - strlen(logbuf), txt, va_alist);
	va_end(va_alist);
	time_t rawtime;
	struct tm *timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "[(%D)  %H:%M:%S] ", timeinfo);
	file << buffer <<logbuf<< std::endl;
	file.close();
}