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
	//Image::Init();
	this->ColRect.left = this->GetPosition().x; // x = 0 dk why, 
	this->ColRect.top = this->GetPosition().y; // y = 0 dk why, 
	this->ColRect.right = ColRect.left + this->GetTextureWidth();
	this->ColRect.bottom = ColRect.top + this->GetTextureHeight();
	

}

bool Button::OnCollide(RECT ColRect)
{	
	//cout << "startButton : " << this->ColRect.left << " , " << this->ColRect.top << " , " << this->ColRect.right << " , " << this->ColRect.bottom << endl;
	//cout << "F1 :" << ColRect.left << " , " << ColRect.top << " , " << ColRect.right << " , " << ColRect.bottom << endl;

	if (this->ColRect.left > ColRect.right)
	{
		
		return false;
	}
	if (this->ColRect.right < ColRect.left)
	{
		
		return false;
	}
	if (this->ColRect.top > ColRect.bottom)
	{
		
		return false;
	}
	if (this->ColRect.bottom < ColRect.top )
	{
		
		return false;
	}

	

	return true;
}

void Button::GetColRect()
{
	cout << "LEFT :" << this->ColRect.left << "," << "TOP :" << this->ColRect.top << "," << "RIGHT :" << this->ColRect.right << "," << "BOTTOM :" << this->ColRect.bottom << endl;
}


