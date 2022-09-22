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

// Frame Timer
#include "FrameTimer.h"

// Audio Library
#include "AudioManager.h"

// Game State (Level control)
#include "GameLevel.h"
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
MyWindowManager* myWindowManager = new MyWindowManager();
D3D9DeviceManager* deviceManager = new D3D9DeviceManager();

// Input Manager
InputManager* inputManager = new InputManager();

// Game Level
vector<GameLevel*> gameLevel;
MainMenu mainMenu = MainMenu();
Level1 level1 =  Level1();

// Audio globals
AudioManager* audioManager;

Button* test = new Button();

void SetInput()
{
	// Add Key Codes to Input Manager
	inputManager->AddKey(DIK_W);
	inputManager->AddKey(DIK_S);
	inputManager->AddKey(DIK_A);
	inputManager->AddKey(DIK_D);
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
	gameLevel.push_back(&mainMenu);

	audioManager->PlayBackgroundMusic();
	audioManager->PlayCarEngineSound();

	mainMenu.InitLevel(deviceManager->GetD3D9Device());
	level1.InitLevel(deviceManager->GetD3D9Device());
}

// Manage which level to be unload and load
void LevelManager()
{
	if (gameLevel.front()->GetLevelState() == 1)
	{
		gameLevel.pop_back();
		gameLevel.push_back(&level1);
	}

	if (gameLevel.front()->GetLevelState() == 2)
	{	
		gameLevel.pop_back();
		gameLevel.push_back(&mainMenu);
	}

	if (gameLevel.front()->GetLevelState() == 3)
	{
		gameLevel.pop_back();
		gameLevel.push_back(&level1);
	}

	if (gameLevel.front()->GetLevelState() == 4)
	{
		gameLevel.pop_back();
		gameLevel.push_back(&mainMenu);
	}
}

void Render() 
{
	deviceManager->BeginRender();
	deviceManager->BeginSpriteBrush();

	gameLevel.front()->Render(deviceManager->GetSpriteBrush());

	deviceManager->EndSpriteBrush();

	gameLevel.front()->RenderLine();

	deviceManager->PresentBuffer();
}

//	use WinMain if you don't want the console
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) // WinMain is a function in WINAPI
{	
	myWindowManager->CreateMyWindow(WindowWidth, WindowHeight);
	deviceManager->CreateMyD3D9Device(myWindowManager->GetWindowHandle(), WindowWidth, WindowHeight);
	inputManager->CreateMyDirectInput(myWindowManager->GetWindowHandle());

	SetInput();
	InitAudio();
	InitLevel();

	FrameTimer* timer = new FrameTimer();
	timer->Init(20);
	while (myWindowManager->IsWindowRunning())
	{	
		LevelManager();
		inputManager->GetInput();
		gameLevel.front()->Update(timer->FramesToUpdate(), inputManager, audioManager, gameLevel);
		Render();
	}
	gameLevel.front()->CleanUpLevel();
	inputManager->CleanUpMyDirectInput();
	deviceManager->CleanUpMyD3D9Device();
	myWindowManager->CleanUpMyWindow();

	return 0;
}

