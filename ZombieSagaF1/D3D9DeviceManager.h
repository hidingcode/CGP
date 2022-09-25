#ifndef D3D9DEVICEMANAGER_H
#define D3D9DEVICEMANAGER_H
#include <d3dx9.h>
#include "Text.h"
#include "Box.h"
#include "RenderComponent.h"
#include "MyWindowManager.h"
#include "GameHeader.h"

class D3D9DeviceManager {
public:
	D3D9DeviceManager();
	~D3D9DeviceManager();

	// Create Direct3D9 Device
	void CreateMyD3D9Device(HWND g_hWnd);
	// Begin Render (Begin scene and set up spriteBrush)
	void BeginRender();
	// Begin Sprite Brush
	void BeginSpriteBrush();
	// End Sprite Brush
	void EndSpriteBrush();
	// Present the back buffer to the screen
	void PresentBuffer();
	// Clean Up Direct3D9 Device
	void CleanUpMyD3D9Device();

	LPD3DXSPRITE GetSpriteBrush();
	IDirect3DDevice9** GetD3D9Reference();
	IDirect3DDevice9* GetD3D9Device();

private:
	IDirect3DDevice9* d3dDevice;
	IDirect3DDevice9** d3dDeviceReference;
	LPD3DXSPRITE spriteBrush = NULL;
};

#endif