#include "VerticalPanel.h"

VerticalPanel::VerticalPanel(D3DXVECTOR2 position)
{
	this->position = position;
}

VerticalPanel::~VerticalPanel()
{
}

void VerticalPanel::Init()
{	
	startButton->Init(210,75, D3DXVECTOR2(0, 0), 0.0f, position, 0.0f,
		D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(255, 255, 255));	
	quitButton->Init(165, 70, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(position.x, position.y / 2 + startButton->GetPosition().y),
		0.0f, D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(255, 255, 255));
}

void VerticalPanel::CreateTexture(IDirect3DDevice9* d3dDevice)
{
	startButton->CreateTexture(d3dDevice, "Assets/startButton.png");
	quitButton->CreateTexture(d3dDevice, "Assets/quitButton.png");
		// Told the player to press e key to start or quit the game
}

// Render the image
void VerticalPanel::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat)
{
	startButton->RenderSprite(spriteBrush, mat);
	quitButton->RenderSprite(spriteBrush, mat);
}

void VerticalPanel::OnCollide(RECT colRect)
{
	if (startButton->OnCollide(colRect))
	{	
		startButton->SetColorFilter(D3DCOLOR_XRGB(255, 0, 0));
		// Start The Game
		cout << "Start Button" << endl;
	}
	else
	{
		startButton->SetColorFilter(D3DCOLOR_XRGB(255, 255, 255));
	}
	
	if (quitButton->OnCollide(colRect))
	{	
		quitButton->SetColorFilter(D3DCOLOR_XRGB(255, 0, 0));
		// Quit the game
		
		cout << "Quit Button" << endl;
	}

	else
	{
		quitButton->SetColorFilter(D3DCOLOR_XRGB(255, 255, 255));
	}
}

