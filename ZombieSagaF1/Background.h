#pragma once
#include <d3dx9.h>

class Background
{
public:
	// Constructor
	Background();
	Background(int textureWidth, int textureHeight);
	// Destructor
	~Background();
	// Create texutre for background
	void CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath);
	
	// Render the background
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat, D3DXVECTOR2 scaling);
protected:
	// Texture
	LPDIRECT3DTEXTURE9 texture = NULL;
	RECT bgRect;
	D3DXVECTOR2 bgCentre;
	D3DXVECTOR2 position;
};