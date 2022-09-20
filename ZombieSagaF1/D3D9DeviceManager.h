#pragma onnce
#include <d3dx9.h>

class D3D9DeviceManager{
public:
	D3D9DeviceManager();
	~D3D9DeviceManager();

	// Create Direct3D9 Device
	void CreateMyD3D9Device(HWND g_hWnd, int WindowWidth, int WindowHeight);
	// Clean Up Direct3D9 Device
	void CleanUpMyD3D9Device(IDirect3DDevice9* d3dDevice);
private:
};