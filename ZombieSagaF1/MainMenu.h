#pragma once
#include "GameLevel.h"
#include "Player.h"
#include "UI.h"
#include "Text.h"

class MainMenu : public GameLevel
{
public:
	MainMenu();
	~MainMenu();

	void InitLevel(IDirect3DDevice9* d3dDevice);
	void Update(int framesToUpdate, InputManager* inputManager, AudioManager* audioManager);
	void Render(LPD3DXSPRITE spriteBrush);

private:
	Player* F1 = new Player();
	UI* ui = new UI();
	Text* instruction = new Text();
};