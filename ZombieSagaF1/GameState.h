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
	virtual void InitLevel(IDirect3DDevice9* d3dDevice);
	virtual	void Update(int framesToUpdate, InputManager* inputManager, AudioManager* audioManager, 
		vector<GameState*> gameState);
	virtual void Render(LPD3DXSPRITE spriteBrush);
	virtual void RenderLine();
	virtual void CleanUpLevel();
	//int GetLevelState();
	//void SetLevelState(int levelState);

	/*void ChangeState(GameStateManager* game, GameState* state, IDirect3DDevice9* d3dDevice);*/

protected:
	/*GameState();*/

private:
	//// Determine which level to load
	//int levelState = 0;
};
#endif
