#ifndef MAINMENU_H
#define MAINMENU_H
#include "GameState.h"
#include "Player.h"
#include "Canva.h"
#include "Text.h"

class MainMenu : public GameState
{
public:
	MainMenu();
	~MainMenu();

	void InitLevel(IDirect3DDevice9* d3dDevice, MyWindowManager* windowManager);
	void Update(InputManager* inputManager, AudioManager* audioManager,
		vector<GameState*> gameState, MyWindowManager* windowManager);
	void Render(LPD3DXSPRITE spriteBrush);
	void CleanUpLevel();

private:
	Player* F1 = new Player();
	Canva* canva = new Canva();
	Text* instruction = new Text();
};
#endif