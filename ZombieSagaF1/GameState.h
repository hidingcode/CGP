#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <d3dx9.h>
#include "GameStateManager.h"

class GameState
{
public:
	GameState();
	~GameState();

	virtual void InitLevel(IDirect3DDevice9* d3dDevice);
	virtual	void Update(IDirect3DDevice9* d3dDevice);
	virtual void Render(LPD3DXSPRITE spriteBrush);
	virtual void RenderLine();
	virtual void CleanUpLevel();
};
#endif
