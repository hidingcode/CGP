#ifndef GAMEHEADER_H
#define GAMEHEADER_H

#define WindowWidth 840
#define WindowHeight 650

using namespace std;

#include <vector>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <iostream>
#include <string>
#include "AudioManager.h"
// Input Manager
#include "InputManager.h"
#include "GameState.h"

extern AudioManager* audioManager;
extern InputManager* inputManager;
extern vector<GameState*> gameState;

#pragma comment (lib, "d3d9.lib") 
#pragma comment (lib, "d3dx9.lib") 
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "fmod_vc.lib")

#endif