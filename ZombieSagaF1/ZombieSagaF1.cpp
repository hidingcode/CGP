// Multibyte
// Not Set
// x86

//	Ask the compiler to include minimal header files for our program.
// #define -> Instruction to communicate with the compiler
#define WIN32_LEAN_AND_MEAN // Only include the skinny(LEAN) and powerful(MEAN) part of Windows.h

#include <Windows.h>
#include <d3d9.h>
#include <iostream>
#include<string>  
//	include the D3DX9 library
#include <d3dx9.h>

#include <ctime>
#include <vector>

// Sprite Brush and Input Manager
#include "SpriteBrush.h"
#include "InputManager.h"

//include windowClass
#include "MyWindowManager.h"

// ScoreBoard
#include "ScoreBoard.h"

// Image
#include "Image.h"

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

//WindowManagerClass
MyWindowManager* Window = new MyWindowManager;

// Sprite Brush
SpriteBrush* spriteBrush = new SpriteBrush();

LPD3DXSPRITE spriteBrush1 = NULL;
LPD3DXSPRITE spriteBrush2 = NULL;

// Input Manager
InputManager* inputManager = new InputManager();

//ScoreBoard Global
ScoreBoard* scoreBoard = new ScoreBoard();

// Image globals
Image* background = new Image();

// Text and Box globals
Text* text = new Text();
Box* box = new Box();

// Number of zombie that will be spawn in the game
const int spawnNum = 5;

// Game Object globals
Player* F1 = new Player();
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
	F1->CleanUpSprite();
	for (int i = 0; i < spawnNum; i++)
	{
		zombie[i].CleanUpSprite();
	}
}

void CreateMyDirect3D9Device() {
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
	d3dPP.hDeviceWindow = Window->GetWindowHandle();

	//	Create a Direct3D 9 device.
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

	if (FAILED(hr))
		cout << "Create Direct 3D 9 Device failed";

	//	Create sprite. Study the documentation. 
	hr = D3DXCreateSprite(d3dDevice, &spriteBrush1);

	if (FAILED(hr)) {
		cout << "Create sprite brush 1 failed" << endl;
	}

	hr = D3DXCreateSprite(d3dDevice, &spriteBrush2);

	if (FAILED(hr)) {
		cout << "Create sprite brush 2 failed" << endl;
	}

	text->CreateFontType(d3dDevice, "Arial");

	box->CreateLine(d3dDevice);
}

void InitialiseLevel() {
	audioManager->PlayBackgroundMusic();
	audioManager->StartCarEngineSound();
	srand(time(0));

	// Add Key Codes to Input Manager
	inputManager->AddKeyCodes(DIK_W);
	inputManager->AddKeyCodes(DIK_S);
	inputManager->AddKeyCodes(DIK_A);
	inputManager->AddKeyCodes(DIK_D);

	//	Create texture
	mainMenu->CreateTexture(d3dDevice, "Assets/roadBG.png");
	background->CreateTexture(d3dDevice, "Assets/roadBG.png");
	F1->CreateTexture(d3dDevice, "Assets/F1.png");
	mainMenu->CreateTexture(d3dDevice, "Assets/mainMenu.png");
	mainMenu->Init(840, 650, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(255, 255, 255));

	//  Initialisation
	F1->Init(768, 450, 3, 6, 5, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(395, 580), 1.0f, 0.0f, 2.0f,
		D3DXVECTOR2(0.4f,0.4f),0.05f, 0.05f, D3DCOLOR_XRGB(255, 255, 255));

	box->Init(120, 30, D3DXVECTOR2(10,10));

	text->Init(200,200, D3DXVECTOR2(1,1), 0.0f ,D3DXVECTOR2(1, 1), text->GetPosition(), 0.0f, 
		box->GetBoxPosition(), -1, 0 ,D3DCOLOR_XRGB(0, 0, 0));

	background->Init(840, 650, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(255,255,255));
	
	for (int i = 0; i < spawnNum; i++)
	{
		zombie[i] = Enemy();
		zombie[i].CreateTexture(d3dDevice, "Assets/zombie_idle.png");
		D3DXVECTOR2 randomSpawn = D3DXVECTOR2(rand() % (WindowWidth - zombie[i].GetSpriteWidth() - 100),
			rand() % (WindowHeight - zombie[i].GetSpriteHeight() - 100));

		zombie[i].Init(3774, 241, 1, 17, 16, D3DXVECTOR2(0, 0), 0.0f, randomSpawn, 0.0f, 0.0f, 1.0f,
			D3DXVECTOR2(0.3f, 0.3f), 0.0f, 0.01f, D3DCOLOR_XRGB(255, 255, 255), 2);
	}
}

