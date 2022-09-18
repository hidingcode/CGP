#include "Button.h"

Button::Button(int textureWidth, int textureHeight)
	:Background(textureWidth, textureHeight)
{
	this->position = position;
}

Button::~Button()
{
}

void Button::CheckCollision()
{
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

void Button::SetPosition(D3DXVECTOR2 position)
{
	this->position = position;
}



