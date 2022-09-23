#include "Button.h"

Button::Button()
{
	this->GetColStuff();
}

Button::~Button()
{
}

void Button::GetColStuff()
{
	this->colRect.left = this->GetPosition().x;
	this->colRect.top = this->GetPosition().y; 
	this->colRect.right = colRect.left + this->GetTextureWidth();
	this->colRect.bottom = colRect.top + this->GetTextureHeight();
}

bool Button::OnCollide(RECT colRect)
{	
	if (this->colRect.left > colRect.right)
	{
		return false;
	}
	if (this->colRect.right < colRect.left)
	{
		return false;
	}
	if (this->colRect.top > colRect.bottom)
	{
		return false;
	}
	if (this->colRect.bottom < colRect.top )
	{
		return false;
	}
	return true;
}



