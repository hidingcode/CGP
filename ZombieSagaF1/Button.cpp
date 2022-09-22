#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

bool Button::OnCollide(RECT rect, D3DXVECTOR2 position)
{	
	if (this->rect.left + this->position.x > rect.right + position.x)
	{
		return false;
	}
	if (this->rect.right + this->position.x < rect.left + position.x)
	{
		return false;
	}
	if (this->rect.top + this->position.x > rect.bottom + position.y)
	{
		return false;
	}
	if (this->rect.bottom + this->position.x < rect.top + position.y)
	{
		return false;
	}
	return true;
}




