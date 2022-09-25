#ifndef MAINMENU_H
#define MAINMENU_H
#include "GameManager.h"
#include "Player.h"
#include "Text.h"
#include "Level1.h"

class MainMenu : public GameState
{
public:
	MainMenu();
	~MainMenu();

	void InitLevel(IDirect3DDevice9* d3dDevice);
	void Update(IDirect3DDevice9* d3dDevice);
	void Render(LPD3DXSPRITE spriteBrush);
	void CleanUpLevel();

private:
	Player* F1 = new Player();
	Image* menuBG = new Image();
	Image* eKey = new Image();
	Text* instruction = new Text();
	Button* startButton = new Button();
	Button* quitButton = new Button();
};
#endif