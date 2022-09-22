#pragma once
#define WIN32_LEAN_AND_MEAN // Only include the skinny(LEAN) and powerful(MEAN) part of Windows.h
#include <Windows.h>


class MyWindowManager
{
public:
	MyWindowManager();
	~MyWindowManager();
	static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void CreateMyWindow(int WindowWidth, int WindowHeight);
	bool IsWindowRunning();
	void CleanUpMyWindow();
	HWND GetWindowHandle();

private:
	//	Window handle
	HWND g_hWnd = NULL;
	// Window's Structure  /DESIGN PATTERN SINGLETON
	WNDCLASS wndClass;
};

