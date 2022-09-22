#pragma once
#include <d3dx9.h>
#include "MyWindowManager.h"
#include "InputManager.h"
#include "AudioManager.h"

class GameLevel
{
public:
	virtual void InitLevel(IDirect3DDevice9* d3dDevice);
	virtual	void Update(int framesToUpdate, InputManager* inputManager, AudioManager* audioManager);
	virtual void Render(LPD3DXSPRITE spriteBrush, IDirect3DDevice9* d3dDevice);
	virtual void RenderLine();
	virtual void CleanUpLevel();
};

