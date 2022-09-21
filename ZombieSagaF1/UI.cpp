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
	panel1->Init();
	panel1->CreateTexture(d3dDevice);
}

// Render the image
void UI::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat)
{	
	Image::RenderSprite(spriteBrush, mat);

	panel1->Render(spriteBrush, mat);
}

void UI::OnCollide(RECT rect)
{
	panel1->OnCollide(rect);
}
