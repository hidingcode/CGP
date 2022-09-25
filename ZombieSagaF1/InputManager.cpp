#include "InputManager.h"

InputManager::InputManager()
{	
}

InputManager::~InputManager()
{
}

void InputManager::AddKey(int keyCode)
{	
	// Push the key code into the key code vector
	keyCodes[numberOfEntries] = keyCode;
	// Add initial key press into the isKeyPressed vector 
	// after a key code is push into key code vector
	isKeyPressed[numberOfEntries] = false;
	// Increase the number of entries to keep track of the number of key code in the arrays
	numberOfEntries++;
}

void InputManager::CreateMyDirectInput(HWND g_hWnd)
{	
	//	Create the Direct Input object.
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	if FAILED(hr)
	{
		cout << "Create Direct Input Failed" << endl;
	}

	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);

	if FAILED(hr)
	{
		cout << "Create Keyboard Input Device Failed" << endl;
	}

	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);

	if FAILED(hr)
	{
		cout << "Create Mouse Input Device Failed" << endl;
	}

	//	Set the input data format.
	hr = dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	//	Set the input data format.
	hr = dInputMouseDevice->SetDataFormat(&c_dfDIMouse);

	// Set Cooperative Level of Keyboard and Mouse DEVICE
	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
}

void InputManager::CleanUpMyDirectInput()
{
	//	Release keyboard device.
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	//	Release DirectInput.
	dInput->Release();
	dInput = NULL;
}

void InputManager::GetInput()
{
	//	Acquire the device.
	dInputKeyboardDevice->Acquire();
	//	Get immediate Keyboard Data.
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	dInputMouseDevice->Acquire();
	//  Get Mouse Data
	dInputMouseDevice->GetDeviceState(sizeof(mouseState), &mouseState);

	/* Loop through the key and check if there is any input
	 If certain key with key codes avaliable in the key code array is pressed, 
	 set the state of the key press to true;*/
	for (int i = 0; i <= numberOfEntries; i++)
	{
		if (diKeys[keyCodes[i]] & 0x80)
		{
			isKeyPressed[i] = true;
		}
	}
}

void InputManager::SetAllKeyPressToFalse()
{	
	/* Loop through all the keys and set them to false*/
	for (int i = 0; i <= numberOfEntries; i++)
	{
		isKeyPressed[i] = false;
	}
}

bool InputManager::GetKeyPress(int keyCode)
{	
	/* Compare the key code with the key code in the array
	 and return the boolean of the same key code*/
	for (int i = 0; i <= numberOfEntries; i++)
	{
		if (keyCodes[i] == keyCode)
		{
			return isKeyPressed[i];
		}
	}
}

