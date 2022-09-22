#pragma once
#include "GameLevel.h"
#include "UI.h"

class MainMenu : public GameLevel
{
public:
	MainMenu();
	~MainMenu();

	void InitLevel(IDirect3DDevice9* d3dDevice);
	void Update(int framesToUpdate, InputManager inputManager, AudioManager audioManager);
	void Render(LPD3DXSPRITE spriteBrush, IDirect3DDevice9* d3dDevice);;

private:
	UI* ui = new UI();
};