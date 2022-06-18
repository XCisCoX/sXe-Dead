#include "Includes.h"
#pragma comment (lib, "Dwmapi.lib")
#include <dwmapi.h>
#pragma comment (lib, "uxtheme.lib")
HBRUSH CreateGradientBrush(COLORREF top, COLORREF bottom, LPNMCUSTOMDRAW item);
HRESULT Aero(HWND hWnd, int Left, int Right, int Bottom, int Top);
LRESULT OnPaint(HWND hWnd);
void SetWindowBlur(HWND hWnd);
void SetOpacity(HWND hwnd, UINT nAlpha);//nAlpha Max =255;
void SetWindowSeven(HWND hWnd);
BOOL DrawTextComposited(HTHEME hTheme, int iPartId, int iStateId,
	HDC hdc, LPCWSTR lpszText, int cchText, UINT uFormat, LPRECT lpRect, INT nGlow);