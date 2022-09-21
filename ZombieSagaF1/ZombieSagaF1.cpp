// Multibyte
// Not Set
// x86

//	Ask the compiler to include minimal header files for our program.
// #define -> Instruction to communicate with the compiler
#define WIN32_LEAN_AND_MEAN // Only include the skinny(LEAN) and powerful(MEAN) part of Windows.h

#include <Windows.h>
#include <d3d9.h>
#include <iostream>
#include <string>  
//	include the D3DX9 library
#include <d3dx9.h>

#include <ctime>
#include <vector>

// Sprite Brush and Input Manager
#include "SpriteBrush.h"
#include "InputManager.h"

//include windowClass
#include "MyWindowManager.h"

// Image
#include "Image.h"

// Text and Box
#include "Text.h"
#include "Box.h"

// Game Object 
#include "Player.h"
#include "Enemy.h"

// Frame Timer
#include "FrameTimer.h"

// Audio Library
#include "AudioManager.h"

// Game State (Level control)
#include "GameLevel.h"
#include "MainMenu.h"
#include "Level1.h"

// Main Menu
#include "UI.h"

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
MyWindowManager* Window = new MyWindowManager();

// Sprite Brush
//SpriteBrush* spriteBrush = new SpriteBrush();

LPD3DXSPRITE spriteBrush1 = NULL;
LPD3DXSPRITE spriteBrush2 = NULL;

// Input Manager
InputManager* inputManager = new InputManager();

Level1 level1 =  Level1();
vector<GameLevel*> gameLevel;

UI* mainmenuUI = new UI();

// Audio globals
AudioManager* audioManager;

Button* test = new Button();


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

}

void SetInput()
{
	// Add Key Codes to Input Manager
	inputManager->AddKey(DIK_W);
	inputManager->AddKey(DIK_S);
	inputManager->AddKey(DIK_A);
	inputManager->AddKey(DIK_D);
}

void InitialiseLevel() {
	audioManager->PlayBackgroundMusic();
	audioManager->PlayCarEngineSound();
	
	level1.InitLevel(d3dDevice);
}

void Update(int framesToUpdate) {

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

	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;
}

//	use WinMain if you don't want the console
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) // WinMain is a function in WINAPI
{	
	Window->CreateMyWindow();
	CreateMyDirect3D9Device();
	inputManager->CreateMyDirectInput(g_hWnd);

	audioManager = new AudioManager();
	audioManager->InitialiseAudio();
	audioManager->LoadSounds();	
	SetInput();
	gameLevel.push_back(&level1);
	InitialiseLevel();

	FrameTimer* timer = new FrameTimer();
	timer->Init(20);
	while (Window->IsWindowRunning())
	{
		inputManager->GetInput();
		gameLevel.front()->Update(timer->FramesToUpdate(), inputManager, audioManager);
		gameLevel.front()->Render(spriteBrush1, spriteBrush2, d3dDevice);
	}
	gameLevel.front()->CleanUpLevel();
	inputManager->CleanUpMyDirectInput();
	CleanupMyDirect3D9Device();
	Window->CleanUpMyWindow();

	return 0;
}

