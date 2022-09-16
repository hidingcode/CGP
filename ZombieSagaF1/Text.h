#pragma once
#include <d3dx9.h>
#include <iostream>

using namespace std;

class Text
{
public:
	// Constructor
	Text();
	Text(LPDIRECT3DDEVICE9 pDevice, INT Height, UINT Width, UINT Weight,
		UINT MipLevels, BOOL Italic, DWORD CharSet, DWORD OuptPrecision, DWORD Quality,
		DWORD PitchAndFamily, LPCSTR pFaceName, LPD3DXFONT* ppFont);
	// Create Font Type
	void CreateFontType(IDirect3DDevice9* d3dDevice, LPCSTR fontType);
	// Initialise Text 
	void Init(int textRectLeft, int textRectTop, int textRectRight, int textRectBottom);
	// Render Text
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat, D3DXVECTOR2 scaling, D3DXVECTOR2 textCentre,
		D3DXVECTOR2 fontPosition, float rotation, LPCSTR text, D3DXCOLOR textColor);
	// Clean Up Text
	void CleanUp();

private:
	LPD3DXFONT font = NULL;
	RECT textRect;
};

