#ifndef MAINMENU_H
#define MAINMENU_H
#include "GameHeader.h"
#include "Player.h"
#include "Text.h"
#include "Level1.h"

class MainMenu : public GameState
{
public:
	MainMenu();
	~MainMenu();

	void InitLevel(IDirect3DDevice9* d3dDevice) override;
	void Update(IDirect3DDevice9* d3dDevice) override;
	void Render(LPD3DXSPRITE spriteBrush) override;
	void CleanUpLevel() override;

private:
	Player* F1 = new Player();
	Image* menuBG = new Image();
	Image* eKey = new Image();
	Text* instruction = new Text();
	Button* startButton = new Button();
	Button* quitButton = new Button();
};
#endif