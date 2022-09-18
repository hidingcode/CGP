#include "MainMenu.h"

Background* mainMenu = new Background(842, 651);
Background* startButton = new Background(300, 300);
Background* quitButton = new Background(300, 300);

MainMenu::MainMenu()
{
	
}

void MainMenu::CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath)
{	
	startButton->CreateTexture(d3dDevice, "Assets/startButton.png");
	quitButton->CreateTexture(d3dDevice, "Assets/quitButton.png");
}

// Render the image
void MainMenu::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat)
{
	startButton->Render(spriteBrush, mat, D3DXVECTOR2(1, 1), D3DXVECTOR2(200, 200));
	quitButton->Render(spriteBrush, mat, D3DXVECTOR2(1, 1), D3DXVECTOR2(300, 300));
}
