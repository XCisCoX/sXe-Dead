#pragma once
#include"Includes.h"
unsigned char* find_locs(HANDLE process, std::string const &pattern);
bool ProtectMemWrite(HANDLE process, DWORD addr, PVOID input, int sizes);