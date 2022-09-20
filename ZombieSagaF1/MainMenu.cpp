#include "MainMenu.h"



MainMenu::MainMenu()
{

}

void MainMenu::CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath)
{	
	Image::CreateTexture(d3dDevice, textureFilePath);

	panel1->Begin();
	panel1->CreateTexture(d3dDevice);
}

// Render the image
void MainMenu::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat)
{	
	Image::RenderSprite(spriteBrush, mat);

	panel1->Render(spriteBrush, mat);
}

void MainMenu::OnCollide(RECT rect)
{
	panel1->OnCollide(rect);
}
