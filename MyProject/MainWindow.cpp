#include "MainWindow.h"


COLORREF MainWindow::ParseColorString(PCWSTR color)
{   
    // Convert colorString to lowercase for case-insensitive comparison
    std::wstring lowercaseColorString = color;
    std::transform(lowercaseColorString.begin(), lowercaseColorString.end(), lowercaseColorString.begin(), towlower);

    std::unordered_map<std::wstring, COLORREF> colors;//Used to return given colors RGB(COLORREF) value

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
    Create(m_state, WS_OVERLAPPEDWINDOW);//Creates window with given state and style
    UpdateWindow(m_hwnd);//To avoid bugs such as one method starts executions before previous method did not end it's execution
}

MainWindow::MainWindow(PCWSTR title) : m_state(new State){
    m_state->m_title = title;//Sets window's current title
    Create(m_state, WS_OVERLAPPEDWINDOW);//Same as default
    UpdateWindow(m_hwnd);
}

MainWindow::MainWindow(int x, int y) : m_state(new State)
{
    m_state->m_position = std::make_pair(x, y);//Sets window's position
    Create(m_state, WS_OVERLAPPEDWINDOW);//Same as default
    UpdateWindow(m_hwnd);
}

MainWindow::MainWindow(PCWSTR title, PCWSTR color): m_state(new State){
    m_state->m_title = title;//Sets window's current title
    m_state->m_backgroundcolor = ParseColorString(color);//Sets window's color
    std::cout << "Main ctr" << std::endl;
    Create(m_state, WS_OVERLAPPEDWINDOW | WS_SIZEBOX | WS_CAPTION | CS_HREDRAW | CS_VREDRAW);//Same as default
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
    delete m_state;//Deletes window's State struct pointer
    std::cout << "Main destructor" << std::endl;
}

void MainWindow::RunMessageLoop()
{
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))//Runs a message loop until user closes window
    {   
        TranslateMessage(&msg);//Translates message
        DispatchMessage(&msg);//Sends message to window's HandleMessage method
    }
}

void MainWindow::Maximize()
{
    ShowWindow(m_hwnd, SW_MAXIMIZE);//Maximizing window
    //std::cout << "Maxmized" << std::endl;
    UpdateWindow(m_hwnd);
}

void MainWindow::Minimize()
{
    ShowWindow(m_hwnd, SW_MINIMIZE);//Minimizing window
    UpdateWindow(m_hwnd);
}

void MainWindow::SetTitle(PCWSTR title)
{
    SetWindowTextW(m_hwnd, title);//Renaming window
    UpdateWindow(m_hwnd);
}

void MainWindow::SetBackgroundColor(PCWSTR color)
{
    m_state->m_backgroundcolor = ParseColorString(color);//Setting current background color of the window
    //Force a repaint of the window to apply the new background color
    SetBkColor(GetDC(m_hwnd), m_state->m_backgroundcolor);
    RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
    UpdateWindow(m_hwnd);
}

void MainWindow::MoveWindowTo(int leftside, int topside)
{
    // Move the window to the specified coordinates without changing size and Z order
    SetWindowPos(m_hwnd, NULL, leftside, topside, 0, 0, SWP_NOSIZE | SWP_NOZORDER);//Flags passed in the end are to disallow window resizing
    UpdateWindow(m_hwnd);
}

void MainWindow::ResizeWindow(int width, int height)
{
    SetWindowPos(m_hwnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);//Flags passed in the end are to disallow window movement
    UpdateWindow(m_hwnd);
}

std::pair<int, int> MainWindow::GetSize()
{
    return m_state->m_size;
}

std::pair<int, int> MainWindow::GetPos()
{
    return m_state->m_position;
}

COLORREF MainWindow::GetColor()
{
    return m_state->m_backgroundcolor;
}

PCWSTR MainWindow::GetTitle()
{
    return m_state->m_title;
}

PCWSTR MainWindow::ClassName() const
{
    return L"MainWindow";
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)//Switches through cases to find given message
    {
    case WM_DESTROY://message which is passes to window when user closes it
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
    {
        // The window has been resized
        int newWidth = LOWORD(lParam);
        int newHeight = HIWORD(lParam);

        // Update the state with the new size
        m_state->m_size = std::make_pair(newWidth, newHeight);
        //std::cout << "Size is:" << m_state->m_size.first << " - " << m_state->m_size.second << std::endl;
        // Redraw the window with the new size
        RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

        return 0;
    }
    case WM_MOVE:
    {
        // The window has been moved
        int newX = LOWORD(lParam);
        int newY = HIWORD(lParam);

        // Update the state with the new position
        m_state->m_position = std::make_pair(newX, newY);
        //std::cout << "Pos is:" << m_state->m_position.first << " - " << m_state->m_position.second << std::endl;

        return 0;
    }
    case WM_PAINT://Is used to paint(fill) window's background
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);

        HBRUSH hBrush = CreateSolidBrush(m_state->m_backgroundcolor);

        FillRect(hdc, &ps.rcPaint, hBrush);

        EndPaint(m_hwnd, &ps);

        return 0;
    }case WM_SYSCOMMAND://Receives when minimizing or maximizing is needed
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
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);//If no message matches the uMsg function return window's default procedure
    }

    return TRUE;
}
