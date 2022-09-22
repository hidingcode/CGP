#include "D3D9DeviceManager.h"



using namespace std;



D3D9DeviceManager::D3D9DeviceManager()
{
}

D3D9DeviceManager::~D3D9DeviceManager()
{
}

void D3D9DeviceManager::CreateMyD3D9Device(HWND g_hWnd,int WindowWidth, int WindowHeight)
{
	
		//	Define Direct3D 9.
		IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
		//	Define how the screen presents.
		D3DPRESENT_PARAMETERS d3dPP;
		ZeroMemory(&d3dPP, sizeof(d3dPP));

		//	Refer to Direct3D 9 documentation for the meaning of the members.
		d3dPP.Windowed = true;
		d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dPP.BackBufferCount = 1;
		d3dPP.BackBufferWidth = WindowWidth;
		d3dPP.BackBufferHeight = WindowHeight;
		d3dPP.hDeviceWindow = g_hWnd;



		//	Create a Direct3D 9 device.
		HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

		//	Create sprite. Study the documentation. 
		hr = D3DXCreateSprite(d3dDevice, &spriteBrush1);

		if (FAILED(hr))
		{
			cout << "Create sprite brush 1 failed" << endl;
		}

		hr = D3DXCreateSprite(d3dDevice, &spriteBrush2);

		if (FAILED(hr)) {
			cout << "Create sprite brush 2 failed" << endl;
		}

		text.CreateFontType(d3dDevice, "Arial");

		box.CreateLine(d3dDevice);
	
	
}





IDirect3DDevice9* D3D9DeviceManager::GetD3D9D()
{
	return this->d3dDevice;
}

IDirect3DDevice9** D3D9DeviceManager::GetD3D9Dreference()
{
	d3dDeviceReference = &d3dDevice;
	return this->d3dDeviceReference;
}

LPD3DXSPRITE D3D9DeviceManager::GetspriteBrush1()
{
	return this->spriteBrush1;
}
LPD3DXSPRITE D3D9DeviceManager::GetspriteBrush2()
{
	return this->spriteBrush2;
}

LPD3DXSPRITE* D3D9DeviceManager::GetspriteBrush1reference()
{
	spriteBrush1Reference = &spriteBrush1;
	return this->spriteBrush1Reference;
}
LPD3DXSPRITE* D3D9DeviceManager::GetspriteBrush2reference()
{
	spriteBrush1Reference = &spriteBrush2;
	return this->spriteBrush2Reference;
}

Text* D3D9DeviceManager::GetTextReference()
{
	textReference = &text;
	return this->textReference;
}
Box* D3D9DeviceManager::GetBoxReference()
{
	boxReference = &box;
	return this->boxReference;
}










void D3D9DeviceManager::CleanUpMyD3D9Device(IDirect3DDevice9* d3dDevice)
{
	//	Release and clean up everything
	spriteBrush1->Release();
	spriteBrush1 = NULL;
	spriteBrush2->Release();
	spriteBrush2 = NULL;
	text.CleanUpText();
	GetBoxReference()->CleanUpLine();
	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;
	
}