#include "Button.h"

Button::Button(int textureWidth, int textureHeight)
	:Background(textureWidth, textureHeight)
{
	this->position = position;
}

Button::~Button()
{
}

bool Button::IsCollide(RECT rect1)
{
	if (rect.left > rect1.right)
	{
		return false;
	}
	if (rect.right < rect1.left)
	{
		return false;
	}
	if (rect.top > rect1.bottom)
	{
		return false;
	}
	if (rect.bottom < rect1.top)
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



