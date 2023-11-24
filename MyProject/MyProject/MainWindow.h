#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "BaseWindow.h"
#include <algorithm>
#include <unordered_map>


class MainWindow : public BaseWindow<MainWindow>
{
private:
    COLORREF ParseColorString(PCWSTR color);
public:
    MainWindow();
    MainWindow(PCWSTR title);
    MainWindow(int x, int y);
    MainWindow(PCWSTR title, PCWSTR color);
    MainWindow(int width, int height, int x, int y, PCWSTR title, PCWSTR color);
    ~MainWindow();

    void Maximize();
    void Minimize();

    void SetTitle(PCWSTR title);
    void SetBackgroundColor(PCWSTR color);
    void MoveWindowTo(int leftside, int topside);
    void ResizeWindow(int width, int height);

    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
private:
    State* m_state;
};

#endif //MAINWINDOW_H
