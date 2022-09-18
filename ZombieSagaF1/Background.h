#pragma once
#include <d3dx9.h>

class Background
{
public:
	// Constructor
	Background(int textureWidth, int textureHeight);
	// Destructor
	~Background();
	// Create texutre for background
	void CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath);
	
	// Render the background
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat, D3DXVECTOR2 scaling, D3DXVECTOR2 position);
private:
	// Texture
	LPDIRECT3DTEXTURE9 texture = NULL;
	RECT spriteRect;
	D3DXVECTOR2 spriteCentre;
};