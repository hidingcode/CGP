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
#include <vector>

// Input
#include "Input.h"

// Background
#include "Background.h"

// Text and Box
#include "Text.h"
#include "Box.h"

// Game Object 
#include "Player.h"
#include "Enemy.h"

// Game Scene
#include "GameScene.h"

// Frame Timer
#include "FrameTimer.h"

// Audio Library
#include "AudioManager.h"

// Game State
#include "GameState.h"

// Main Menu
#include "MainMenu.h"

using namespace std;

#define WindowWidth 840
#define WindowHeight 650

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
LPD3DXSPRITE spriteBrush1 = NULL;
LPD3DXSPRITE spriteBrush2 = NULL;
// Line
LPD3DXLINE line = NULL;

// Input
Input* inputW = new Input();
Input* inputS = new Input();
Input* inputA = new Input();
Input* inputD = new Input();

// Background globals
Background* background1 = new Background(840, 650);

// Text and Box globals
Text* text = new Text();
Box* box = new Box();

// Number of zombie that will be spawn in the game
const int spawnNum = 10;

// Game Object globals
Player* F1 = new Player(768, 450, 3, 6, 5);
Enemy zombie[spawnNum];

MainMenu* mainMenu = new MainMenu();

// Audio globals
AudioManager* audioManager;

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
		}
		break;
		//	Default handling for other messages.
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
	wndClass.lpszClassName = "Zombie Saga F1";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	Register the window.
	RegisterClass(&wndClass);

	//	You are to refer to MSDN for each of the parameters details.
	//  Create instance of window
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Zombie Sage F1", WS_OVERLAPPEDWINDOW, 0, 0, WindowWidth, WindowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
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
	hr = D3DXCreateSprite(d3dDevice, &spriteBrush1);

	if (FAILED(hr)) {
		cout << "Create sprite 1 failed" << endl;
	}

	hr = D3DXCreateSprite(d3dDevice, &spriteBrush2);

	if (FAILED(hr)) {
		cout << "Create sprite 2 failed" << endl;
	}

	text->CreateFontType(d3dDevice, "Arial");

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
}

// !! Place to implement
void InitialiseLevel() {
	audioManager->PlaySoundTrack();
	audioManager->PlayCarSound();
	srand(time(0));

	//	Create texture
	background1->CreateTexture(d3dDevice, "Assets/roadBG.png");
	F1->CreateTexture(d3dDevice, "Assets/F1.png");
	mainMenu->CreateTexture(d3dDevice, "Assets/roadBG.png");

	//  Initialisation
	F1->Init(D3DXVECTOR2(395, 580), 1.0f, 0.0f, 2.0f, D3DXVECTOR2(0.4f,0.4f),0.05f, 0.05f);
	box->Init(120, 30, D3DXVECTOR2(10,10));
	text->Init(0,0,200,200);
	
	for (int i = 0; i < spawnNum; i++)
	{
		zombie[i] = Enemy(3774, 241, 1, 17, 16);
		zombie[i].CreateTexture(d3dDevice, "Assets/zombie_idle.png");

		cout << WindowWidth - zombie[i].GetSpriteWidth() << endl;
		D3DXVECTOR2 randomSpawn = D3DXVECTOR2(rand() % (WindowWidth - zombie[i].GetSpriteWidth() - 100), rand() % (WindowHeight - zombie[i].GetSpriteHeight() - 100));
		zombie[i].Init(randomSpawn, 0.0f, 0.0f, 1.0f, D3DXVECTOR2(0.3f, 0.3f), 0.0f, 0.01f, 20);
	}
	
}

void GetInput()
{	
	//	Acquire the device.
	dInputKeyboardDevice->Acquire();
	dInputMouseDevice->Acquire();
	//	Get immediate Keyboard Data.
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	// Get Mouse Data
	dInputMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);

	inputW->GetInput(diKeys, DIK_W);
	inputS->GetInput(diKeys, DIK_S);
	inputA->GetInput(diKeys, DIK_A);
	inputD->GetInput(diKeys, DIK_D);
}

void CarMoving()
{
	if (inputW->GetKeyPressed() == true || inputS->GetKeyPressed() == true)
	{
		bool pause = false;
		audioManager->ChangeState(pause);
	}

	else
	{
		cout << "i am not doing anything" << endl;
		bool pause = true;
		audioManager->ChangeState(pause);
	}
}

