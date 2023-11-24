#ifndef BASEWINDOW_H
#define BASEWINDOW_H
#include <windows.h>
#include <iostream>


struct State {
    PCWSTR m_title = L"DefTitle";
    std::pair<int, int> m_position = std::make_pair((GetSystemMetrics(SM_CXSCREEN) - 650) / 2,
        (GetSystemMetrics(SM_CYSCREEN) - 400) / 2);
    std::pair<int, int> m_size = std::make_pair(650, 400);
    COLORREF m_backgroundcolor = RGB(255, 255, 255);
};


template <class DERIVED_TYPE>
class BaseWindow
{
public:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    BaseWindow();

    BOOL Create(
        const State* state,
        DWORD dwStyle,
        DWORD dwExStyle = 0,
        int x = 300,
        int y = 250,
        int nWidth = 650,
        int nHeight = 400,
        HWND hWndParent = 0,
        HMENU hMenu = 0
    );

    HWND Window() const;

protected:
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

    HWND m_hwnd;
};

#include "BaseWindow.hpp"

#endif //BASEWINDOW_H