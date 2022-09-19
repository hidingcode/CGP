#include "InputManager.h"

InputManager::InputManager()
{
}

InputManager::~InputManager()
{

}

void InputManager::SetInput(BYTE* diKeys, int key)
{

}

void InputManager::SetKeyPressed(bool state)
{
	isKeyPressed = state;
}

bool InputManager::GetKeyPressed()
{
	return isKeyPressed;
}

