#pragma once
#include <Windows.h>
#include <iostream>
#include <iostream>
using namespace std;
#include <fstream>
#pragma warning(disable:4996)
bool ExsistDriver();
bool  MemHacking(HANDLE hProcess);
bool memSender(HANDLE hProcess, DWORD Address, LPCVOID NewVal, SIZE_T sizes);
bool ExsistReg();
bool InestallDriver();
bool 	UnistallDriver();
bool SpoofingDriverHWID(char*sXe1, char*sXe2, char*sXe3);
