#include "Text.h"

Text::Text()
{
}

void Text::CreateFontType(IDirect3DDevice9* d3dDevice, LPCSTR fontType)
{
	HRESULT hr = D3DXCreateFont(d3dDevice, 25, 0, 0, 1, false, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, fontType, &font);


	if (FAILED(hr)) {
		cout << "Create font failed" << endl;
	}
}

void Text::Init(int textRectLeft, int textRectTop, int textRectRight, int textRectBottom)
{
	textRect.left = textRectLeft;
	textRect.top = textRectTop;
	textRect.right = textRectRight;
	textRect.bottom = textRectBottom;
}

void Text::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat, D3DXVECTOR2 scaling, D3DXVECTOR2 textCentre, 
	D3DXVECTOR2 fontPosition, float rotation,LPCSTR text, D3DXCOLOR textColor)
{	
	D3DXMatrixTransformation2D(mat, NULL, 0.0, &scaling, &textCentre, rotation, &fontPosition);
	spriteBrush->SetTransform(mat);
	font->DrawText(spriteBrush, text, -1, &textRect, 0, textColor);
}

void Text::CleanUp()
{
	font->Release();
	font = NULL;
}