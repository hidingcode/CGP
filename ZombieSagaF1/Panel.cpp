#include "Panel.h"

Button* startButton = new Button(400, 75);
Button* quitButton = new Button(400, 75);

Panel::Panel(D3DXVECTOR2 position)
{
	this->position = position;
}

Panel::~Panel()
{
}

void Panel::Begin()
{
	startButton->SetPosition(position);
	quitButton->SetPosition(D3DXVECTOR2(position.x, startButton->GetTextureHeight()));
}
