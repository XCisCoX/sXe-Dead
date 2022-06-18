#pragma once
#include "Includes.h"
static HWND lable1, lable2, lable3, btnExit, btnSetSteam,
btnAbout, txtSetSteam, prgSteam, btnRandomsteam, ComboBox,
GroupBoxSteam, btnAntiSs, GroupBoxSs, btnSetHWID
, CheckBoxAIO, btnInjectCheat, GroupBoxsXe,
txtSxe1, txtSxe2, txtSxe3, lblSxe1, lblSxe2, lblSxe3,
btnRandomHwid, GroupBoxAlias, CheckBoxAlias, ComboAntiSs, lblSendMessage;
void ThemeButton(LPARAM lParam);
static HFONT  hFontVerdana;
void InitGui(LPARAM lParam);
static HINSTANCE hInst;
#define IDT_TIMER1 0x242
#define EXIT_APP 0x1
#define SET_STEAM 0x2
#define TXT_STEAM 0x3
#define TXT_SXE1 0x123
#define TXT_SXE2 0x1632
#define TXT_SXE3 0x125
#define PROG_STEAM 0x4
#define BTN_RANDOM_STEAM 0x5
#define BTN_SET_HWID 0x9
#define BTN_ANTI_SS 0x7
#define BTN_ABOUT 0x10
#define CHECK_CS_VER 0x6
#define INJECT_CHEAT 0x12
#define BTN_RANDOM_HWID 0x21
#define CHECK_ALAIS 0x124
#define CHECK_AIO 0x1521
#define COMBO_SS 0x4215
#define LABLE_SEND 0x4324