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
#include <ctime>
#include "Audio.h"

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

Audio* audioManager;

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
LPD3DXSPRITE spriteBrush = NULL;

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
	playerTexture->Release();
	playerTexture = NULL;
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

	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	mousePosition.x = WindowWidth / 2;
	mousePosition.y = WindowHeight / 2;

}

// !! Place to implement
void InitializeLevel() {

	srand(time(0));

	audioManager->PlaySoundTrack();

	//	Create texture. Study the documentation.
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, "Assets/spaceship.png", &playerTexture);
	hr = D3DXCreateTextureFromFile(d3dDevice, "Assets/pointer.png", &mouseTexture);
	//load mass
	hr = D3DXCreateTextureFromFile(d3dDevice, "Assets/mass.png", &massTexture);

	//hr = D3DXCreateTextureFromFileEx(/* Your Direct3D device */, "01.bmp", D3DX_DEFAULT, D3DX_DEFAULT, 
	//									D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
	//									D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), 
	//									NULL, NULL, &texture);
	if (FAILED(hr)) {
		cout << "Create texture failed" << endl;
	}

	playerTextureWidth = 64;
	playerTextureHeight = 64;
	playerTextureRow = 2;
	playerTextureColumn = 2;
	playerSpriteWidth = playerTextureWidth / playerTextureColumn;
	playerSpriteHeight = playerTextureHeight / playerTextureRow;
	playerSpriteFPS = 10;
	playerMaxFrame = 1;
	friction = 0.01;

	// Player 1
	player1ID = 1;

	player1AnimRect.left = (player1ID - 1) * playerSpriteWidth;
	player1AnimRect.right = player1AnimRect.left + playerSpriteWidth;
	player1AnimRect.top = 0;
	player1AnimRect.bottom = player1AnimRect.top + playerSpriteHeight;

	player1ColRect.left = 0;
	player1ColRect.right = player1ColRect.left + playerSpriteWidth;
	player1ColRect.top = 0;
	player1ColRect.bottom = player1ColRect.top + playerSpriteHeight;

	player1Position = D3DXVECTOR2(100, 300);
	player1Velocity = D3DXVECTOR2(0, 0);
	player1Acceleration = D3DXVECTOR2(0, 0);
	player1EngineForce = 1;
	player1Direction = 0;
	player1Mass = 1;
	player1FrameCounter = 0;

	player1Scaling = D3DXVECTOR2(1, 1);
	player1SpriteCentre = D3DXVECTOR2(playerSpriteWidth / 2, playerSpriteHeight / 2);
	player1RotationSpeed = 0.05;
	player1HP = 1;

	//	Player 2
	player2ID = 2;

	player2AnimRect.left = (player2ID - 1) * playerSpriteWidth;
	player2AnimRect.right = player2AnimRect.left + playerSpriteWidth;
	player2AnimRect.top = 0;
	player2AnimRect.bottom = player2AnimRect.top + playerSpriteHeight;

	player2ColRect.left = 0;
	player2ColRect.right = player2ColRect.left + playerSpriteWidth;
	player2ColRect.top = 0;
	player2ColRect.bottom = player2ColRect.top + playerSpriteHeight;

	player2Position = D3DXVECTOR2(700, 300);
	player2Velocity = D3DXVECTOR2(0, 0);
	player2Acceleration = D3DXVECTOR2(0, 0);
	player2EngineForce = 1;
	player2Direction = 0;
	player2Mass = 1;
	player2FrameCounter = 0;

	player2Scaling = D3DXVECTOR2(1, 1);
	player2SpriteCentre = D3DXVECTOR2(playerSpriteWidth / 2, playerSpriteHeight / 2);
	player2RotationSpeed = 0.05;
	player2HP = 1;

	// Mass Initialize
	massTextureWidth = 32;
	massTextureHeight = 32;
	massTextureRow = 4;
	massTextureColumn = 4;
	massSpriteWidth = 9;
	massSpriteHeight = 9;
	massSpriteFPS = 10;
	massMaxFrame = 0;

	// mass 1
	mass1AnimRect.left = 0;
	mass1AnimRect.right = mass1AnimRect.left + massSpriteWidth;
	mass1AnimRect.top = 0;
	mass1AnimRect.bottom = mass1AnimRect.top + massSpriteHeight;

	mass1ColRect.left = 0;
	mass1ColRect.right = mass1ColRect.left + massSpriteWidth;
	mass1ColRect.top = 0;
	mass1ColRect.bottom = mass1ColRect.top + massSpriteHeight;

	mass1Position = D3DXVECTOR2(rand() % WindowWidth - massSpriteWidth, rand() % WindowWidth - massSpriteHeight);
	mass1Velocity = D3DXVECTOR2(0, 0);
	mass1Acceleration = D3DXVECTOR2(0, 0);
	mass1EngineForce = 0;
	mass1Direction = 0;
	mass1Mass = 1;
	mass1FrameCounter = 0;

	mass1Scaling = D3DXVECTOR2(1, 1);
	mass1SpriteCentre = D3DXVECTOR2(massSpriteWidth / 2, massSpriteHeight / 2);
	mass1RotationSpeed = 0;
	mass1HP = 1;

	//	mass 2
	mass2AnimRect.left = 0;
	mass2AnimRect.right = mass2AnimRect.left + massSpriteWidth;
	mass2AnimRect.top = 0;
	mass2AnimRect.bottom = mass2AnimRect.top + massSpriteHeight;

	mass2ColRect.left = 0;
	mass2ColRect.right = mass2ColRect.left + massSpriteWidth;
	mass2ColRect.top = 0;
	mass2ColRect.bottom = mass2ColRect.top + massSpriteHeight;

	mass2Position = D3DXVECTOR2(rand() % WindowWidth - massSpriteWidth, rand() % WindowWidth - massSpriteHeight);
	mass2Velocity = D3DXVECTOR2(0, 0);
	mass2Acceleration = D3DXVECTOR2(0, 0);
	mass2EngineForce = 0;
	mass2Direction = 0;
	mass2Mass = 1;
	mass2FrameCounter = 0;

	mass2Scaling = D3DXVECTOR2(1, 1);
	mass2SpriteCentre = D3DXVECTOR2(massSpriteWidth / 2, massSpriteHeight / 2);
	mass2RotationSpeed = 0;
	mass2HP = 1;

	// Mouse
	mouseRect.left = 0;
	mouseRect.top = 0;
	mouseRect.right = 32;
	mouseRect.bottom = 32;
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
	audioManager->UpdateSound();

	for (int i = 0; i < framesToUpdate; i++) {
		/*counter++;*/

		if (aKeyPressed) {
			player1Direction -= player1RotationSpeed;
		}

		if (dKeyPressed) {
			player1Direction += player1RotationSpeed;
		}

		if (wKeyPressed) {
			/*if (counter % timer->getFPS() / player1SpriteFPS) {
				player1FrameCounter++
			}*/
			player1FrameCounter++;

			player1Acceleration.x = sin(player1Direction) * player1EngineForce / player1Mass;
			player1Acceleration.y = -cos(player1Direction) * player1EngineForce / player1Mass;
		}

		if (sKeyPressed) {
			player1FrameCounter++;

			player1Acceleration.x = -sin(player1Direction) * player1EngineForce / player1Mass;
			player1Acceleration.y = cos(player1Direction) * player1EngineForce / player1Mass;
		}

		if (leftKeyPressed) {
			player2Direction -= player2RotationSpeed;
		}

		if (rightKeyPressed) {
			player2Direction += player2RotationSpeed;
		}

		if (upKeyPressed) {
			/*if (counter % timer->getFPS() / player1SpriteFPS) {
				player1FrameCounter++
			}*/
			player2FrameCounter++;

			player2Acceleration.x = sin(player2Direction) * player2EngineForce / player2Mass;
			player2Acceleration.y = -cos(player2Direction) * player2EngineForce / player2Mass;
		}

		if (downKeyPressed) {
			player2FrameCounter++;

			player2Acceleration.x = -sin(player2Direction) * player2EngineForce / player2Mass;
			player2Acceleration.y = cos(player2Direction) * player2EngineForce / player2Mass;
		}

		player1Velocity += player1Acceleration;
		//friction
		player1Velocity *= 1 - friction;
		player1Position += player1Velocity;

		player2Velocity += player2Acceleration;
		//friction
		player2Velocity *= 1 - friction;
		player2Position += player2Velocity;

		if (CircleCollisionDetection(playerSpriteWidth / 2, playerSpriteWidth / 2, player1Position + player1SpriteCentre, player2Position + player2SpriteCentre))
		{
			player1HP -= 0;
			player1Velocity.x *= -1;
			player1Velocity.y *= -1;

			/*player2Position.x -= player1Velocity.x;
			player2Position.y -= player1Velocity.y;*/
			cout << "Collision detected between spaceship" << endl;

			// find the angle
			// perpendicular to the vector
		}

		if (mass1HP > 0)
		{
			if (CircleCollisionDetection(playerSpriteWidth / 2, playerSpriteWidth / 2, player1Position, mass1Position + mass1SpriteCentre))
			{
				player1Mass += mass1Mass;
				mass1HP = 0;
				audioManager->PlaySound1();
				cout << "Collision detected with mass 1" << endl;
			}
		}

		if (mass2HP > 0)
		{
			if (CircleCollisionDetection(playerSpriteWidth / 2, playerSpriteWidth / 2, player1Position, mass2Position + mass2SpriteCentre))
			{
				player1Mass += mass2Mass;
				mass2HP = 0;
				cout << "Collision detected with mass 2" << endl;
			}
		}

		if (player1FrameCounter > playerMaxFrame) {
			player1FrameCounter = 0;
		}

		player1AnimRect.left = (player1ID - 1) * playerSpriteWidth;
		player1AnimRect.top = player1FrameCounter * playerSpriteHeight;
		player1AnimRect.right = player1AnimRect.left + playerSpriteWidth;
		player1AnimRect.bottom = player1AnimRect.top + playerSpriteHeight;

		if (player2FrameCounter > playerMaxFrame) {
			player2FrameCounter = 0;
		}

		player2AnimRect.left = (player2ID - 1) * playerSpriteWidth;
		player2AnimRect.top = player2FrameCounter * playerSpriteHeight;
		player2AnimRect.right = player2AnimRect.left + playerSpriteWidth;
		player2AnimRect.bottom = player2AnimRect.top + playerSpriteHeight;

		// boundry
		if (player1Position.x <0 || player1Position.x > WindowWidth - playerSpriteWidth) {
			player1Velocity.x *= -1;
		}
		if (player1Position.y <0 || player1Position.y > WindowHeight - playerSpriteHeight) {
			player1Velocity.y *= -1;
		}
		if (player2Position.x <0 || player2Position.x > WindowWidth - playerSpriteWidth) {
			player2Velocity.x *= -1;
		}
		if (player2Position.y <0 || player2Position.y > WindowHeight - playerSpriteHeight) {
			player2Velocity.y *= -1;
		}

	}
	leftKeyPressed = false;
	rightKeyPressed = false;
	upKeyPressed = false;
	downKeyPressed = false;
	aKeyPressed = false;
	dKeyPressed = false;
	wKeyPressed = false;
	sKeyPressed = false;

	player1Acceleration = D3DXVECTOR2(0, 0);
	player2Acceleration = D3DXVECTOR2(0, 0);
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

	/*D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &fontPosition);
	spriteBrush->SetTransform(&mat);
	font->DrawText(spriteBrush, "Hello World!", -1, &textRect, 0, D3DCOLOR_XRGB(255, 255, 255));*/

	D3DXMATRIX mat;

	// draw Player 1
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &player1Scaling, &player1SpriteCentre, player1Direction, &player1Position);
	spriteBrush->SetTransform(&mat);
	spriteBrush->Draw(playerTexture, &player1AnimRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	// draw Player 2
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &player2Scaling, &player2SpriteCentre, player2Direction, &player2Position);
	spriteBrush->SetTransform(&mat);
	spriteBrush->Draw(playerTexture, &player2AnimRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	if (mass1HP > 0)
	{
		// draw Mass 1
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &mass1Scaling, &mass1SpriteCentre, mass1Direction, &mass1Position);
		spriteBrush->SetTransform(&mat);
		spriteBrush->Draw(massTexture, &mass1AnimRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}

	if (mass2HP > 0)
	{
		// draw Mass 2
		D3DXMatrixTransformation2D(&mat, NULL, 0.0, &mass2Scaling, &mass2SpriteCentre, mass2Direction, &mass2Position);
		spriteBrush->SetTransform(&mat);
		spriteBrush->Draw(massTexture, &mass2AnimRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	}


	//D3DXMatrixTransformation2D(&mat, NULL, 0.0, D3DXVECTOR3(1,1), D3DXVECTOR3(WindowWidth/2, WindowHeight/2), 0, &mousePosition);
	//spriteBrush->SetTransform(&mat);
	//spriteBrush->Draw(mouseTexture, &mouseRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

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

	audioManager = new Audio();
	audioManager->InitializeAudio();
	audioManager->LoadSounds();

	InitializeLevel();

	FrameTimer* timer = new FrameTimer();

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