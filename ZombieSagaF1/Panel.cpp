#include "Panel.h"

Panel::Panel(D3DXVECTOR2 position)
{
	this->position = position;
}

Panel::~Panel()
{
}


void Panel::Init()
{	
	startButton->Init(210,75, D3DXVECTOR2(0, 0), 0.0f, position, 0.0f,
		D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(255, 255, 255));
	quitButton->Init(170, 75, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(position.x, position.y / 2 + startButton->GetPosition().y),
		0.0f, D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(255, 255, 255));
}

void Panel::CreateTexture(IDirect3DDevice9* d3dDevice)
{
	startButton->CreateTexture(d3dDevice, "Assets/startButton.png");
	quitButton->CreateTexture(d3dDevice, "Assets/quitButton.png");
}

// Render the image
void Panel::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat)
{
	startButton->RenderSprite(spriteBrush, mat);
	quitButton->RenderSprite(spriteBrush, mat);
}

void Panel::OnCollide(RECT rect)
{
	if (startButton->OnCollide(rect))
	{
		// Start The Game
	}
	
	if (quitButton->OnCollide(rect))
	{
		// Quit the game
	}
}
