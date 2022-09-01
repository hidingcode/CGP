//	include the Direct Input library.
#include <dinput.h>

//	TO DO:
//	Link dinput8.lib and dxguid.lib to your project

int main()
{
	//	Direct Input object.
	LPDIRECTINPUT8 dInput;
	
	//	Create the Direct Input object.
	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL); 
		
	//	Direct Input keyboard device.
	LPDIRECTINPUTDEVICE8  dInputKeyboardDevice; 

	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL); 

	//	Set the input data format.
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard); 

	//	Set the cooperative level.
	//	To Do:
	//	Try with different combination.
	dInputKeyboardDevice->SetCooperativeLevel(/*HWND*/, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

/*---
	For buffered data
	//	Define buffer for input.
	//const int DEVICE_BUFFER_SIZE = 4;
	//DIDEVICEOBJECTDATA deviceBuffer[DEVICE_BUFFER_SIZE];

	////	Set the event buffer / properties. 
	//DIPROPDWORD dipdw;
	//dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	//dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	//dipdw.diph.dwObj = 0;
	//dipdw.diph.dwHow = DIPH_DEVICE;
	//dipdw.dwData = DEVICE_BUFFER_SIZE;
	
	//hr = dInputKeyboardDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
--*/

	//	Acquire the device.
	dInputKeyboardDevice->Acquire();
		
	//	Key input buffer
	BYTE  diKeys[256]; 
	
	while (true)
	{
		//	Get immediate Keyboard Data.
		dInputKeyboardDevice->GetDeviceState(256, diKeys);

		if (diKeys[DIK_UP] & 0x80)
		{
			std::cout << "UP" << std::endl;
		}

/*---
	For buffered data
		//	Get buffered keyboard data.
		//DWORD items = DEVICE_BUFFER_SIZE;
		//dInputKeyboardDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), deviceBuffer, &items, 0);
		//
		//for(DWORD i=0; i<items; i++)
		//{	
		//	if ((deviceBuffer[i].dwData & 0x80) != 0)
		//	{
		//		if (deviceBuffer[i].dwOfs == DIK_UP)
		//		{
		//			std::cout << "UP" << std::endl;
		//		}
		//	}
		//} 
--*/

	}

	//	Release keyboard device.
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	//	Release DirectInput.
	dInput->Release();
	dInput = NULL;

	return 0;
}