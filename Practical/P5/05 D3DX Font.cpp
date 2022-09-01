// WARNING!
// The following code is incomplete!
// You are required to merge it to your work in previous Lab.

//	include the D3DX9 library
#include <d3dx9.h>
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//	Initialization
	
	LPD3DXFONT font = NULL;
	//	Create font. Study the documentation.
	hr = D3DXCreateFont(/* Your Direct3D device */, 25, 0, 0, 1, false,
				DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	RECT textRect;
	textRect.left = 100;
	textRect.top = 100;
	textRect.right = 150;
	textRect.bottom = 125;
	
	while (windowIsRunning())
	{
		//	Clear and begin scene
			
		//	Sprite Begin

		font->DrawText(/* Your D3DXSprite */, "Hello World!", 5, &textRect, 0, D3DCOLOR_XRGB(255, 255, 255));
			
		//	Sprite End
		
		//	End and present scene
	}
	
	//	Release and clean up everything
	
	font->Release();
	font = NULL;
	
	return 0;
}
//--------------------------------------------------------------------