#ifdef WIN32

#include <windows.h>
#include <gdiplus.h>
#include <resource.hpp>

#define WM_ICONSYSTRAY WM_USER

NOTIFYICONDATA icone;
char version[16];
TCHAR WindowTitle[20];
HWND hWnd;
HMENU Hmenu;
WNDCLASS wc;

void intHandler(int);

void win32_unNOTIFYICON()
{
  Shell_NotifyIcon(NIM_DELETE, &icone);
  UpdateWindow(hWnd);
  UnregisterClass(WindowTitle, wc.hInstance);
}

// Window procedure for our main window.
LRESULT CALLBACK MainWin_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
	case WM_ICONSYSTRAY:
		switch (LOWORD(lParam))
		{
			case WM_RBUTTONDOWN:
			{
				POINT curPoint ;
				GetCursorPos( &curPoint ) ;
				UINT clicked = TrackPopupMenu(Hmenu,TPM_RETURNCMD | TPM_NONOTIFY,curPoint.x,curPoint.y,0,hWnd,NULL);
				SendMessage(hWnd, WM_NULL, 0, 0); // send benign message to window to make sure the menu goes away.
				if (clicked == 1000) {
					intHandler(0);
					PostMessage(hWnd, WM_QUIT, 0, 0);
				}
				return 0;
			}
		}
		break;

	case WM_CREATE:
		Hmenu = CreatePopupMenu();
			AppendMenu(Hmenu, MF_STRING, 1001, WindowTitle);
			AppendMenu(Hmenu, MF_SEPARATOR, 0, NULL);
			AppendMenu(Hmenu, MF_STRING, 1000, L"Quit");
		break;
  }
  return DefWindowProc(hWnd, msg, wParam, lParam);
}

int win32_NOTIFYICON()
{
  MSG msg;

  LoadStringA(GetModuleHandle(NULL), STR_VERSION, version, 16);
  LoadString(GetModuleHandle(NULL), WINDOW_TITLE, WindowTitle, 20);
  
  // Class for our main window.
  wc.style         = CS_DBLCLKS;
  wc.lpfnWndProc   = &MainWin_WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = GetModuleHandle(NULL);
  wc.hIcon         = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_ICON_App));
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = WindowTitle;

  // Register our window classes, or error.
  RegisterClass(&wc);
  
  hWnd = CreateWindowEx( WS_EX_LAYERED, WindowTitle, WindowTitle, WS_POPUP | WS_MINIMIZEBOX, 0, 0, 1, 1, NULL, NULL, wc.hInstance, NULL);
  ShowWindow(hWnd, SW_HIDE);
  UpdateWindow(hWnd);

  icone.cbSize = sizeof(icone);
  icone.uID = IDI_ICON_App;
  icone.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
  icone.uCallbackMessage = WM_ICONSYSTRAY;
  wcsncpy_s(icone.szTip, WindowTitle, wcslen(WindowTitle));
  icone.hWnd = hWnd;
  icone.hIcon = wc.hIcon;//LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_ICON_App));
  Shell_NotifyIcon(NIM_ADD, &icone);
  UpdateWindow(hWnd);

  // Main message loop.
  while(GetMessage(&msg, NULL, 0, 0) > 0)
  {
    if (! TranslateAccelerator(msg.hwnd, NULL, &msg))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return (int) msg.wParam;
}

#endif
