#include "Panel.h"

Button* startButton = new Button(210, 75);
Button* quitButton = new Button(168, 75);

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
	startButton->Render(spriteBrush, mat, D3DXVECTOR2(1,1), startButton->GetPosition());
	quitButton->Render(spriteBrush, mat, D3DXVECTOR2(1, 1), quitButton->GetPosition());
}

void Panel::OnCollide(RECT rect)
{
	if (startButton->IsCollide(rect))
	{
		// Start The Game
	}
	
	if (quitButton->IsCollide(rect))
	{
		// Quit the game
	}
}
