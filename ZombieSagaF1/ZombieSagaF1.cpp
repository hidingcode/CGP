// Multibyte
// Not Set
// x86

//	Ask the compiler to include minimal header files for our program.
// #define -> Instruction to communicate with the compiler
#define WIN32_LEAN_AND_MEAN // Only include the skinny(LEAN) and powerful(MEAN) part of Windows.h

#include <Windows.h>
#include <d3d9.h>
#include <iostream>
//	include the D3DX9 library
#include <d3dx9.h>
// include the Direct Input library
#include <dinput.h>
#include <ctime>

// Background
#include "Background.h"

// Game Object 
#include "GameObject.h"
#include "Player.h"

// Timer
#include "FrameTimer.h"

// Audio Library
#include "AudioManager.h"

using namespace std;

#define WindowWidth 900
#define WindowHeight 700

#pragma comment(lib, "d3d9.lib ")
#pragma comment(lib, "d3dx9.lib ")
#pragma comment(lib, "dinput8.lib ")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "fmod_vc.lib")
//--------------------------------------------------------------------

//	Window handle
HWND g_hWnd = NULL;
// Window's Structure  /DESIGN PATTERN SINGLETON
WNDCLASS wndClass;

// Audio* audioManager;

// DX globals
IDirect3DDevice9* d3dDevice;
//	Direct Input globals.
LPDIRECTINPUT8 dInput;
LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
LPDIRECTINPUTDEVICE8 dInputMouseDevice;

//	Key input buffer
BYTE  diKeys[256];
// Mouse input buffer
DIMOUSESTATE mouseState;
// Sprite Brush
LPD3DXSPRITE spriteBrush = NULL;

// Background global
Background* bg = new Background(840, 650);

// Game Object globals
// GameObject* F1 = new GameObject(750,450, 3, 6, 20, 5);
Player* F1 = new Player(750, 450, 3, 6, 20, 5);

// Audio global 
AudioManager* audioManager;


// Input checker
bool leftKeyPressed = false;
bool rightKeyPressed = false;
bool upKeyPressed = false;
bool downKeyPressed = false;
bool wKeyPressed = false;
bool aKeyPressed = false;
bool sKeyPressed = false;
bool dKeyPressed = false;
bool spaceKeyPressed = false;

// !! Place to implement
bool CircleCollisionDetection(int radiusA, int radiusB, D3DXVECTOR2 positionA, D3DXVECTOR2 positionB)
{
	D3DXVECTOR2 distance = positionA - positionB;
	if (radiusA + radiusB < D3DXVec2Length(&distance))
	{
		return false;
	}

	else
	{
		return true;
	}
}

//	Window Procedure, for event handling
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // Get messages from the OS(mouse was move,keyboard was press)
{
	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_SPACE:
			spaceKeyPressed = true;
			cout << "SPACE" << endl;
			break;
		}
		break;
		//	Default handling for other messages.
	/*
	case WM_MOUSEMOVE:
		playerPosition.y = (short)HIWORD(lParam);
		playerPosition.x = (short)LOWORD(lParam);
		break;
	*/
	default:
		return DefWindowProc(hWnd, message, wParam, lParam); // Return messages back to the OS
	}

	return 0;
}
//--------------------------------------------------------------------

//	use int main if you want to have a console to print out message
//int main()

void CreateMyWindow() {
	//	Set all members in wndClass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));
	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure; // Long Pointer to a window procedure function
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	Register the window.
	RegisterClass(&wndClass);

	//	You are to refer to MSDN for each of the parameters details.
	//  Create instance of window
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "My Window's Name", WS_OVERLAPPEDWINDOW, 0, 100, WindowWidth, WindowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(g_hWnd, 1);
}

bool WindowIsRunning() {
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

void CleanupMyLevel() {
	LPDIRECT3DTEXTURE9 f1Texture = F1->GetTexture();
	f1Texture->Release();
	f1Texture = NULL;
}

void CreateMyDX() {
	//	Define Direct3D 9.
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	//	Define how the screen presents.
	D3DPRESENT_PARAMETERS d3dPP;
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = WindowWidth;
	d3dPP.BackBufferHeight = WindowHeight;
	d3dPP.hDeviceWindow = g_hWnd;

	//	Create a Direct3D 9 device.
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

	if (FAILED(hr))
		cout << "Create DX failed";

	//	Create sprite. Study the documentation. 
	hr = D3DXCreateSprite(d3dDevice, &spriteBrush);

	if (FAILED(hr)) {
		cout << "Create sprite failed" << endl;
	}

}

void CreateMyDirectInput()
{
	//	Create the Direct Input object.
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	if FAILED(hr)
	{
		cout << "Create Direct Input Failed" << endl;
	}


	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);

	if FAILED(hr)
	{
		cout << "Create Keyboard Input Device Failed" << endl;
	}

	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);

	if FAILED(hr)
	{
		cout << "Create Mouse Input Device Failed" << endl;
	}

	//	Set the input data format.
	hr = dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	//	Set the input data format.
	hr = dInputMouseDevice->SetDataFormat(&c_dfDIMouse);

	//	Set the cooperative level.
	//	To Do:
	//	Try with different combination.
	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
}

