#include "MainMenu.h"

//Button* startButton = new Button(400, 75);
//Button* quitButton = new Button(400, 75);
Panel* panel1 = new Panel(D3DXVECTOR2(310,300));

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

	panel1->Begin();
	panel1->CreateTexture(d3dDevice);
}

// Render the image
void MainMenu::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat, D3DXVECTOR2 scaling, D3DXVECTOR2 position)
{	
	Background::Render(spriteBrush, mat, scaling, position);

	panel1->Render(spriteBrush, mat);
}

void MainMenu::OnCollide(RECT rect)
{
	panel1->OnCollide(rect);
}
