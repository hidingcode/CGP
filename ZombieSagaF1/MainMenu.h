#ifndef MAINMENU_H
#define MAINMENU_H
#include "GameManager.h"
#include "Player.h"
#include "Canva.h"
#include "Text.h"

class MainMenu : public GameState
{
public:
	MainMenu()
	{

	};
	~MainMenu();

	void InitLevel(IDirect3DDevice9* d3dDevice);
	void Update(vector<GameState*> gameState, IDirect3DDevice9* d3dDevice);
	void Render(LPD3DXSPRITE spriteBrush);
	void CleanUpLevel();

private:
	Player* F1 = new Player();
	Canva* canva = new Canva();
	Text* instruction = new Text();
};
#endif