// !! Place to implement
void InitializeLevel() {

	audioManager->PlaySoundTrack();
	srand(time(0));

	//	Create texture
	HRESULT hr = bg->CreateTexture(d3dDevice, "Assets/roadBG.png");

	if (FAILED(hr)) {
		cout << "Create background texture failed" << endl;
	}

	hr = F1->CreateTexture(d3dDevice, "Assets/F1.PNG");
									;
	if (FAILED(hr)) {
		cout << "Create F1 texture failed" << endl;
	}

	// F1 car (player) initialisation
	F1->Init(D3DXVECTOR2(100, 300), 1.0f, 0.0f, 2.0f, D3DXVECTOR2(0.4f,0.4f),0.05f, 0.001f);
}

void GetInput()
{	//	Acquire the device.
	dInputKeyboardDevice->Acquire();
	dInputMouseDevice->Acquire();
	//	Get immediate Keyboard Data.
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	// Get Mouse Data
	dInputMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);

	if (diKeys[DIK_UP] & 0x80)
	{
		cout << "UP" << std::endl;
		upKeyPressed = true;
	}

	if (diKeys[DIK_DOWN] & 0x80)
	{
		cout << "DOWN" << std::endl;
		downKeyPressed = true;
	}

	if (diKeys[DIK_LEFT] & 0x80)
	{
		cout << "LEFT" << std::endl;
		leftKeyPressed = true;
	}

	if (diKeys[DIK_RIGHT] & 0x80)
	{
		cout << "RIGHT" << std::endl;
		rightKeyPressed = true;
	}

	if (diKeys[DIK_W] & 0x80)
	{
		cout << "W" << std::endl;
		wKeyPressed = true;
	}

	if (diKeys[DIK_A] & 0x80)
	{
		cout << "A" << std::endl;
		aKeyPressed = true;
	}

	if (diKeys[DIK_S] & 0x80)
	{
		cout << "S" << std::endl;
		sKeyPressed = true;
	}

	if (diKeys[DIK_D] & 0x80)
	{
		cout << "D" << std::endl;
		dKeyPressed = true;
	}

	/*
	if (diKeys[DIK_SPACE] & 0x80)
	{
		cout << "SPACE" << std::endl;
		spaceKeyPressed = true;
	}
	*/
}

// !! Place to implement
void Update(int framesToUpdate) {
	// audioManager->UpdateSound();

	for (int i = 0; i < framesToUpdate; i++) {
		/*counter++;*/

		if (wKeyPressed) {
			/*if (counter % timer->getFPS() / player1SpriteFPS) {
				player1FrameCounter++
			}*/
			F1->MovForward();
			F1->IncreaseFrameCounter();	
		}

		if (sKeyPressed) {
			/*F1->MovBackward();*/
		}

		if (leftKeyPressed) {
			/*F1->TurnLeft();*/
		}

		if (rightKeyPressed) {
			/*F1->TurnRight();*/
		}

		F1->UpdateAnim();
		F1->UpdatePhysics();
		F1->CheckBoundary(WindowWidth, WindowHeight);

	}
		leftKeyPressed = false;
		rightKeyPressed = false;
		upKeyPressed = false;
		downKeyPressed = false;
		aKeyPressed = false;
		dKeyPressed = false;
		wKeyPressed = false;
		sKeyPressed = false;
}

void Render() {
	//	To Do:
		//	Update.

		//	Clear the back buffer.
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//	Begin the scene
	d3dDevice->BeginScene();

	//	Drawing.
	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX mat;

	// draw F1
	bg->Render(spriteBrush, &mat, D3DXVECTOR2(1.1, 1.1), D3DXVECTOR2(0, 0));
	F1->Render(spriteBrush, &mat);

	//	End sprite drawing
	spriteBrush->End();
	//PlaySound()

	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void CleanupMyDx() {
	//	Release and clean up everything
	spriteBrush->Release();
	spriteBrush = NULL;

	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;
}

void CleanupMyDirectInput()
{
	//	Release keyboard device.
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	//	Release DirectInput.
	dInput->Release();
	dInput = NULL;
}

void CleanupMyWindow() {
	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL)); // Delete window class
}
//	use WinMain if you don't want the console
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) // WinMain is a function in WINAPI
{
	/*
	   HINSTANCE hInstance - ID Number
	   HINSTANCE hPrevInstance - previous window
	   LPSTR lpCmdLine - Long pointer to a command line (ping.exe ->www.yahoo.com<-)
	   int nShowCmd - window mode (fullscreen, borderless)
	*/

	CreateMyWindow();
	CreateMyDX();
	CreateMyDirectInput();

	audioManager = new AudioManager();
	audioManager->InitializeAudio();
	audioManager->LoadSounds();

	InitializeLevel();

	FrameTimer* timer = new FrameTimer();

	timer->Init(20);
	while (WindowIsRunning())
	{
		GetInput();
		Update(timer->FramesToUpdate());
		Render();
	}
	CleanupMyLevel();
	CleanupMyDirectInput();
	CleanupMyDx();
	CleanupMyWindow();

	return 0;
}