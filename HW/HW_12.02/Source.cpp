#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <map>

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst1;
std::map<int, HWND> statics;
int rectCount = 0;

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
    hInst1 = hInst;
    MSG msg;
    HWND hDialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
    ShowWindow(hDialog, nCmdShow);
    while (GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp)
{
    switch (mes)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        PostQuitMessage(0);
        return TRUE;
    case WM_LBUTTONDBLCLK:
    {
        if (!statics.empty())
        {
            DestroyWindow(statics.begin()->second);
            statics.erase(statics.begin());
            return TRUE;
        }
    }
    break;
    case WM_LBUTTONDOWN:
    {        int startX = LOWORD(lp);
        int startY = HIWORD(lp);
        int endX = startX + 50;
        int endY = startY + 50;

        rectCount++;
        TCHAR str[10];
        wsprintf(str, TEXT("%d"), rectCount);
        HWND mystatic = CreateWindowEx(0, TEXT("STATIC"), str,
            WS_CHILD | WS_VISIBLE | SS_CENTER | WS_BORDER,
            startX, startY, 50, 50, hWnd, 0, hInst1, 0);
        statics[rectCount] = mystatic;
    }
    break;
    }
    return FALSE;
}
