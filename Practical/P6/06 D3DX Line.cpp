// WARNING!
// The following code is incomplete!
// You are required to merge it to your work in previous Lab.

//	include the D3DX9 library
#include <d3dx9.h>
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//	Initialization
	
	LPD3DXLINE line = NULL;	
	//	Create line
	hr = D3DXCreateLine(/* Your Direct3D device */, &line);
	
	while (windowIsRunning())
	{
		//	Clear and begin scene
			
		//	Define the line vertices.
		D3DXVECTOR2 lineVertices[] = {D3DXVECTOR2(200, 200), D3DXVECTOR2(200, 400)};
		//	Begin to draw the lines.
		line->Begin();
		line->Draw(lineVertices, 2, D3DCOLOR_XRGB(0, 0, 0));
		line->End();
		
		//	End and present scene
	}
	
	//	Release and clean up everything
	line->Release();
	line = NULL;

	return 0;
}
//--------------------------------------------------------------------