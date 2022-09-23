#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H
#include <d3dx9.h>
#include <vector>

using namespace std;

class GameState;

class GameStateManager
{
public:
	void ChangeState(GameState* states, IDirect3DDevice9* d3dDevice);
	void PushState(GameState* states, IDirect3DDevice9* d3dDevice);

private:
	// stack of game states
	vector<GameState*> states;
};
#endif

