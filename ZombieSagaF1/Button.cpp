#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

bool Button::OnCollide(RECT colRect)
{	
	return RectColDetection(GetColRectangle(), colRect);
}



