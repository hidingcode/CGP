#pragma once
#include "Background.h"
#include "Panel.h"
#include <iostream>

using namespace std;

class MainMenu : public Background
{
public:
	MainMenu();
	MainMenu(int textureWidth, int textureHeight);
	void CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath);
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat, D3DXVECTOR2 scaling, D3DXVECTOR2 position);
	void OnCollide(RECT rect);
};

