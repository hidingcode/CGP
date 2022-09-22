#include "UI.h"

UI::UI()
{
}

UI::~UI()
{
}

void UI::CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath)
{	
	Image::CreateTexture(d3dDevice, textureFilePath);

	// Initialise Panel
	instruction->CreateFontType(d3dDevice, "Arial");
	instruction->Init(800, 200, D3DXVECTOR2(1, 1), 0.0f, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 0), 0.0f,
		D3DXVECTOR2(0, 0), -1, 0, D3DCOLOR_XRGB(255, 255, 255));
	panel1->Init();
	panel1->CreateTexture(d3dDevice);
}

// Render the image
void UI::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat)
{	
	Image::RenderSprite(spriteBrush, mat);
	instruction->RenderText(spriteBrush, mat, "Move your car with W, A, S ,D to Start Button to start your game");
	panel1->Render(spriteBrush, mat);
}

void UI::OnCollide(RECT Colrect)
{
	panel1->OnCollide(Colrect);
}
