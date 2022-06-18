#include "Theme.h"

LRESULT OnPaint(HWND hWnd)
{

	PAINTSTRUCT ps;
	HDC hDC = BeginPaint(hWnd, &ps);
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	FillRect(hDC, &clientRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
	EndPaint(hWnd, &ps);
	return NULL;
}


void SetWindowSeven(HWND hWnd)
{
	const HINSTANCE hModule = LoadLibrary(TEXT("user32.dll"));
	if (hModule)
	{
		struct ACCENTPOLICY
		{
			int nAccentState;
			int nFlags;
			int nColor;
			int nAnimationId;
		};
		struct WINCOMPATTRDATA
		{
			int nAttribute;
			PVOID pData;
			ULONG ulDataSize;
		};
		typedef BOOL(WINAPI*pSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);
		const pSetWindowCompositionAttribute SetWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(hModule, "SetWindowCompositionAttribute");
		if (SetWindowCompositionAttribute)
		{

			ACCENTPOLICY policy = { 3, 0, 0, 0 };
			WINCOMPATTRDATA data = { 11, &policy, sizeof(ACCENTPOLICY) }; // WCA_ACCENT_POLICY=19
			//11 =Win 7
			SetWindowCompositionAttribute(hWnd, &data);
		}
		FreeLibrary(hModule);
	}
}

void SetOpacity(HWND hwnd, UINT nAlpha)//nAlpha Max =255
{
	HMODULE hUser32 = GetModuleHandle(_T("USER32.DLL"));
	typedef BOOL(WINAPI *lpfn) (HWND hWnd, COLORREF cr, BYTE bAlpha, DWORD dwFlags);
	lpfn pSetLayeredWindowAttributes;
	pSetLayeredWindowAttributes =
		(lpfn)GetProcAddress(hUser32, "SetLayeredWindowAttributes");
	if (!pSetLayeredWindowAttributes) return;
	LONG nStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
	if ((nStyle | 0x00080000) != nStyle)
		::SetWindowLong(hwnd, GWL_EXSTYLE, nStyle ^ 0x00080000);
	pSetLayeredWindowAttributes(hwnd, 0, (BYTE)(nAlpha), 0x00000002);
	::RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
}

BOOL DrawTextComposited(HTHEME hTheme, int iPartId, int iStateId,
	HDC hdc, LPCWSTR lpszText, int cchText, UINT uFormat, LPRECT lpRect, INT nGlow) // by Napalm
{
	HDC hdcMem;
	INT ndcMem;

	hdcMem = CreateCompatibleDC(hdc);
	if (!hdcMem) return FALSE;
	ndcMem = SaveDC(hdcMem);

	INT nWidth = (lpRect->right - lpRect->left);
	INT nHeight = (lpRect->bottom - lpRect->top);
	RECT rcRel = { 0, 0, nWidth, nHeight };
	BITMAPINFO bmInfo = { {
		sizeof(BITMAPINFOHEADER), nWidth, -nHeight, 1, 32, BI_RGB,
	} };
	HBITMAP hbmMem = CreateDIBSection(hdc, &bmInfo, DIB_RGB_COLORS, 0, 0, 0);
	if (!hbmMem) {
		RestoreDC(hdcMem, ndcMem);
		DeleteDC(hdcMem);
		return FALSE;
	}
	SelectObject(hdcMem, hbmMem);
	BitBlt(hdcMem, 0, 0, nWidth, nHeight, hdc, lpRect->left, lpRect->top, SRCCOPY);

	HFONT hFont = CreateFont(17,
		0,
		0,
		0,
		FW_DONTCARE,
		FALSE,
		FALSE,						  // Creating New Font
		FALSE,
		ANSI_CHARSET,
		OUT_TT_PRECIS,
		CLIP_TT_ALWAYS,
		DEFAULT_QUALITY,
		FF_DONTCARE,
		L"tahoma"
	);
	if (hFont) SelectObject(hdcMem, hFont);
	SetBkMode(hdcMem, TRANSPARENT);
	SetTextColor(hdcMem, GetTextColor(hdc));

	BOOL bThemedText = FALSE;
	if (hTheme) {
		HMODULE hUxTheme = LoadLibrary(TEXT("UxTheme.dll"));
		if (hUxTheme) {
			HRESULT(WINAPI *Dyn_DrawThemeTextEx)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId,
				LPCWSTR lpszText, int cchText, DWORD dwTextFlags, LPRECT lpRect, const PDTTOPTS pOptions);
			*(FARPROC *)&Dyn_DrawThemeTextEx = GetProcAddress(hUxTheme, "DrawThemeTextEx");
			if (Dyn_DrawThemeTextEx) {
				DTTOPTS dtto = { sizeof(dtto), DTT_COMPOSITED | DTT_GLOWSIZE };
				dtto.iGlowSize = nGlow;
				bThemedText = SUCCEEDED(Dyn_DrawThemeTextEx(hTheme, hdcMem, iPartId, iStateId,
					lpszText, cchText, uFormat, &rcRel, &dtto));
			}
			else {
				bThemedText = SUCCEEDED(DrawThemeText(hTheme, hdcMem, iPartId, iStateId,
					lpszText, cchText, uFormat, 0, &rcRel));
			}
			FreeLibrary(hUxTheme);
		}

	}
	if (!bThemedText) {
		DrawText(hdcMem, lpszText, cchText, &rcRel, uFormat);
	}

	BitBlt(hdc, lpRect->left, lpRect->top, nWidth, nHeight, hdcMem, 0, 0, SRCCOPY);
	RestoreDC(hdcMem, ndcMem);
	DeleteObject(hbmMem);
	DeleteDC(hdcMem);

	return TRUE;
}

