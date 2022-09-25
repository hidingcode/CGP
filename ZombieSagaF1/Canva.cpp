#include "Canva.h"

Canva::Canva()
{
}

Canva::~Canva()
{
}

void Canva::CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath)
{	
	Image::CreateTexture(d3dDevice, textureFilePath);

	// Initialise Panel
	instruction1->CreateFontType(d3dDevice, "Arial");
	instruction1->Init(800, 200, D3DXVECTOR2(1, 1), 0.0f, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 0), 0.0f,
		D3DXVECTOR2(0, 0), -1, 0, D3DCOLOR_XRGB(255, 255, 255));
	panel1->Init();
	panel1->CreateTexture(d3dDevice);
}

// Render the image
void Canva::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat)
{	
	Image::RenderSprite(spriteBrush, mat);
	instruction1->RenderText(spriteBrush, mat, 
		"Move your car with W, A, S ,D to Start Button to start your game");
	panel1->Render(spriteBrush, mat);
}

void Canva::OnCollide(RECT colRect, IDirect3DDevice9* d3dDevice)
{
	panel1->OnCollide(colRect, d3dDevice);
}
