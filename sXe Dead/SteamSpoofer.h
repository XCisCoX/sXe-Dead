#pragma once
#include "Includes.h"
//Set Steam
#define SECCUSS_SET_STEAM	    0x0
#define CANT_FIND_CS_HANDLE		0x1
#define CANT_WRITE_PROCESS	    0x2
#define IS_BIG_NUMBER		    0x3
#define FRIST_NUMBER_ZERO		0x4
#define IS_NOT_NUMBER			0x5
#define IS_NOT_STANDARD			0x6
#define IS_SMALL_NUMBER			0x7
#define IS_EMPTY_STRING			0x8

int SteamChanger(DWORD ProcesId,DWORD baseAddress, char *newSteam);
#define STEAM_CHANGER(address,Steam) SteamChanger(pId,(address),(Steam))