#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

bool Button::OnCollide(RECT rect)
{
	if (this->rect.left > rect.right)
	{
		return false;
	}
	if (this->rect.right < rect.left)
	{
		return false;
	}
	if (this->rect.top > rect.bottom)
	{
		return false;
	}
	if (this->rect.bottom < rect.top)
	{
		return false;
	}
	return true;
}

D3DXVECTOR2 Button::GetPosition()
{
	return position;
}

int Button::GetTextureWidth()
{
	return textureWidth;
}

int Button::GetTextureHeight()
{
	return textureHeight;
}

RECT Button::GetRect()
{
	return rect;
}

void Button::SetPosition(D3DXVECTOR2 position)
{
	this->position = position;
}



