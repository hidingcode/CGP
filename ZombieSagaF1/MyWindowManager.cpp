#include "MyWindowManager.h"

MyWindowManager::MyWindowManager()
{
}

MyWindowManager::~MyWindowManager()
{
}

LRESULT MyWindowManager::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	the message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case  WM_KEYDOWN:
		switch (wParam)
		{
		// Quit the message when escape key is pressed down
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
		//	default handling for other messages.
	default:
		return DefWindowProc(hWnd, message, wParam, lParam); // return messages back to the os
	}

	return 0;
}

void MyWindowManager::CreateMyWindow(int windowWidth, int windowHeight)
{	
	// Store Window Width and Window Height data 
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	//	set all members in wndclass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));
	//	filling wndclass. you are to refer to msdn for each of the members details.
	//	these are the fundamental structure members to be specify, in order to create your window.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure; // Long Pointer to a window procedure function
	wndClass.lpszClassName = "Zombie Saga F1";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	register the window.
	RegisterClass(&wndClass);

	//	you are to refer to msdn for each of the parameters details.
	//  create instance of window
	this->g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Zombie Sage F1", WS_OVERLAPPEDWINDOW, 0, 0, windowWidth, windowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(g_hWnd, 1);
}

bool MyWindowManager::IsWindowRunning()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg)); // Set memory to zero (To clear the memory)

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT)
			return false;
		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);
	}
	return true;
}

void MyWindowManager::CleanUpMyWindow()
{
	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL));
}

HWND MyWindowManager::GetWindowHandle()
{
	return this->g_hWnd;
}

int MyWindowManager::GetWindowWidth()
{
	return windowWidth;
}

int MyWindowManager::GetWindowHeight()
{
	return windowHeight;
}