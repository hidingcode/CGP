#include "MainMenu.h"

Button* startButton = new Button(400, 75);
Button* quitButton = new Button(400, 75);

MainMenu::MainMenu()
{

}

MainMenu::MainMenu(int textureWidth, int textureHeight):
	Background(textureWidth, textureHeight)
{

}

void MainMenu::CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath)
{	
	Background::CreateTexture(d3dDevice, textureFilePath);

	startButton->CreateTexture(d3dDevice, "Assets/startButton.png");
	quitButton->CreateTexture(d3dDevice, "Assets/quitButton.png");
}

// Render the image
void MainMenu::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat, D3DXVECTOR2 scaling, D3DXVECTOR2 position)
{	
	Background::Render(spriteBrush, mat, scaling, position);

	startButton->Render(spriteBrush, mat, D3DXVECTOR2(1, 1), D3DXVECTOR2(200, 200));
	quitButton->Render(spriteBrush, mat, D3DXVECTOR2(1, 1), D3DXVECTOR2(300, 300));
}
