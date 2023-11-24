#ifndef BASEWINDOW_HPP
#define BASEWINDOW_HPP

#include "BaseWIndow.h"

template <class DERIVED_TYPE>
LRESULT CALLBACK BaseWindow<DERIVED_TYPE>::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    DERIVED_TYPE* pThis = NULL;
    State* state = nullptr;
    if (uMsg == WM_NCCREATE)
    {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

        pThis->m_hwnd = hwnd;
    }
    else
    {
        pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    if (pThis)
    {
        return pThis->HandleMessage(uMsg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

template <class DERIVED_TYPE>
BaseWindow<DERIVED_TYPE>::BaseWindow() : m_hwnd(NULL) {}

template <class DERIVED_TYPE>
BOOL BaseWindow<DERIVED_TYPE>::Create(const State* state, DWORD dwStyle, DWORD dwExStyle, int x, int y,
    int nWidth, int nHeight, HWND hWndParent, HMENU hMenu)
{   

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"MainWindow";
    
    RegisterClass(&wc);

    m_hwnd = CreateWindowEx(
        dwExStyle, L"MainWindow", state->m_title, dwStyle, state->m_position.first,
        state->m_position.second, state->m_size.first, state->m_size.second, hWndParent, hMenu, GetModuleHandle(NULL), this
    );

    if (m_hwnd)
    {
        std::cout << "Window created" << std::endl;
        ShowWindow(m_hwnd, SW_SHOW);

        return TRUE;
    }
    else
    {
        return FALSE;
    } 

}

template <class DERIVED_TYPE>
HWND BaseWindow<DERIVED_TYPE>::Window() const
{
    return m_hwnd;
}

#endif //BASEWINDOW_HPP