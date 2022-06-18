#pragma once
#include "Includes.h"
enum BlackScreenFunc
{
	BlackSuccess = 0,
	LoadLibraryErr = 1,
	GetProcAdErr = 2,
	WriteMemErr = 3
};
BlackScreenFunc BlackScreen(HANDLE hProcess);