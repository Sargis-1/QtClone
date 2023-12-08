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
BaseWindow<DERIVED_TYPE>::BaseWindow() : m_hwnd(NULL) {
    std::cout << "Base ctr" << std::endl;
}

template <class DERIVED_TYPE>
BOOL BaseWindow<DERIVED_TYPE>::Create(const State* state, DWORD dwStyle, DWORD dwExStyle, int x, int y,
    int nWidth, int nHeight, HWND hWndParent, HMENU hMenu)
{   

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = DERIVED_TYPE::WindowProc;//Initializes window's window procedure
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = ClassName();//Initializes class's name

    RegisterClass(&wc);//Registeres class

    m_hwnd = CreateWindowEx(//Creates window and returns it's handler, receives - style, class's name, title, position, size, parent's handler, Menu type, Inatance handelr, This pointer
        dwExStyle, ClassName(), state->m_title, dwStyle, state->m_position.first,
        state->m_position.second, state->m_size.first, state->m_size.second, state->m_parent, hMenu/*null for button*/, (HINSTANCE)GetWindowLongPtr(state->m_parent, GWLP_HINSTANCE), this
    );

    if (m_hwnd)
    {
        //std::cout << ClassName() << " type of obejct was created" << std::endl;
        ShowWindow(m_hwnd, SW_SHOW);//Shows the window id it was successfully created

        return TRUE;
    }
    else
    {
        std::cout << "Couldn't create a window" << std::endl;
        return FALSE;
    } 

}

template <class DERIVED_TYPE>
HWND BaseWindow<DERIVED_TYPE>::Window() const
{
    return m_hwnd;
}

template<class DERIVED_TYPE>
inline BaseWindow<DERIVED_TYPE>::~BaseWindow()
{
    UnregisterClass(L"MainWindow", GetModuleHandle(NULL));
    std::cout << "Base Destructor" << std::endl;
}


#endif //BASEWINDOW_HPP