#pragma once
#include <d3dx9.h>
#include <iostream>

using namespace std;

class Text
{
public:
	Text();
	// Create Font Type
	void CreateFontType(IDirect3DDevice9* d3dDevice, LPCSTR fontType);
	// Initialise Text 
	void Init(int textRectLeft, int textRectTop, int textRectRight, int textRectBottom);
	// Render Text
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat, D3DXVECTOR2 scaling, D3DXVECTOR2 textCentre,
		D3DXVECTOR2 fontPosition, float rotation, LPCSTR text, D3DXCOLOR textColor);

private:
	LPD3DXFONT font = NULL;
	RECT textRect;
};

