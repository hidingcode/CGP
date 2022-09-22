#pragma once
#include <d3dx9.h>
#include "MyWindowManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "GameLevel.h"

class GameLevel
{
public:
	virtual void InitLevel(IDirect3DDevice9* d3dDevice);
	virtual	void Update(int framesToUpdate, InputManager* inputManager, AudioManager* audioManager, 
		vector<GameLevel*> gameLevel);
	virtual void Render(LPD3DXSPRITE spriteBrush);
	virtual void RenderLine();
	virtual void CleanUpLevel();
	int GetLevelState();
	void SetLevelState(int levelState);

private:
	// Determine which level to load
	int levelState = 0;
};

