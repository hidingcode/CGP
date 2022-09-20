//#include "MyWindowManager.h"
//
//
//MyWindowManager::MyWindowManager()
//{
//}
//
//MyWindowManager::~MyWindowManager()
//{
//}
//
//LRESULT CALLBACK MyWindowManager::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	switch (message)
//	{
//		//	The message is post when we destroy the window.
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//
//	case WM_KEYDOWN:
//		switch (wParam)
//		{
//		case VK_ESCAPE:
//			PostQuitMessage(0);
//			break;
//		}
//		break;
//		//	Default handling for other messages.
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam); // Return messages back to the OS
//	}
//
//	return 0;
//}
//
//void MyWindowManager::CreateMyWindow()
//{
//	//	Set all members in wndClass to 0.
//	ZeroMemory(&wndClass, sizeof(wndClass));
//	//	Filling wndClass. You are to refer to MSDN for each of the members details.
//	//	These are the fundamental structure members to be specify, in order to create your window.
//	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
//	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wndClass.hInstance = GetModuleHandle(NULL);
//	wndClass.lpfnWndProc = WindowProcedure; // Long Pointer to a window procedure function
//	wndClass.lpszClassName = "Zombie Saga F1";
//	wndClass.style = CS_HREDRAW | CS_VREDRAW;
//
//	//	Register the window.
//	RegisterClass(&wndClass);
//
//	//	You are to refer to MSDN for each of the parameters details.
//	//  Create instance of window
//	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Zombie Sage F1", WS_OVERLAPPEDWINDOW, 0, 0, WindowWidth, WindowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
//	ShowWindow(g_hWnd, 1);
//}
//
//bool MyWindowManager::IsWindowRunnig()
//{
//	MSG msg;
//	ZeroMemory(&msg, sizeof(msg)); // Set memory to zero (To clear the memory)
//
//	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//	{
//		//	Receive a quit message
//		if (msg.message == WM_QUIT)
//			return false;
//		//	Translate the message 
//		TranslateMessage(&msg);
//		//	Send message to your window procedure
//		DispatchMessage(&msg);
//	}
//	return true;
//}


