#ifndef BUTTON_H
#define BUTTON_H
#include "MainWindow.h"
#include <functional>


class Button : public BaseWindow<Button>
{
private:
	COLORREF ParseColorString(PCWSTR color);
	void DrawCustomButton(HDC& hdc, RECT& rect);
public:
	Button(MainWindow& win);
	Button(MainWindow& win, PCWSTR text);
	Button(MainWindow& win, int width, int heigth);
	Button(MainWindow& win, std::pair<int, int> position);
	Button(MainWindow& win, int width, int heigth, std::pair<int, int> position);
	Button(MainWindow& win, PCWSTR text, PCWSTR color);
	Button(MainWindow& win, PCWSTR text, PCWSTR color, int width, int heigth, std::pair<int, int> position);
	~Button();//Destructor

	void ResizeButton(int width, int height);
	void MoveButtonTo(int leftside, int topside);
	void SetBackgroundColor(PCWSTR color);
	void SetTitle(PCWSTR title);
	void SetBorder(int size, PCWSTR color);

	template<typename Func>
	void SetOnClick(Func&& UserFunc);

	void RunMessageLoop();

	PCWSTR  ClassName() const;
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;//Function that handles all messages sent to the button
private:
	MainWindow* wnd = nullptr;
	State* m_state;//Struct which contains button's position's, size's, parent's and background color's current state
	
	std::function<void()> OnClick;
};


template<typename Func>
inline void Button::SetOnClick(Func&& UserFunc)
{
	OnClick = std::forward<Func>(UserFunc);
}

#endif //BUTTON_H
