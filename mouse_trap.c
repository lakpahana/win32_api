#include <windows.h>

#define IDT_MOUSETRAP 1

HICON hIcon1;
POINT ptOld;
UINT uResult;
HINSTANCE hinstance;

wc.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(400));
wc.hCursor = LoadCursor(hinstance, MAKEINTRESOURCE(200));

GetCursorPos(&ptOld);

uResult = SetTimer(hwnd,
                   IDT_MOUSETRAP,
                   10000,
                   (TIMERPROC)NULL);

if (uResult == 0)
{
    ErrorHandler("No timer is available.");
}

LONG APIENTRY MainWndProc(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam)
{

    HDC hdc;
    POINT pt;
    RECT rc;

    switch (message)
    {

    case WM_TIMER:

        if (IsIconic(hwnd))
        {
            GetCursorPos(&pt);

            if ((pt.x == ptOld.x) && (pt.y == ptOld.y))
            {
                GetWindowRect(hwnd, &rc);
                SetCursorPos(rc.left, rc.top);
            }
            else
            {
                ptOld.x = pt.x;
                ptOld.y = pt.y;
            }
        }

        return 0;

    case WM_DESTROY:

        KillTimer(hwnd, IDT_MOUSETRAP);
        PostQuitMessage(0);
        break;
    }