void Update(int framesToUpdate) {
	audioManager->UpdateSound();
	CarMoving();
	
	for (int i = 0; i < framesToUpdate; i++) {
		if (inputW->GetKeyPressed()) {
			F1->MovForward();
			F1->IncreaseFrameCounter();	
		}

		if (inputS->GetKeyPressed()) {
			F1->MovBackward();
		}

		if (inputA->GetKeyPressed()) {
			F1->TurnLeft();
		}

		if (inputD->GetKeyPressed()) {
			F1->TurnRight();
		}
	;
		for (int i = 0; i < spawnNum; i++)
		{	
			if (zombie[i].GetHP() <= 0)
			{
				zombie[i].~Enemy();
			}

			if (zombie[i].GetHP() > 0)
			{
				if (CircleCollisionDetection(F1->GetSpriteWidth() / 2, zombie[i].GetSpriteWidth() / 2, F1->GetPosition() + F1->GetSpriteCentre(), zombie[i].GetPosition() + zombie[i].GetSpriteCentre()))
				{
					F1->SetVelocity(F1->GetVelocity() / 2);
					cout << "Collision occurs" << endl;
					audioManager->PlayCollision();
					// Final Velocity of F1 after collision
					D3DXVECTOR2 f1FVelocity = F1->GetVelocity() * (F1->GetMass() - zombie[i].GetMass()) + 2 * zombie[i].GetMass() * zombie[i].GetVelocity() / (F1->GetMass() + zombie[i].GetMass());

					// Final Velocity of zombie after collision
					D3DXVECTOR2 zombieFVelocity = zombie[i].GetVelocity() * (zombie[i].GetMass() - F1->GetMass()) + 2 * F1->GetMass() * F1->GetVelocity() / (F1->GetMass() + zombie[i].GetMass());

					F1->SetVelocity(f1FVelocity);
					zombie[i].SetVelocity(zombieFVelocity);
					zombie[i].DecreaseHP(1);
				}
			}
			zombie[i].UpdatePhysics();
			zombie[i].UpdateAnim();
			zombie[i].CheckBoundary(WindowWidth, WindowHeight);
		}

		F1->UpdateAnim();
		F1->UpdatePhysics();
		F1->CheckBoundary(WindowWidth, WindowHeight);
	}
	inputW->SetKeyPressed(false);
	inputA->SetKeyPressed(false);
	inputS->SetKeyPressed(false);
	inputD->SetKeyPressed(false);
}

void Render() {
	//	Clear the back buffer.
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//	Begin the scene
	d3dDevice->BeginScene();

	//	Drawing.
	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	spriteBrush1->Begin(D3DXSPRITE_ALPHABLEND);
	spriteBrush2->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX mat;
	
	// Draw background
	/*background1->Render(spriteBrush1, &mat, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 0));*/
	// parallex scrolling
	/*background2->Render(spriteBrush, &mat, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 650));*/
	
	mainMenu->Render(spriteBrush1, &mat);

	// Draw F1
	F1->Render(spriteBrush1, &mat);
	
	// Draw Text
	text->Render(spriteBrush1, &mat, D3DXVECTOR2(1, 1), D3DXVECTOR2(1, 1), box->GetBoxPosition(), 0.0f,
		"Score: ", D3DCOLOR_XRGB(0, 0, 0));
	
	// Draw Zombie
	for (int i = 0; i < spawnNum; i++)
	{	
		if(zombie[i].GetHP() > 0)
		{
			zombie[i].Render(spriteBrush2, &mat);
		}
	}
	//	End sprite drawing
	spriteBrush1->End();
	spriteBrush2->End();

	// Draw Box
	box->Render(line, D3DCOLOR_XRGB(255, 0, 0));

	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void CleanupMyDx() {
	//	Release and clean up everything
	spriteBrush1->Release();
	spriteBrush1 = NULL;
	spriteBrush2->Release();
	spriteBrush2 = NULL;

	text->CleanUp();

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

void CleanupMyWindow() {
	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL)); // Delete window class
}

//	use WinMain if you don't want the console
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) // WinMain is a function in WINAPI
{
	CreateMyWindow();
	CreateMyDX();
	CreateMyDirectInput();

	GameState mainmenu = GameState();
	GameState level1 = GameState();
	vector<GameState*> gameState = {&mainmenu, &level1};

	audioManager = new AudioManager();
	audioManager->InitializeAudio();
	audioManager->LoadSounds();

	InitialiseLevel();

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

