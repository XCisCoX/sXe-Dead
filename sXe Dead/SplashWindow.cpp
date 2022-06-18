#include "SplashWindow.h"
#include "resource.h"
#include <time.h>
const LPCWSTR SW_CLASSNAME = L"CISCO_X_SPLASH";
LRESULT CALLBACK SplashWindow_WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
HRGN CreateRgnFromBitmap(HBITMAP hBmp, COLORREF color, HWND hwnd);
SplashWindow::SplashWindow ()
{
	clearMembers ();
}
SplashWindow::SplashWindow (LPCSTR bitmapFileName, const int r, const int g, const int b)
{
	clearMembers ();
	createSplashWindow (bitmapFileName, r, g, b);
}

SplashWindow::SplashWindow (DWORD bitmapResourceID, const int r, const int g, const int b)
{
	clearMembers ();
	createSplashWindow (bitmapResourceID, r, g, b);
}
	
SplashWindow::~SplashWindow ()
{
	destroySplashWindow ();
}

void SplashWindow::showModalWindow (DWORD minDisplayTime)
{
	if (!isValidWindow ())
	{
		return;
	}
	MSG msg;
	BOOL gotMSG;
	HANDLE threadHandle;
	DWORD threadID;
	SECURITY_ATTRIBUTES sa;
	bool isThreadFinished = false;
	mMinDisplayTime = minDisplayTime;
	ZeroMemory (&msg, sizeof (MSG));
	ZeroMemory (&sa, sizeof (SECURITY_ATTRIBUTES));
	sa.nLength = sizeof (SECURITY_ATTRIBUTES);
	InitializeCriticalSection (&mLock);
	threadHandle = CreateThread (&sa, 0, SplashWindow_ThreadProc, this, 0, &threadID);
	mThreadFinished = isThreadFinished = false;
	UpdateWindow (mHWND);
	ShowWindow (mHWND, SW_SHOW);


	while (true)
	{
		gotMSG = PeekMessage (&msg, 0L, 0L, 0L, PM_REMOVE);
		EnterCriticalSection (&mLock);
		isThreadFinished = mThreadFinished;
		LeaveCriticalSection (&mLock);
		if (isThreadFinished)
		{
			break;
		}
		if (gotMSG)
		{
			if (msg.message == WM_PAINT)
			{
				PAINTSTRUCT paint;
				HDC dc = BeginPaint (mHWND, &paint);
				HDC memDC = CreateCompatibleDC(dc); 
				SelectObject(memDC,mBitmap);
				BitBlt(dc,0,0,mBitmapWidth,mBitmapHeight,memDC,0,0,SRCCOPY); 	
				DeleteObject (dc);
			}
			else
			{
				TranslateMessage (&msg);
				DispatchMessage (&msg);
			}

		}
		
	}
	CloseHandle (threadHandle);
	DeleteCriticalSection (&mLock);
	destroySplashWindow ();
}

bool SplashWindow::createSplashWindow (LPCSTR bitmapFileName, const int r, const int g, const int b)
{
	mBitmap = (HBITMAP)LoadImageA (
		GetModuleHandle (0),bitmapFileName,
								IMAGE_BITMAP,0,0, LR_LOADFROMFILE);
	if (mBitmap == 0L)
	{
		return false;
	}
	return createWindowHelper (r, g, b);
}

bool SplashWindow::createSplashWindow (DWORD bitmapResourceID, const int r, const int g, const int b)
{
	mBitmap = (HBITMAP)LoadImage (GetModuleHandle (0L),
								MAKEINTRESOURCE (bitmapResourceID),
								IMAGE_BITMAP,
								0,
								0, 
								LR_DEFAULTCOLOR);
	if (mBitmap == 0L)
	{
		return false;
	}

	return createWindowHelper (r, g, b);
}

bool SplashWindow::isValidWindow () const
{
	return mHWND != 0L;
}

HWND SplashWindow::getHWND () const
{
	return mHWND;
}

void SplashWindow::loadResources () const
{

}

bool SplashWindow::createWindowHelper (const int r, const int g, const int b)
{
	if (!mBitmap)
	{
		return false;
	}
	BITMAP bm;
	int x, y;
	WNDCLASS wc; 
	wc.lpfnWndProc = SplashWindow_WndProc;
	wc.lpszClassName = SW_CLASSNAME;
	wc.hInstance = GetModuleHandle (0L);
	wc.style = 0;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)GetStockObject (WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.hIcon = NULL;

	if (!RegisterClass(&wc))
	{
		DeleteObject (mBitmap);
		clearMembers ();
		return false;
	}

	mHWND = CreateWindowEx (WS_EX_TOOLWINDOW | WS_EX_TOPMOST, 
							wc.lpszClassName,
							L"sXe Dead V2.0 Splash",
							WS_POPUP,
							0,
							0,
							0,
							0,
							HWND_DESKTOP,
							0L,
							wc.hInstance,
							0L);

	if (!isValidWindow ())
	{
		destroySplashWindow ();
		return false;
	}
	GetObject(mBitmap, sizeof(bm), &bm);
	mBitmapWidth = bm.bmWidth;
	mBitmapHeight = bm.bmHeight;
	x =(GetSystemMetrics(SM_CXFULLSCREEN)-mBitmapWidth)/2;
	y =(GetSystemMetrics(SM_CYFULLSCREEN)-mBitmapHeight)/2;
	MoveWindow (mHWND, x, y, mBitmapWidth, mBitmapHeight, FALSE);
	if (r != -1 && g != -1 && b != -1)
	{
		HRGN region = CreateRgnFromBitmap (mBitmap, RGB(r,g,b), mHWND);		
		if (FAILED (SetWindowRgn (mHWND, region, TRUE)))
		{
			destroySplashWindow ();
			return false;
		}
	}
	return true;
}

