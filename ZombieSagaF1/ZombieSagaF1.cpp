// Multibyte
// Not Set
// x86

//	Ask the compiler to include minimal header files for our program.
// #define -> Instruction to communicate with the compiler
#include <d3d9.h>
#include <iostream>
#include <string>  
//	include the D3DX9 library
#include <d3dx9.h>

#include <ctime>
#include <vector>

// Sprite Brush and Input Manager
#include "InputManager.h"
//include windowClass
#include "MyWindowManager.h"
//DeviceManagerClass
#include "D3D9DeviceManager.h"
// Audio Library
#include "AudioManager.h"

// Frame Timer
#include "FrameTimer.h"

// Game State (Level control)
#include "GameStateManager.h"
#include "GameState.h"
#include "MainMenu.h"
#include "Level1.h"

using namespace std;

#define WindowWidth 840
#define WindowHeight 650

#pragma comment(lib, "d3d9.lib ")
#pragma comment(lib, "d3dx9.lib ")
#pragma comment(lib, "dinput8.lib ")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "fmod_vc.lib")
//--------------------------------------------------------------------

//WindowManagerClass
MyWindowManager* windowManager = new MyWindowManager();
D3D9DeviceManager* deviceManager = new D3D9DeviceManager();

// Input Manager
InputManager* inputManager = new InputManager();

// Game Level
vector<GameState*> gameState;
MainMenu mainMenu = MainMenu();
Level1 level1 =  Level1();

// Audio globals
AudioManager* audioManager;

void SetInput()
{
	// Add Key Codes to Input Manager
	inputManager->AddKey(DIK_W);
	inputManager->AddKey(DIK_S);
	inputManager->AddKey(DIK_A);
	inputManager->AddKey(DIK_D);
	// Testing
	inputManager->AddKey(DIK_P);
	inputManager->AddKey(DIK_O);
	inputManager->AddKey(DIK_I);
	inputManager->AddKey(DIK_U);
}

void InitAudio()
{
	audioManager = new AudioManager();
	audioManager->InitialiseAudio();
	audioManager->LoadSounds();
}

void InitLevel() 
{	
	// First level 
	//gameState.push_back(&mainMenu);

	audioManager->PlayBackgroundMusic();
	audioManager->PlayCarEngineSound();

	mainMenu.InitLevel(deviceManager->GetD3D9Device(), windowManager);
	//level1.InitLevel(deviceManager->GetD3D9Device());
}

// Manage which level to be unload and load
void LevelManager()
{
	//if (gameState.back()->GetLevelState() == 1)
	//{
	//	gameState.pop_back();
	//	gameState.push_back(&level1);
	//}

	//if (gameState.back()->GetLevelState() == 2)
	//{	
	//	gameState.pop_back();
	//	gameState.push_back(&mainMenu);
	//}

	//if (gameState.front()->GetLevelState() == 3)
	//{
	//	gameState.pop_back();
	//	gameState.push_back(&level1);
	//}

	//if (gameState.front()->GetLevelState() == 4)
	//{
	//	gameState.pop_back();
	//	gameState.push_back(&mainMenu);
	//}
}

void Render() 
{
	deviceManager->BeginRender();
	deviceManager->BeginSpriteBrush();

	gameState.back()->Render(deviceManager->GetSpriteBrush());

	deviceManager->EndSpriteBrush();

	gameState.back()->RenderLine();

	deviceManager->PresentBuffer();
}

//	use WinMain if you don't want the console
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) // WinMain is a function in WINAPI
{	
	windowManager->CreateMyWindow(WindowWidth, WindowHeight);
	deviceManager->CreateMyD3D9Device(windowManager->GetWindowHandle(), WindowWidth, WindowHeight);
	inputManager->CreateMyDirectInput(windowManager->GetWindowHandle());
	SetInput();
	InitAudio();
	InitLevel();

	gameState.push_back(&mainMenu);

	FrameTimer* timer = new FrameTimer();
	timer->Init(20);
	while (windowManager->IsWindowRunning())
	{	
		inputManager->GetInput();
		gameState.back()->Update(timer->FramesToUpdate(), inputManager, audioManager, gameState, windowManager);
		Render();
	}
	gameState.back()->CleanUpLevel();
	inputManager->CleanUpMyDirectInput();
	deviceManager->CleanUpMyD3D9Device();
	windowManager->CleanUpMyWindow();

	return 0;
}