void Update(int framesToUpdate) {
	audioManager->UpdateSound();
	audioManager->DynamicCarEngineSound(inputManager->GetKeyPress(DIK_W), inputManager->GetKeyPress(DIK_S));

	//test
	//cout << "spriteX_width: " << F1->GetSpriteWidth() / 2 << " spriteX_Height: " << F1->GetSpriteHeight() / 2 << endl;
	
	for (int i = 0; i < framesToUpdate; i++) {
		if (inputManager->GetKeyPress(DIK_W)) {
			F1->MovForward();
		}

		if (inputManager->GetKeyPress(DIK_S)) {
			F1->MovBackward();
		}

		if (inputManager->GetKeyPress(DIK_A)) {
			F1->TurnLeft();
		}

		if (inputManager->GetKeyPress(DIK_D)) {
			F1->TurnRight();
		}

		for (int i = 0; i < spawnNum; i++)
		{	
			if (zombie[i].GetHP() > 0)
			{
				if (CircleCollisionDetection(F1->GetSpriteWidth() / 2, zombie[i].GetSpriteWidth() / 2, F1->GetPosition() /* + F1->GetSpriteCentre()*/, zombie[i].GetPosition()/* + zombie[i].GetSpriteCentre()*/))
				{
					cout << "Collision occurs" << endl;
					audioManager->PlayCollisionSound();
					// testing stuff:
					/*float fDistance = sqrtf((F1->GetPosition().x - zombie[i].GetPosition().x) * (F1->GetPosition().x - zombie[i].GetPosition().x) + (F1->GetPosition().y - zombie[i].GetPosition().y) * (F1->GetPosition().y - zombie[i].GetPosition().y));
					float fOverlap = 0.5f * (fDistance - (F1->GetSpriteWidth() / 2) - (zombie[i].GetSpriteWidth() / 2));

					//bounce distance to prevent overlapping
					 bounceDistanceX = fOverlap * (F1->GetPosition().x - zombie[i].GetPosition().x) / fDistance;
					 bounceDistanceY = fOverlap * (F1->GetPosition().y - zombie[i].GetPosition().y) / fDistance;*/

					// Final Velocity of F1 after collision
					D3DXVECTOR2 f1FVelocity = F1->GetVelocity() * (F1->GetMass() - zombie[i].GetMass()) + 2 * zombie[i].GetMass() * zombie[i].GetVelocity() / (F1->GetMass() + zombie[i].GetMass());

					// Calculate the bouncing vector of zombie after collision
					D3DXVECTOR2 zombieFVelocity = zombie[i].GetVelocity() * (zombie[i].GetMass() - F1->GetMass()) + 2 * F1->GetMass() * F1->GetVelocity() / (F1->GetMass() + zombie[i].GetMass());

					F1->SetVelocity(-f1FVelocity);
					zombie[i].SetVelocity(zombieFVelocity);
					zombie[i].DecreaseHP(1);
					scoreBoard->IncreaseScore(10);
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
	inputManager->SetAllKeyPressToFalse();
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
	/*background->RenderSprite(spriteBrush1, &mat);*/
	mainMenu->Render(spriteBrush1, &mat);

	// Draw F1
	F1->RenderSprite(spriteBrush1, &mat);

	// Draw Text
	// .c_str() is to change the score to LPCSTR
	text->RenderText(spriteBrush1, &mat, scoreBoard->DisplayScore().c_str());
	
	// Draw Zombie
	for (int i = 0; i < spawnNum; i++)
	{	
		if(zombie[i].GetHP() > 0)
		{
			zombie[i].RenderSprite(spriteBrush2, &mat);
		}
	}
	//	End sprite drawing
	spriteBrush1->End();
	spriteBrush2->End();

	// Draw Box
	box->RenderLine(D3DCOLOR_XRGB(255, 0, 0));

	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void CleanupMyDirect3D9Device() {
	//	Release and clean up everything
	spriteBrush1->Release();
	spriteBrush1 = NULL;
	spriteBrush2->Release();
	spriteBrush2 = NULL;

	text->CleanUpText();

	box->CleanUpLine();

	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;
}

void CleanupMyWindow() {
	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL)); // Delete window class
}

//	use WinMain if you don't want the console
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) // WinMain is a function in WINAPI
{	
	Window->CreateMyWindow();
	/*CreateMyWindow();*/
	CreateMyDirect3D9Device();
	inputManager->CreateMyDirectInput(g_hWnd);

	/*GameState mainmenu = GameState();
	GameState level1 = GameState();
	vector<GameState*> gameState = {&mainmenu, &level1};*/

	audioManager = new AudioManager();
	audioManager->InitialiseAudio();
	audioManager->LoadSounds();

	InitialiseLevel();

	FrameTimer* timer = new FrameTimer();

	timer->Init(20);
	while (WindowIsRunning())
	{
		inputManager->GetInput();
		Update(timer->FramesToUpdate());
		Render();
	}

	CleanupMyLevel();
	inputManager->CleanUpMyDirectInput();
	CleanupMyDirect3D9Device();
	/*CleanupMyWindow();*/

	return 0;
}

