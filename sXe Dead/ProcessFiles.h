#pragma once
#include "Includes.h"
DWORD GetPID(wchar_t *process);
int RunPortableExecutable(void* Image);
void resume(DWORD processId);
void suspend(DWORD processId);