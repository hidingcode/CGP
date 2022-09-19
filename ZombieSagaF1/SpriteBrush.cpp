#include "SpriteBrush.h"

SpriteBrush::SpriteBrush()
{
}

SpriteBrush::~SpriteBrush()
{
}

void SpriteBrush::CreateSpriteBrush(IDirect3DDevice9* d3dDevice)
{
	HRESULT hr = D3DXCreateSprite(d3dDevice, &spriteBrush);

	if (FAILED(hr)) {
		cout << "Create sprite brush failed" << endl;
	}
}

void SpriteBrush::Begin()
{
	spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);
}
