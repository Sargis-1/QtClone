#include "Button.h"

COLORREF Button::ParseColorString(PCWSTR color)
{
    // Convert colorString to lowercase for case-insensitive comparison
    std::wstring lowercaseColorString = color;
    std::transform(lowercaseColorString.begin(), lowercaseColorString.end(), lowercaseColorString.begin(), towlower);

    std::unordered_map<std::wstring, COLORREF> colors;//Used to return given colors RGB(COLORREF) value

    colors[L"white"] = RGB(255, 255, 255);
    colors[L"red"] = RGB(255, 0, 0);
    colors[L"green"] = RGB(60, 179, 113);
    colors[L"blue"] = RGB(0, 0, 255);
    colors[L"yellow"] = RGB(255, 255, 0);
    colors[L"purple"] = RGB(128, 0, 128);
    colors[L"orange"] = RGB(255, 165, 0);
    colors[L"black"] = RGB(0, 0, 0);
    colors[L"gray"] = RGB(128, 128, 128);
    colors[L"brown"] = RGB(139, 69, 19);
    colors[L"pink"] = RGB(255, 182, 193);
    colors[L"cyan"] = RGB(0, 255, 255);
    colors[L"magenta"] = RGB(255, 0, 255);
    colors[L"silver"] = RGB(192, 192, 192);
    colors[L"gold"] = RGB(255, 215, 0);


    return colors[lowercaseColorString];
}

