#include "Button.h"


int main()
{
    //MainWindow win;
    //MainWindow win(L"Some name");
    //MainWindow win(0, 0);s
    //MainWindow win(L"My window", L"green");
    MainWindow win(800, 600, 500, 150, L"My window", L"green");
    
    

    //Button b(win);
    //Button b(win, L"Don't Click");
    //Button b(win, 300, 400);
    //Button b(win, {0, 0});
    //Button b(win, 300, 500, {250, 250});
    //Button b(win, L"Click", L"gold");
    //Button b(win, L"Click", L"blue", 300, 500, { 250, 250 });
    Button b(win, L"Click", L"gold");
    //Write border related methods, button's message loop, button's OnClick method

    //std::thread wint(&MainWindow::RunMessageLoop, &win);/*fix this moments*/
    //std::thread bt(&Button::RunMessageLoop, &b);/*fix this moments*/

    //Button b2(win, L"Second button", L"gray", 200 ,40 , {0, 0});
    b.SetBorder(10, L"purple");

    b.SetOnClick([&win]() {win.Maximize(); });
    //Sleep(1000);
    
    

   /* Sleep(1000);
    b.ResizeButton(300, 100);
    Sleep(1000);*/
   /* b.SetBorder(15, L"blue");
    Sleep(1000);
    b.SetBackgroundColor(L"purple");*/
   /* Sleep(1000);
    b.SetTitle(L"Don't click");
    Sleep(1000);
    b.MoveButtonTo(0, 0);*/
    
    /*Sleep(1000);
    win.Maximize();
    Sleep(1000);
    win.Minimize();
    Sleep(1000);
    win.Maximize();
    Sleep(1000);
    win.SetBackgroundColor(L"gold");
    Sleep(1000);
    win.SetTitle(L"new name");
    Sleep(1000);
    win.ResizeWindow(800, 800);
    Sleep(1000);
    win.MoveWindowTo(600, 300);*/

    //win.RunMessageLoop();
    
    //bt.join();
    //wint.join();
    win.RunMessageLoop();
    return 0;
}
