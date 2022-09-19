#pragma once
#include <d3dx9.h>
#include "Button.h"

class Panel
{
public:
	Panel(D3DXVECTOR2 position);
	~Panel();
	void Begin();
	void CreateTexture(IDirect3DDevice9* d3dDevice);
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat);
	void OnCollide(RECT rect);
private:
	D3DXVECTOR2 position = D3DXVECTOR2(0, 0);
};

