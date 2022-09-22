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
}

// Render the image
void VerticalPanel::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat)
{
	startButton->RenderSprite(spriteBrush, mat);
	quitButton->RenderSprite(spriteBrush, mat);
}

void VerticalPanel::OnCollide(RECT Colrect)
{
	//update the collision rectangle of button  
	startButton->GetColStuff();
	quitButton->GetColStuff();
	//cout << "F1 :" << Colrect.left << "," << Colrect.top << "," << Colrect.right << "," << Colrect.bottom << endl;

	if (startButton->OnCollide(Colrect))
	{
		// Start The Game
		cout << "Start Button" << endl;
		//cout << "F1           :" << Colrect.left << "," << Colrect.top << "," << Colrect.right << "," << Colrect.bottom << endl;
		//cout << "start button :" << startButton-> << "," << Colrect.top << "," << Colrect.right << "," << Colrect.bottom << endl;
		

	}
	
	if (quitButton->OnCollide(Colrect))
	{
		// Quit the game
		
		cout << "Quit Button" << endl;
	}
	
}

