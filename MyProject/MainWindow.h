#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "BaseWindow.h"
#include <thread>


class MainWindow : public BaseWindow<MainWindow>
{
private:
    COLORREF ParseColorString(PCWSTR color);
public:
    //Constructors and Destructor
    MainWindow();//default constructor
    MainWindow(PCWSTR title);//Constructor with title
    MainWindow(int x, int y);//Constructor with position
    MainWindow(PCWSTR title, PCWSTR color);//Constructor with title and color
    MainWindow(int width, int height, int x, int y, PCWSTR title, PCWSTR color);//Constructor with width, heigth, position, title and color
    ~MainWindow();//Destructor

    void Maximize();//Maximize the window size to fill full screen
    void Minimize();//Minimize the window size(hide the window)

    void SetTitle(PCWSTR title);//Rename already created window's title
    void SetBackgroundColor(PCWSTR color);//Change already created window's background color
    void MoveWindowTo(int leftside, int topside);//Move window to given position
    void ResizeWindow(int width, int height);//Set windows size to given size

    std::pair<int, int> GetSize();
    std::pair<int, int> GetPos();
    COLORREF GetColor();
    PCWSTR GetTitle();

    void RunMessageLoop();//Starts the message loop
    PCWSTR  ClassName() const;
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;//Function that handles all messages sent to the window
private:
    State* m_state;//Struct which contains window's title's, position's, size's and background color's current state
};

#endif //MAINWINDOW_H
