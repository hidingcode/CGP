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
// include tje Direct Input library
#include <dinput.h>
#include "FrameTimer.h"

using namespace std;

#define WindowWidth 900
#define WindowHeight 700

#pragma comment(lib, "d3d9.lib ")
#pragma comment(lib, "d3dx9.lib ")
#pragma comment(lib, "dinput8.lib ")
#pragma comment(lib, "dxguid.lib")
//--------------------------------------------------------------------

//	Window handle
HWND g_hWnd = NULL;
// Window's Structure  /DESIGN PATTERN SINGLETON
WNDCLASS wndClass;

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

int red = 0;
int green = 0;
int blue = 0;
int maxColorValue = 255;
bool redReach = false;
bool greenReach = false;
bool blueReach = false;

// Game level globals
LPDIRECT3DTEXTURE9 texture = NULL;
LPDIRECT3DTEXTURE9 mouseTexture = NULL;
LPD3DXSPRITE spriteBrush = NULL; 
LPD3DXFONT font = NULL;
LPD3DXLINE line = NULL;

RECT spriteRect;
RECT spriteColRect;
RECT textRect;
RECT mouseRect;
RECT mouseColRect;

// Mouse Position
D3DXVECTOR2 mousePosition;
// Player Position
D3DXVECTOR2 playerPosition;
D3DXVECTOR2 fontPosition;

// Texture and Sprite
int textureWidth = 0;
int textureHeight = 0;
int textureRow = 0;
int textureColumn = 0;
int spriteWidth = 0;
int spriteHeight = 0;
int spriteFPS = 0;

int frameCounter = 0;
int maxFrame = 0;

int currentDirection = 0;
int currentState = 0;
float playerVelocityX = 0;
float playerVelocityY = 0;
float gravity = 0;
float jumpForce = 0;
int jumpCount;
int remainingJump;

float currentTime = 0;
int radius = 0;

D3DXVECTOR2 startPoint;
D3DXVECTOR2 endPoint;
D3DXVECTOR2 lineVertices[] = { startPoint, endPoint };

enum movementDirection { moveDown, moveLeft, moveRight, moveUp};

int counter = 0;
int delayFactor = 0;

bool leftKeyPressed = false;
bool rightKeyPressed = false;
bool upKeyPressed = false;
bool downKeyPressed = false;
bool spaceKeyPressed = false;

bool isIdle = true;
//--------------------------------------------------------------------

bool CollisionDetection(RECT rect1, RECT rect2)
{
	if (rect1.left > rect2.right)
	{
		return false;
	}
	if (rect1.right < rect2.left)
	{
		return false;
	}
	if (rect1.top > rect2.bottom)
	{
		return false;
	}
	if (rect1.bottom < rect2.top)
	{
		return false;
	}
	return true;
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
		/*
		case VK_LEFT:
			leftKeyPressed = true;
			cout << "lEFT KEY WAS PRESSED" << endl;
			break;
		case VK_RIGHT:
			rightKeyPressed = true;
			cout << "RIGHT KEY WAS PRESSED" << endl;
			break;
		case VK_UP:
			upKeyPressed = true;
			cout << "UP KEY WAS PRESSED" << endl;
			break;
		case VK_DOWN:
			downKeyPressed = true;
			cout << "DOWN KEY WAS PRESSED" << endl;
			break;
		case 'R':
			if(red < maxColorValue && !redReach)
			{
				red += 5;

				if (red == maxColorValue)
				{
					redReach = true;
				}
			}

			else
			{
				red -= 5;
				if (red == 0)
				{
					redReach = false;
				}
			}
		
			// colorRange(red);
			cout << "Red: " << red<< endl;
			break;
		case 'G':
			if (green < maxColorValue && !greenReach)
			{
				green += 5;

				if (green == maxColorValue)
				{
					greenReach = true;
				}
			}

			else
			{
				green -= 5;
				if (green == 0)
				{
					greenReach = false;
				}
			}
			cout << "Green: " << green << endl;
			break;
		case 'B':
			if (blue < maxColorValue && !blueReach)
			{
				blue += 5;

				if (blue == maxColorValue)
				{
					blueReach = true;
				}
			}

			else
			{
				blue -= 5;
				if (blue == 0)
				{
					blueReach = false;
				}
			}
			cout << "Blue: " << blue << endl;
			break;
		default:
			break;
		*/
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

void CreateMyWindow(){
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

bool WindowIsRunning(){
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
	texture->Release();
	texture = NULL;
}

void CleanupMyWindow(){
	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL)); // Delete window class
}

