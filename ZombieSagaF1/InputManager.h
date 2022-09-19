#pragma once
#include <dinput.h>
#include <vector>

class InputManager
{
public:
	InputManager();
	~InputManager();
	// Get the input
	void SetInput(BYTE* diKeys, int key);
	// Set the key pressed state to (false or true)
	void SetKeyPressed(bool state);
	// Get Key Pressed
	bool GetKeyPressed();

private:
	bool isKeyPressed;
	vector<int> keys;
};

