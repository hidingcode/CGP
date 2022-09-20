#pragma once
#include <Windows.h>

class MyWindowManager
{
public:
	MyWindowManager();
	~MyWindowManager();
	static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void CreateMyWindow();
	bool IsWindowRunning();
	void CleanUpMyWindow();
	HWND GetWindowHandle();
private:
	//	Window handle
	HWND g_hWnd = NULL;
	// Window's Structure  /DESIGN PATTERN SINGLETON
	WNDCLASS wndClass;
};