HRESULT Aero(HWND hWnd,int Left,int Right,int Bottom,int Top)
{
	HRESULT hr = S_OK;
	MARGINS margins = { Left,Right,Bottom,Top };
	//hr = DwmExtendFrameIntoClientArea(hWnd, &margins);

	if (SUCCEEDED(DwmExtendFrameIntoClientArea(hWnd, &margins)))
	{
		return hr;
	}
	return hr;
}

HBRUSH CreateGradientBrush(COLORREF top, COLORREF bottom, LPNMCUSTOMDRAW item)
{
	HBRUSH Brush = NULL;
	HDC hdcmem = CreateCompatibleDC(item->hdc);
	HBITMAP hbitmap = CreateCompatibleBitmap(item->hdc, item->rc.right - item->rc.left, item->rc.bottom - item->rc.top);
	SelectObject(hdcmem, hbitmap);
	int r1 = GetRValue(top), r2 = GetRValue(bottom), g1 = GetGValue(top), g2 = GetGValue(bottom), b1 = GetBValue(top), b2 = GetBValue(bottom);
	for (int i = 0; i < item->rc.bottom - item->rc.top; i++)
	{
		RECT temp;
		int r, g, b;
		r = int(r1 + double(i * (r2 - r1) / item->rc.bottom - item->rc.top));
		g = int(g1 + double(i * (g2 - g1) / item->rc.bottom - item->rc.top));
		b = int(b1 + double(i * (b2 - b1) / item->rc.bottom - item->rc.top));
		Brush = CreateSolidBrush(RGB(r, g, b));
		temp.left = 0;
		temp.top = i;
		temp.right = item->rc.right - item->rc.left;
		temp.bottom = i + 1;
		FillRect(hdcmem, &temp, Brush);
		DeleteObject(Brush);
	}
	HBRUSH pattern = CreatePatternBrush(hbitmap);
	DeleteDC(hdcmem);
	DeleteObject(Brush);
	DeleteObject(hbitmap);
	return pattern;
}

void SetWindowBlur(HWND hWnd)
{
	const HINSTANCE hModule = LoadLibrary(TEXT("user32.dll"));
	if (hModule)
	{
		struct ACCENTPOLICY
		{
			int nAccentState;
			int nFlags;
			int nColor;
			int nAnimationId;
		};
		struct WINCOMPATTRDATA
		{
			int nAttribute;
			PVOID pData;
			ULONG ulDataSize;
		};
		typedef BOOL(WINAPI*pSetWindowCompositionAttribute)(HWND, WINCOMPATTRDATA*);
		const pSetWindowCompositionAttribute SetWindowCompositionAttribute = (pSetWindowCompositionAttribute)GetProcAddress(hModule, "SetWindowCompositionAttribute");
		if (SetWindowCompositionAttribute)
		{
			ACCENTPOLICY policy = { 2, 1, 1, 1 }; // ACCENT_ENABLE_BLURBEHIND=3...
			WINCOMPATTRDATA data = { 19, &policy, sizeof(ACCENTPOLICY) }; // WCA_ACCENT_POLICY=19
			SetWindowCompositionAttribute(hWnd, &data);
		}
		//FreeLibrary(hModule);
	}
}