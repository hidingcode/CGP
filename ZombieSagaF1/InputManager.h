#pragma once
#include <dinput.h>
#include <vector>
#include <iostream>

using namespace std;

class InputManager
{
public:
	InputManager();
	~InputManager();
	
	// Add Key into the Input Manager. Example: AddKey(DIK_W)
	// For more information of keycodes please look at direct input key codes
	void AddKeyCodes(int keyCode);
	// Create Direct Input Object, Keyboard Device and Mouse Device
	void CreateMyDirectInput(HWND g_hWnd);
	// Release Input Device
	void CleanupMyDirectInput();
	// Accquire Input
	void GetInput();
	// Set all of the key press to false
	void SetAllKeyPressToFalse();
	// Get Key Pressed. Example: GetKeyPress(DIK_W) 
	// to get the key press of W
	bool GetKeyPress(int keyCode);

private:
	// Direct Input
	LPDIRECTINPUT8 dInput;
	// Direct Input Keyboard Device
	LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
	// Direct Input Mouse Device
	LPDIRECTINPUTDEVICE8 dInputMouseDevice;
	//	Key input buffer
	BYTE  diKeys[256];
	// Mouse input buffer
	DIMOUSESTATE mouseState;
	// Store Keys Codes of keyboard key
	int keyCodes[256];
	// Track the number of key code added into the array
	int numberOfEntries = 0;
	//// Boolean to check if the key is pressed or not
	//vector<bool> isKeyPressed;
	bool isKeyPressed[256];
	
};

