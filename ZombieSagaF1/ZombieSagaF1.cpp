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

// Framer Timer
FrameTimer* timer = new FrameTimer();

// Game Level
vector<GameState*> gameState;
MainMenu mainMenu = MainMenu();
Level1 level1 =  Level1();

// Audio globals
AudioManager* audioManager = new AudioManager();

// Set Input
void SetInput()
{
	// Add Key Codes to Input Manager
	inputManager->AddKey(DIK_W);
	inputManager->AddKey(DIK_S);
	inputManager->AddKey(DIK_A);
	inputManager->AddKey(DIK_D);
	inputManager->AddKey(DIK_0);
	inputManager->AddKey(DIK_9);
	// Testing
	inputManager->AddKey(DIK_P);
}

// Initialise audio
void InitAudio()
{
	audioManager->InitialiseAudio();
	audioManager->LoadSounds();
	audioManager->PlayBackgroundMusic();
	audioManager->PlayCarEngineSound();
}

void Init()
{
	SetInput();
	InitAudio();
	// Push main menu to the back of the stack
	gameState.push_back(&mainMenu);
	// Get the back of the game state stack  
	gameState.back()->InitLevel(deviceManager->GetD3D9Device(), windowManager);
}

// Change the state of background musci to muted or unmuted
void HandleBGMusic()
{
	if (inputManager->GetKeyPress(DIK_0))
	{
		audioManager->ChangeMuteState(true);
	}

	if (inputManager->GetKeyPress(DIK_9))
	{
		audioManager->ChangeMuteState(false);
	}
}

void Update(int framesToUpdate)
{
	HandleBGMusic();
	for (int i = 0; i < framesToUpdate; i++) {
		// Get the back of the game state stack  
		gameState.back()->Update(inputManager, audioManager, gameState,
			windowManager);
	}
}

void Render()
{
	deviceManager->BeginRender();
	deviceManager->BeginSpriteBrush();

	gameState.back()->Render(deviceManager->GetSpriteBrush());

	deviceManager->EndSpriteBrush();
	// End the sprite brush before draw the line to allow line to be 
	// drawn in front of sprite or text
	gameState.back()->RenderLine();

	deviceManager->PresentBuffer();
}

// Clean Up Level, Direct Input, Virtual Graphic Card and Window
void CleanUp()
{
	gameState.back()->CleanUpLevel();
	inputManager->CleanUpMyDirectInput();
	deviceManager->CleanUpMyD3D9Device();
	windowManager->CleanUpMyWindow();
}

//	use WinMain if you don't want the console
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) // WinMain is a function in WINAPI
{
	// Create Window
	windowManager->CreateMyWindow();
	// Create virtual graphic card
	deviceManager->CreateMyD3D9Device(windowManager->GetWindowHandle());
	// Create direct input
	inputManager->CreateMyDirectInput(windowManager->GetWindowHandle());
	// Initialise input,audio, level
	Init();

	// Set the game fps
	timer->Init(20);

	while (windowManager->IsWindowRunning())
	{
		inputManager->GetInput();
		Update(timer->FramesToUpdate());
		Render();
	}

	CleanUp();
	return 0;
}

