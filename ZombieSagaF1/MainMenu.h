#pragma once
#include "Background.h"

class MainMenu
{
public:
	MainMenu();
	void CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath);
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat);
};