void Button::DrawCustomButton(HDC& hdc, RECT& rect)
{
   
    // Draw the border
    HPEN hPen = CreatePen(PS_SOLID, m_state->m_bordersize, m_state->m_bordercolor);
    SelectObject(hdc, hPen);
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

    //std::cout << "bordersize = " << m_state->m_bordersize << std::endl;
    // Draw the button background (fill color)
    HBRUSH hBrush = CreateSolidBrush(m_state->m_backgroundcolor);
    RECT fillrect = {};
    fillrect.left = rect.left + m_state->m_bordersize/2;
    fillrect.right = rect.right - m_state->m_bordersize/2;
    fillrect.top = rect.top + m_state->m_bordersize/2;
    fillrect.bottom = rect.bottom - m_state->m_bordersize/2;

    FillRect(hdc, &fillrect, hBrush);
    //Draw the button text using DrawText
    SetBkMode(hdc, TRANSPARENT);
    DrawText(hdc, m_state->m_title, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

    // Cleanup
    DeleteObject(hPen);
    DeleteObject(hBrush);
}

Button::Button(MainWindow& win) : m_state(new State)
{
    m_state->m_backgroundcolor = ParseColorString(L"white");
    m_state->m_size = std::make_pair(200, 40);
    int buttonx = (win.GetSize().first - m_state->m_size.first) / 2;//to place button in the middle of the window
    int buttony = (win.GetSize().second - m_state->m_size.second) / 2;
    m_state->m_position = std::make_pair( buttonx, buttony);
    m_state->m_title = L"Click me";
    m_state->m_bordercolor = m_state->m_backgroundcolor;
    m_state->m_parent = win.Window();
    Create(m_state, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON);//Creates button with given state and style
    UpdateWindow(m_hwnd);//To avoid bugs such as one method starts executions before previous method did not end it's execution
}

Button::Button(MainWindow& win, PCWSTR text) : m_state(new State)
{
    m_state->m_backgroundcolor = ParseColorString(L"white");
    m_state->m_size = std::make_pair(200, 40);
    int buttonx = (win.GetSize().first - m_state->m_size.first) / 2;//to place button in the middle of the window
    int buttony = (win.GetSize().second - m_state->m_size.second) / 2;
    m_state->m_position = std::make_pair(buttonx, buttony);
    m_state->m_title = text;
    m_state->m_bordercolor = m_state->m_backgroundcolor;
    m_state->m_parent = win.Window();
    Create(m_state, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON);//Creates button with given state and style
    UpdateWindow(m_hwnd);
}

Button::Button(MainWindow& win, int width, int heigth) : m_state(new State)
{
    m_state->m_backgroundcolor = ParseColorString(L"white");
    m_state->m_size = std::make_pair(width, heigth);
    int buttonx = (win.GetSize().first - m_state->m_size.first) / 2;//to place button in the middle of the window
    int buttony = (win.GetSize().second - m_state->m_size.second) / 2;
    m_state->m_position = /*std::make_pair(400, 400);*/std::make_pair(buttonx, buttony);
    m_state->m_title = L"Click me";
    m_state->m_bordercolor = m_state->m_backgroundcolor;
    m_state->m_parent = win.Window();
    Create(m_state, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON);//Creates button with given state and style
    UpdateWindow(m_hwnd);
}

Button::Button(MainWindow& win, std::pair<int, int> position) : m_state(new State)
{
    m_state->m_backgroundcolor = ParseColorString(L"white");
    m_state->m_size = std::make_pair(200, 40);
    //int buttonx = (win.GetSize().first - m_state->m_size.first) / 2;//to place button in the middle of the window
    //int buttony = (win.GetSize().second - m_state->m_size.second) / 2;
    m_state->m_position = std::make_pair(position.first, position.second);/*std::make_pair(buttonx, buttony);*/
    m_state->m_title = L"Click me";
    m_state->m_bordercolor = m_state->m_backgroundcolor;
    m_state->m_parent = win.Window();
    Create(m_state, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON);//Creates button with given state and style
    UpdateWindow(m_hwnd);
}

Button::Button(MainWindow& win, int width, int heigth, std::pair<int, int> position) : m_state(new State)
{
    m_state->m_backgroundcolor = ParseColorString(L"white");
    m_state->m_size = std::make_pair(width, heigth);
    //int buttonx = (win.GetSize().first - m_state->m_size.first) / 2;//to place button in the middle of the window
    //int buttony = (win.GetSize().second - m_state->m_size.second) / 2;
    m_state->m_position = std::make_pair(position.first, position.second);/*std::make_pair(buttonx, buttony);*/
    m_state->m_title = L"Click me";
    m_state->m_bordercolor = m_state->m_backgroundcolor;
    m_state->m_parent = win.Window();
    Create(m_state, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_BORDER);//Creates button with given state and style
    UpdateWindow(m_hwnd);
}

Button::Button(MainWindow& win, PCWSTR text, PCWSTR color) : m_state(new State)
{
    m_state->m_backgroundcolor = ParseColorString(color);
    m_state->m_size = std::make_pair(200, 40);
    int buttonx = (win.GetSize().first - m_state->m_size.first) / 2;//to place button in the middle of the window
    int buttony = (win.GetSize().second - m_state->m_size.second) / 2;
    m_state->m_position = std::make_pair(buttonx, buttony);
    m_state->m_title = text;
    m_state->m_bordercolor = m_state->m_backgroundcolor;
    m_state->m_parent = win.Window();
    Create(m_state, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON);//Creates button with given state and style
    UpdateWindow(m_hwnd);
}

Button::Button(MainWindow& win, PCWSTR text, PCWSTR color, int width, int heigth, std::pair<int, int> position) : m_state(new State)
{
    m_state->m_backgroundcolor = ParseColorString(color);
    m_state->m_size = std::make_pair(width, heigth);
    m_state->m_position = std::make_pair(position.first, position.second);
    m_state->m_title = text;
    m_state->m_bordercolor = m_state->m_backgroundcolor;
    m_state->m_parent = win.Window();
    Create(m_state, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON);//Creates button with given state and style
    UpdateWindow(m_hwnd);
}

Button::~Button()
{
    delete m_state;//Deletes window's State struct pointer
    std::cout << "Button destructor" << std::endl;
}

void Button::ResizeButton(int width, int height)
{   
    SetWindowPos(m_hwnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);
    UpdateWindow(m_state->m_parent);
    UpdateWindow(m_hwnd);
}

void Button::MoveButtonTo(int leftside, int topside)
{
    SetWindowPos(m_hwnd, NULL, leftside, topside, 0, 0, SWP_NOSIZE | SWP_NOZORDER);//Flags passed in the end are to disallow window resizing
    UpdateWindow(m_state->m_parent);
    UpdateWindow(m_hwnd);
}

void Button::SetBackgroundColor(PCWSTR color)
{
    m_state->m_backgroundcolor = ParseColorString(color);//Setting current background color of the button

    //Force a repaint of the window to apply the new background color
    //SetBkColor(GetDC(m_hwnd), m_state->m_backgroundcolor);//DO I NEED THIS OR NOT?
    RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
    UpdateWindow(m_state->m_parent);
    UpdateWindow(m_hwnd);
}

void Button::SetTitle(PCWSTR title)
{
    m_state->m_title = title;

    // Force a repaint of the button to update the text
    RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
    UpdateWindow(m_hwnd);
}

void Button::SetBorder(int size, PCWSTR color)
{
    m_state->m_bordersize = size;
    m_state->m_bordercolor = ParseColorString(color);

    // Force a repaint of the button to update the border
    RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
    UpdateWindow(m_state->m_parent);
    UpdateWindow(m_hwnd);
}

void Button::RunMessageLoop()
{
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))//Runs a message loop until user closes window
    {
        TranslateMessage(&msg);//Translates message
        DispatchMessage(&msg);//Sends message to window's HandleMessage method
    }
}

