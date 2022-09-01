// WARNING!
// The following code is incomplete!
// You are required to merge it to your work in previous Lab.

//	include the D3DX9 library
#include <d3dx9.h>
//--------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//	Initialization
	
	LPDIRECT3DTEXTURE9 texture = NULL;
	LPD3DXSPRITE sprite = NULL;

	//	Create sprite. Study the documentation. 
	HRESULT hr = D3DXCreateSprite(/* Your Direct3D device */, &sprite);

	//	Create texture. Study the documentation.
	hr = D3DXCreateTextureFromFile(/* Your Direct3D device */, "01.bmp", &texture);
	//hr = D3DXCreateTextureFromFileEx(/* Your Direct3D device */, "01.bmp", D3DX_DEFAULT, D3DX_DEFAULT, 
	//									D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
	//									D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), 
	//									NULL, NULL, &texture);

	//	Specify the "	" rectangle.
	RECT spriteRect;
	spriteRect.left = spriteRect.top = 0;
	spriteRect.right = spriteRect.bottom = 32;
	
	while (windowIsRunning())
	{
		//	Clear and begin scene
			
		//	Specify alpha blend will ensure that the sprite will render the background with alpha.
		sprite->Begin(D3DXSPRITE_ALPHABLEND);

		//	Sprite rendering. Study the documentation.
		sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		//sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		//sprite->Draw(texture, &spriteRect, NULL, &D3DXVECTOR3(32, 32, 0), D3DCOLOR_XRGB(255, 255, 255));

		//	End sprite drawing
		sprite->End();
		
		//	End and present scene
	}
	
	//	Release and clean up everything
	
	sprite->Release();
	sprite = NULL;
	
	texture->Release();
	texture = NULL;

	return 0;
}
//--------------------------------------------------------------------