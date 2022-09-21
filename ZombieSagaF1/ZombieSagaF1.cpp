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

//DeviceManagerClass
#include "D3D9DeviceManager.h"

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
//HWND g_hWnd = NULL;
// Window's Structure  /DESIGN PATTERN SINGLETON
WNDCLASS wndClass;

// DX globals
//IDirect3DDevice9* d3dDevice;

//WindowManagerClass
MyWindowManager* Window = new MyWindowManager();
D3D9DeviceManager* DeviceManager = new D3D9DeviceManager();


// Sprite Brush
//SpriteBrush* spriteBrush = new SpriteBrush();

/*LPD3DXSPRITE spriteBrush1 = NULL;
LPD3DXSPRITE spriteBrush2 = NULL;*/

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
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window->GetWindowHandle(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, DeviceManager->GetD3D9Dreference());

	if (FAILED(hr))
		cout << "Create Direct 3D 9 Device failed";

	//	Create sprite. Study the documentation. 
	hr = D3DXCreateSprite(DeviceManager->GetD3D9D(), DeviceManager->GetspriteBrush1reference());

	if (FAILED(hr)) {
		cout << "Create sprite brush 1 failed" << endl;
	}

	hr = D3DXCreateSprite(DeviceManager->GetD3D9D(), DeviceManager->GetspriteBrush2reference());

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
	
	gameLevel.front()->InitLevel(DeviceManager->GetD3D9D());
}

void Update(int framesToUpdate) {

}

void Render() {
	//	Clear the back buffer.

	DeviceManager->GetD3D9D()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//	Begin the scene
	DeviceManager->GetD3D9D()->BeginScene();

	//	Drawing.
	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	DeviceManager->GetspriteBrush1()->Begin(D3DXSPRITE_ALPHABLEND);
	DeviceManager->GetspriteBrush2()->Begin(D3DXSPRITE_ALPHABLEND);

	//	End the scene
	DeviceManager->GetD3D9D()->EndScene();

	//	Present the back buffer to screen
	DeviceManager->GetD3D9D()->Present(NULL, NULL, NULL, NULL);
}

void CleanupMyDirect3D9Device() {
	//	Release and clean up everything
	DeviceManager->GetspriteBrush1()->Release();
	/*DeviceManager->GetspriteBrush1() = NULL;*/
	DeviceManager->GetspriteBrush2()->Release();
	/*DeviceManager->GetspriteBrush1() = NULL;*/

	DeviceManager->GetTextReference()->CleanUpText();

	DeviceManager->GetBoxReference()->CleanUpLine();

	//	Release the device when exiting.
	DeviceManager->GetD3D9D()->Release();
	//	Reset pointer to NULL, a good practice.
	/*DeviceManager->GetD3D9D() = NULL;*/
}

//	use WinMain if you don't want the console
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) // WinMain is a function in WINAPI
{	
	Window->CreateMyWindow();
	//CreateDeviceManager
	
	DeviceManager->CreateMyD3D9Device(Window->GetWindowHandle(), WindowWidth, WindowHeight);
	/*CreateMyWindow();*/
	//CreateMyDirect3D9Device

	
	//CreateMyDirect3D9Device();
	inputManager->CreateMyDirectInput(Window->GetWindowHandle());

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
		/*Update(timer->FramesToUpdate());*/
		gameLevel.front()->Update(timer->FramesToUpdate(), inputManager, audioManager);
		gameLevel.front()->Render(DeviceManager->GetspriteBrush1(), DeviceManager->GetspriteBrush2(), DeviceManager->GetD3D9D());

	}
	gameLevel.front()->CleanUpLevel();
	inputManager->CleanUpMyDirectInput();
	DeviceManager->CleanUpMyD3D9Device(DeviceManager->GetD3D9D());
	Window->CleanupMyWindow();
	/*CleanupMyWindow();*/

	return 0;
}

