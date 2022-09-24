#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <d3dx9.h>
#include "MyWindowManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "GameStateManager.h"

class GameState
{
public:
	GameState();
	~GameState();

	virtual void InitLevel(IDirect3DDevice9* d3dDevice, MyWindowManager* windowManager);
	virtual	void Update(InputManager* inputManager, AudioManager* audioManager,
		vector<GameState*> gameState, MyWindowManager* windowManager);
	virtual void Render(LPD3DXSPRITE spriteBrush);
	virtual void RenderLine();
	virtual void CleanUpLevel();
};
#endif