//	use int main if you want to have a console to print out message
//int main()

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

	hr = D3DXCreateFont(d3dDevice, 25, 0, 0, 1, false,DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);
	
	if (FAILED(hr)) {
		cout << "Create font failed" << endl;
	}

	hr = D3DXCreateLine(d3dDevice, &line);

	if (FAILED(hr)) {
		cout << "Create line failed" << endl;
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

	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	mousePosition.x = WindowWidth / 2;
	mousePosition.y = WindowHeight / 2;
	
}

void InitializeLevel() {
	//	Create texture. Study the documentation.
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Assets/militia.png", &texture);
	hr = D3DXCreateTextureFromFile(d3dDevice, "Assets/pointer.png", &mouseTexture);

	//hr = D3DXCreateTextureFromFileEx(/* Your Direct3D device */, "01.bmp", D3DX_DEFAULT, D3DX_DEFAULT, 
	//									D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
	//									D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), 
	//									NULL, NULL, &texture);
	if (FAILED(hr)) {
		cout << "Create texture failed" << endl;
	}

	textureWidth = 128;
	textureHeight = 192;
	textureRow = 4;
	textureColumn = 4;
	spriteWidth = textureWidth / textureColumn;
	spriteHeight = textureHeight / textureRow;
	maxFrame = 3;
	delayFactor = 8;

	playerVelocityX = 10;
	gravity = 2;
	jumpForce = -30;
	jumpCount = 0;
	remainingJump = 2;

	//	Specify the "	" rectangle.
	spriteRect.left = frameCounter % textureColumn * spriteWidth;
	spriteRect.right = spriteRect.left + spriteWidth;
	spriteRect.top = currentDirection * spriteHeight;
	spriteRect.bottom = spriteRect.top + spriteHeight;

	mouseRect.left = 0;
	mouseRect.top = 0;
	mouseRect.right = 32;
	mouseRect.bottom = 32;
	
	textRect.left = 100;
	textRect.top = 100;
	textRect.right = 450;
	textRect.bottom = 125;

	playerPosition.x = 0;
	playerPosition.y = WindowWidth - spriteHeight;
	
	startPoint = D3DXVECTOR2(WindowWidth / 2, WindowHeight / 2);
	endPoint;

	lineVertices[0] = startPoint;
	lineVertices[1] = endPoint;
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

/*
if (diKeys[DIK_SPACE] & 0x80)
{
	cout << "SPACE" << std::endl;
	spaceKeyPressed = true;
}
*/
}

void Update(int framesToUpdate) {
	// See how far in the X direction the mouse has been moved
	mousePosition.x += mouseState.lX;
	// See how far in the Y direction the mouse has been moved
	mousePosition.y += mouseState.lY;

	spriteRect.left = frameCounter % textureColumn * spriteWidth;
	spriteRect.right = spriteRect.left + spriteWidth;
	spriteRect.top = currentDirection * spriteHeight;
	spriteRect.bottom = spriteRect.top + spriteHeight;

	spriteColRect.left = playerPosition.x;
	spriteColRect.right = spriteColRect.left + spriteWidth;
	spriteColRect.top = playerPosition.y;
	spriteColRect.bottom = spriteColRect.top + spriteHeight;

	mouseColRect.left = mousePosition.x;
	mouseColRect.top = mousePosition.y;
	mouseColRect.right = mousePosition.x + 32;
	mouseColRect.bottom = mousePosition.y + 32;

	//	if (frameCounter > maxFrame)
	//	{	
	//		isIdle = true;
	//		frameCounter = 0;
	//	}
	//}

	for (int i = 0; i < framesToUpdate; i++)
	{	
		if (leftKeyPressed)
		{
			currentDirection = moveLeft;
			if (playerPosition.x > 0)
			{
				playerPosition.x -= playerVelocityX;
			}
			isIdle = false;
		}

		if (rightKeyPressed) {
			currentDirection = moveRight;
			if (playerPosition.x < WindowWidth - spriteWidth - playerVelocityX)
			{
				playerPosition.x += playerVelocityX;
			}
			isIdle = false;
		}
		if (upKeyPressed) {
			currentDirection = moveUp;
			if (playerPosition.y > 0)
			{
				playerPosition.y -= playerVelocityX;
			}
			isIdle = false;
		}
		if (downKeyPressed) {
			currentDirection = moveDown;
			if (playerPosition.y < WindowHeight - spriteHeight - playerVelocityX)
			{
				playerPosition.y += playerVelocityX;
			}
			isIdle = false;
		}

		if (spaceKeyPressed)
		{
			if (jumpCount > 0)
			{
				if (playerPosition.y == WindowHeight - spriteHeight)
				{
					jumpCount = 0;
				}
			}

			if (jumpCount == 0)
			{
				playerVelocityY = jumpForce;
				cout << "First Jump" << endl;
				if (playerPosition.y == WindowHeight - spriteHeight)
				{
					jumpCount = 1;
				}

				else
				{
					jumpCount = 2;
				}
			}
			else if (jumpCount == 1)
			{
				playerVelocityY = jumpForce;
				jumpCount = 2;
				cout << "Double Jump" << endl;
			}

			spaceKeyPressed = false;
		}

		//counter++;
		//if (counter % delayFactor == 0)
		//{	
			//if (!isIdle)
			//{
			//	frameCounter++;
			//}

		if (i == framesToUpdate - 1)
		{
			leftKeyPressed = false;
			downKeyPressed = false;
			upKeyPressed = false;
			rightKeyPressed = false;
		}

		if (!isIdle)
		{
			frameCounter++;
		}

		if (frameCounter > maxFrame)
		{	
			isIdle = true;
			frameCounter = 0;
		}
	}
	
	playerVelocityY += gravity;
	playerPosition.y += playerVelocityY;
	if (playerPosition.y > WindowHeight - spriteHeight)
	{
		playerPosition.y = WindowHeight - spriteHeight;
		playerVelocityY = 0;
	}
	
	radius = 200;
	currentTime += 0.02;

	endPoint.x = sin(currentTime) * radius + startPoint.x;
	endPoint.y = -cos(currentTime) * radius + startPoint.y;

	lineVertices[1] = endPoint;

	if (CollisionDetection(spriteColRect, mouseColRect))
	{
		cout << "Collision occur!" << endl;
	}
}

