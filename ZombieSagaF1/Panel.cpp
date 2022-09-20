#include "Panel.h"

Panel::Panel(D3DXVECTOR2 position)
{
	this->position = position;
}

Panel::~Panel()
{
}


void Panel::Begin()
{
	// Set the position of widget according to the panel position
	startButton->SetPosition(position);
	quitButton->SetPosition(D3DXVECTOR2(position.x, 420));
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
