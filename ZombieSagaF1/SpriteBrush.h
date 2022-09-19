#pragma once
#include <d3dx9.h>
#include <iostream>
using namespace std;

class SpriteBrush
{
public:
	SpriteBrush();
	~SpriteBrush();
	void CreateSpriteBrush(IDirect3DDevice9* d3dDevice);
	void Begin();
	void Release();
private:
	LPD3DXSPRITE spriteBrush = NULL;
};

