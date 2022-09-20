#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

bool Button::OnCollide(RECT rect)
{
	if (rect.left > this->rect.right)
	{
		return false;
	}
	if (rect.right < this->rect.left)
	{
		return false;
	}
	if (rect.top > this->rect.bottom)
	{
		return false;
	}
	if (rect.bottom < this->rect.top)
	{
		return false;
	}
	return true;
}




