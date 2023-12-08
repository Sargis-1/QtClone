#ifndef BASEWINDOW_H
#define BASEWINDOW_H
#include <windows.h>
#include <iostream>
#include <algorithm>
#include <unordered_map>

struct State {
    PCWSTR m_title = L"DefTitle";//Default title
    std::pair<int, int> m_position = std::make_pair((GetSystemMetrics(SM_CXSCREEN) - 650) / 2,
        (GetSystemMetrics(SM_CYSCREEN) - 400) / 2);//Default position//First - X coordinates->//Second - Y coordinates to bottom 
    std::pair<int, int> m_size = std::make_pair(650, 400);//Default size//First - width, Second - height
    COLORREF m_backgroundcolor = RGB(255, 255, 255);
    HWND m_parent = NULL;
    int m_bordersize = 15;
    COLORREF m_bordercolor = m_backgroundcolor;
};


template <class DERIVED_TYPE>
class BaseWindow
{
public:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//Procedure which is responsible 
    //for all operations related to the window
    BaseWindow();//Default constructor

    BOOL Create(//Function which actually creates the window
        const State* state,//State pointer received from derived class
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = 300,
        int y = 250,
        int nWidth = 650,
        int nHeight = 400,
        HWND hWndParent = 0,
        HMENU hMenu = 0
    );

    HWND Window() const;//Returns the window handle

    virtual ~BaseWindow();
protected:
    virtual PCWSTR  ClassName() const = 0;
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;//Derived class's window procedure
    //Must be implemented in Derived class

    HWND m_hwnd;//Window handler
};

#include "BaseWindow.hpp"

#endif //BASEWINDOW_H