PCWSTR Button::ClassName() const
{
    return L"BUTTON";
}

LRESULT Button::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)//Switches through cases to find given message
    {
    case WM_DESTROY://message which is passes to window when user closes it
        PostQuitMessage(0);
        return 0;
    case WM_LBUTTONDOWN:
        OnClick();
    //case WM_ERASEBKGND:
    //{
    //    HDC hdc = reinterpret_cast<HDC>(wParam);
    //    RECT rect;
    //    GetClientRect(m_hwnd, &rect);

    //    MainWindow* parentWindow = reinterpret_cast<MainWindow*>(GetWindowLongPtr(m_state->parent, GWLP_USERDATA));

    //    // Fill the background with the window's background color
    //    HBRUSH hBrush = CreateSolidBrush(parentWindow->GetColor());
    //    FillRect(hdc, &rect, hBrush);
    //    //DeleteObject(hBrush);
    //    UpdateWindow(m_hwnd);
    //    // Return nonzero to indicate that the background has been erased
    //    return 1;
    //}
    case WM_SIZE:
    {
        // The window has been resized
        int newWidth = LOWORD(lParam);
        int newHeight = HIWORD(lParam);

        // Update the state with the new size
        m_state->m_size = std::make_pair(newWidth, newHeight);

        // Redraw the window with the new size
        RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

        //std::cout << "Size is:" << m_state->m_size.first << " - " << m_state->m_size.second << std::endl;

        return 0;
    }case WM_MOVE:
    {
        // The window has been moved
        int newX = LOWORD(lParam);
        int newY = HIWORD(lParam);

        // Update the state with the new position
        m_state->m_position = std::make_pair(newX, newY);

        RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
        //std::cout << "Pos is:" << m_state->m_position.first << " - " << m_state->m_position.second << std::endl;

        return 0;
    }
    case WM_PAINT://Is used to paint(fill) window's background
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(m_hwnd, &ps);

        RECT clientRect;
        GetClientRect(m_hwnd, &clientRect);
        DrawCustomButton(hdc, clientRect);

        EndPaint(m_hwnd, &ps);

        return 0;
    }
    default:
        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);//If no message matches the uMsg function return window's default procedure
    }

    return TRUE;
}
