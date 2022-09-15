#pragma once
#include <dinput.h>

class Input
{
public:
	Input();
	// Get the input
	void GetInput(BYTE* diKeys, int key);
	// Set the key pressed state to (false or true)
	void SetKeyPressed(bool state);
	// Get Key Pressed
	bool GetKeyPressed();

private:
	bool isKeyPressed;
};

