#include "MainMenu.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::InitLevel(IDirect3DDevice9* d3dDevice)
{
	ui->CreateTexture(d3dDevice, "Assets/mainMenu.png");
}

void MainMenu::Update(int framesToUpdate, InputManager inputManager, AudioManager audioManager)
{
}

void MainMenu::Render(LPD3DXSPRITE spriteBrush, IDirect3DDevice9* d3dDevice)
{	
	D3DXMATRIX mat;
	ui->Render(spriteBrush, &mat);
}


