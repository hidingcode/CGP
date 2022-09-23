#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H
#include <d3dx9.h>
#include <vector>

using namespace std;

class GameState;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();
	void ChangeState(GameState* state, IDirect3DDevice9* d3dDevice);
	void PushState(GameState* state, IDirect3DDevice9* d3dDevice);

private:
	vector<GameState*> states;
};
#endif

