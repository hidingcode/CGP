#pragma onnce
#include <d3dx9.h>
#include "Text.h"
#include "Box.h"
#include "RenderComponent.h"
#include "MyWindowManager.h"
#include <iostream>


class D3D9DeviceManager {
public:
	D3D9DeviceManager();
	~D3D9DeviceManager();

	// Create Direct3D9 Device
	void CreateMyD3D9Device(HWND g_hWnd, int WindowWidth, int WindowHeight);
	// Clean Up Direct3D9 Device
	void CleanUpMyD3D9Device(IDirect3DDevice9* d3dDevice);
	Text* GetTextReference();
	Box* GetBoxReference();

	LPD3DXSPRITE GetspriteBrush1();
	LPD3DXSPRITE GetspriteBrush2();
	LPD3DXSPRITE* GetspriteBrush1reference();
	LPD3DXSPRITE* GetspriteBrush2reference();
	IDirect3DDevice9** GetD3D9Dreference();
	IDirect3DDevice9* GetD3D9D();
	Text GetText();
	Box GetBox();
private:
	IDirect3DDevice9* d3dDevice;
	IDirect3DDevice9** d3dDeviceReference;
	int WindowWidth;
	int WindowHeight;
	LPD3DXSPRITE spriteBrush1 ;
	LPD3DXSPRITE spriteBrush2 ;
	LPD3DXSPRITE* spriteBrush1Reference;
	LPD3DXSPRITE* spriteBrush2Reference;

	Text* textReference;
	Box* boxReference;
	Text text;
	Box box;

};