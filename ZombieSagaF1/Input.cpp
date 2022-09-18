#include "Input.h"

Input::Input()
{
}

Input::~Input()
{

}

void Input::GetInput(BYTE* diKeys, int key)
{
	if (diKeys[key] & 0x80)
	{
		isKeyPressed = true;
	}
}

void Input::SetKeyPressed(bool state)
{
	isKeyPressed = state;
}

bool Input::GetKeyPressed()
{
	return isKeyPressed;
}

