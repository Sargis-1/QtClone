#include "BaseWindow.h"
#include "MainWindow.h"


int main()
{
    //MainWindow win;
    //MainWindow win(L"Some name");
    //MainWindow win(0, 0);
    MainWindow win(L"My window", L"green");
    //MainWindow win(500, 500, 200, 200, L"My window", L"Yellow");
    Sleep(1000);
    win.Maximize();
    Sleep(1000);
    win.Minimize();
    Sleep(1000);
    win.Maximize();
    Sleep(1000);
    win.SetBackgroundColor(L"purple");
    Sleep(1000);
    win.SetTitle(L"new name");
    Sleep(1000);
    win.MoveWindowTo(50, 100);
    Sleep(1000);
    win.ResizeWindow(800, 800);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