void Render() {
	//	To Do:
		//	Update.

		//	Clear the back buffer.
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(red, green, blue), 1.0f, 0);

	//	Begin the scene
	d3dDevice->BeginScene();

	//	Drawing.
	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);
	
	// D3DXMATRIX mat;
	// D3DXVECTOR2 scaling = D3DXVECTOR2(1.0f, 1.0f);
	// D3DXVECTOR2 spriteCentre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	// float rotation = 0.0f;

	// D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &playerPosition);

	// spriteBrush->SetTransform(&mat);
	// 
	//	Sprite rendering. Study the documentation.
	// D3DCOLOR_XRGB() - COLOR FILTER
	//spriteBrush->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//spriteBrush->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//spriteBrush->Draw(texture, &spriteRect, NULL, &playerPosition, D3DCOLOR_XRGB(255, 255, 255));
	//spriteBrush->Draw(mouseTexture, &mouseRect, NULL, &mousePosition, D3DCOLOR_XRGB(255, 255, 255));
	//font->DrawText(spriteBrush, "Hello World!", -1, &textRect, 0, D3DCOLOR_XRGB(255, 255, 255));

	D3DXMATRIX mat;
	D3DXVECTOR2 scaling = D3DXVECTOR2(1.0f, 1.0f);
	D3DXVECTOR2 spriteCentre = D3DXVECTOR2(12, 12);
	float rotation = 0.0f;

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &fontPosition);
	spriteBrush->SetTransform(&mat);
	font->DrawText(spriteBrush, "Hello World!", -1, &textRect, 0, D3DCOLOR_XRGB(255, 255, 255));

	scaling = D3DXVECTOR2(1.0f, 1.0f);
	spriteCentre = D3DXVECTOR2(32, 32);
	rotation = 0.0f;

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &playerPosition);
	spriteBrush->SetTransform(&mat);
	spriteBrush->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	scaling = D3DXVECTOR2(1.0f, 1.0f);
	spriteCentre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	rotation = 0.0f;

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &mousePosition);
	spriteBrush->SetTransform(&mat);
	spriteBrush->Draw(mouseTexture, &mouseRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	//	End sprite drawing
	spriteBrush->End();
	
	line->Begin();
	line->Draw(lineVertices, 2, D3DCOLOR_XRGB(255, 255, 255));
	line->End();

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
	
	font->Release();
	font = NULL;

	line->Release();
	line = NULL;

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
	InitializeLevel();                                                                

	FrameTimer *timer = new FrameTimer();

	timer->Init(30);
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
//--------------------------------------------------------------------