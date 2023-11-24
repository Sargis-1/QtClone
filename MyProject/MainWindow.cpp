#include "MainWindow.h"


COLORREF MainWindow::ParseColorString(PCWSTR color)
{   
    // Convert colorString to lowercase for case-insensitive comparison
    std::wstring lowercaseColorString = color;
    std::transform(lowercaseColorString.begin(), lowercaseColorString.end(), lowercaseColorString.begin(), towlower);

    std::unordered_map<std::wstring, COLORREF> colors;

    colors[L"white"]   = RGB(255, 255, 255);
    colors[L"red"]     = RGB(255, 0, 0);
    colors[L"green"]   = RGB(60, 179, 113);
    colors[L"blue"]    = RGB(0, 0, 255);
    colors[L"yellow"]  = RGB(255, 255, 0);
    colors[L"purple"]  = RGB(128, 0, 128);
    colors[L"orange"]  = RGB(255, 165, 0);
    colors[L"black"]   = RGB(0, 0, 0);
    colors[L"gray"]    = RGB(128, 128, 128);
    colors[L"brown"]   = RGB(165, 42, 42);
    colors[L"pink"]    = RGB(255, 182, 193);
    colors[L"cyan"]    = RGB(0, 255, 255);
    colors[L"magenta"] = RGB(255, 0, 255);
    colors[L"silver"]  = RGB(192, 192, 192);
    colors[L"gold"]    = RGB(255, 215, 0);

    return colors[lowercaseColorString];
}


MainWindow::MainWindow() : m_state(new State) {
    Create(m_state, WS_OVERLAPPEDWINDOW);
    UpdateWindow(m_hwnd);
}

MainWindow::MainWindow(PCWSTR title) : m_state(new State){
    m_state->m_title = title;
    Create(m_state, WS_OVERLAPPEDWINDOW);
    UpdateWindow(m_hwnd);
}

MainWindow::MainWindow(int x, int y) : m_state(new State)
{
    m_state->m_position = std::make_pair(x, y);
    Create(m_state, WS_OVERLAPPEDWINDOW);
    UpdateWindow(m_hwnd);
}

MainWindow::MainWindow(PCWSTR title, PCWSTR color): m_state(new State){
    m_state->m_title = title;
    m_state->m_backgroundcolor = ParseColorString(color);

    Create(m_state, WS_OVERLAPPEDWINDOW);
    UpdateWindow(m_hwnd);
}

MainWindow::MainWindow(int width, int height, int x, int y, PCWSTR title, PCWSTR color) : m_state(new State)
{
    m_state->m_title = title;
    m_state->m_backgroundcolor = ParseColorString(color);
    m_state->m_position = std::make_pair(x, y);
    m_state->m_size = std::make_pair(width, height);
    Create(m_state, WS_OVERLAPPEDWINDOW);
    UpdateWindow(m_hwnd);
}

MainWindow::~MainWindow()
{
    delete m_state;
    std::cout << "Window destroyed" << std::endl;
}

void MainWindow::Maximize()
{
    ShowWindow(m_hwnd, SW_MAXIMIZE);
    UpdateWindow(m_hwnd);
}

void MainWindow::Minimize()
{
    ShowWindow(m_hwnd, SW_MINIMIZE);
    UpdateWindow(m_hwnd);
}

void MainWindow::SetTitle(PCWSTR title)
{
    SetWindowTextW(m_hwnd, title);
}

void MainWindow::SetBackgroundColor(PCWSTR color)
{
    m_state->m_backgroundcolor = ParseColorString(color);
    //Force a repaint of the window to apply the new background color
    SetBkColor(GetDC(m_hwnd), m_state->m_backgroundcolor);
    RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
    UpdateWindow(m_hwnd);
}

void MainWindow::MoveWindowTo(int leftside, int topside)
{
    // Move the window to the specified coordinates without changing size and Z order
    SetWindowPos(m_hwnd, NULL, leftside, topside, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void MainWindow::ResizeWindow(int width, int height)
{
    SetWindowPos(m_hwnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
}


LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);

        HBRUSH hBrush = CreateSolidBrush(m_state->m_backgroundcolor);

        FillRect(hdc, &ps.rcPaint, hBrush);

        EndPaint(m_hwnd, &ps);

        return 0;
    }case WM_SYSCOMMAND:
    {
        switch (wParam & 0xFFF0)
        {
        case SC_MAXIMIZE:
            Maximize();
            break;
        case SC_MINIMIZE:
            Minimize();
            break;
        default:
            return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
        }
        break;
    }
    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }

    return TRUE;
}