void SplashWindow::clearMembers ()
{
	mHWND = 0L;
	mBitmap = 0L;
	mBitmapWidth = mBitmapHeight = 0;
	mMinDisplayTime = 0;
	mThreadFinished = true;
}

void SplashWindow::destroySplashWindow ()
{
	DestroyWindow (mHWND);
	DeleteObject (mBitmap);
	clearMembers ();
	UnregisterClass (SW_CLASSNAME, GetModuleHandle (0L));
}

HRGN CreateRgnFromBitmap(HBITMAP hBmp, COLORREF color, HWND hwnd)
{
	if (!hBmp) return NULL;
	BITMAP bm;
	GetObject( hBmp, sizeof(BITMAP), &bm );
	HDC windowHDC = GetDC(hwnd);	
	HDC hdc = CreateCompatibleDC(windowHDC);
	SelectObject(hdc, hBmp);	
	const DWORD RDHDR = sizeof(RGNDATAHEADER);
	const DWORD MAXBUF = 40;	
	LPRECT	pRects;								
	DWORD	cBlocks = 0;	
	INT		i, j;				
	INT		first = 0;				
	bool	wasfirst = false;		
	bool	ismask;				
	RGNDATAHEADER* pRgnData = (RGNDATAHEADER*)new BYTE[ RDHDR + ++cBlocks * MAXBUF * sizeof(RECT) ];
	memset( pRgnData, 0, RDHDR + cBlocks * MAXBUF * sizeof(RECT) );
	pRgnData->dwSize	= RDHDR;
	pRgnData->iType		= RDH_RECTANGLES;
	pRgnData->nCount	= 0;
	for ( i = 0; i < bm.bmHeight; i++ )
		for ( j = 0; j < bm.bmWidth; j++ ){
			ismask=(GetPixel(hdc, j,bm.bmHeight-i-1)!=color);
			if (wasfirst && ((ismask && (j==(bm.bmWidth-1)))||(ismask ^ (j<bm.bmWidth)))){
				pRects = (LPRECT)((LPBYTE)pRgnData + RDHDR);
				SetRect (&pRects[ pRgnData->nCount++ ], first, bm.bmHeight - i - 1, j+(j==(bm.bmWidth-1)), bm.bmHeight - i );
				if ( pRgnData->nCount >= cBlocks * MAXBUF ){
					LPBYTE pRgnDataNew = new BYTE[ RDHDR + ++cBlocks * MAXBUF * sizeof(RECT) ];
					memcpy( pRgnDataNew, pRgnData, RDHDR + (cBlocks - 1) * MAXBUF * sizeof(RECT) );
					delete pRgnData;
					pRgnData = (RGNDATAHEADER*)pRgnDataNew;
				}
				wasfirst = false;
			} else if ( !wasfirst && ismask ){
				first = j;
				wasfirst = true;
			}
		}
		DeleteDC(hdc);	
		DeleteDC (windowHDC);
		HRGN hRgn=CreateRectRgn(0, 0, 0, 0);
		if ( hRgn == NULL )
		{
			return hRgn;
		}
		pRects = (LPRECT)((LPBYTE)pRgnData + RDHDR);
		for(i=0;i<(int)pRgnData->nCount;i++)
		{
			HRGN hr=CreateRectRgn(pRects[i].left, pRects[i].top, pRects[i].right, pRects[i].bottom);
			if (FAILED (CombineRgn(hRgn, hRgn, hr, RGN_OR)))
			{
				DeleteObject (hr);
				return hRgn;
			}

			if (hr) 
			{
				DeleteObject(hr);
			}
		}
		delete pRgnData;
		return hRgn;
}

DWORD WINAPI SplashWindow_ThreadProc (LPVOID parameter)
{
	SplashWindow* sw = (SplashWindow*)parameter;
	unsigned long startTime = (unsigned long)time (0L);
	unsigned long endTime = 0;
	DWORD threadLength;
	DWORD sleepTime;
	if (sw)
	{
		sw->loadResources ();

	}
	else
	{
		ExitThread (1);
		return 1;
	}
	endTime = (unsigned long)time (0L);
	threadLength = (DWORD)(endTime - startTime);
	sleepTime = sw->mMinDisplayTime - threadLength;
	PlaySoundA(MAKEINTRESOURCEA(IDR_WAVE2), GetModuleHandle(NULL), SND_RESOURCE | SND_MEMORY);
	if (sleepTime > 0)
	{
		Sleep (sleepTime);
	}
	EnterCriticalSection (&(sw->mLock));
		sw->mThreadFinished = true;
	LeaveCriticalSection (&(sw->mLock));
	ExitThread (0);
	return 0;
}

LRESULT CALLBACK SplashWindow_WndProc (HWND hwnd, UINT message, WPARAM wParam, 
						   LPARAM lParam)
{
	return DefWindowProc (hwnd, message, wParam, lParam);
}