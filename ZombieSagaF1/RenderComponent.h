#pragma once
#include <d3dx9.h>
#include <iostream>
using namespace std;

class RenderComponent
{
public:
	RenderComponent();
	~RenderComponent();
	// Initialise Sprite Data
	void InitSprite(D3DXVECTOR2 scalingCentre, float scalingRotation, D3DXVECTOR2 scaling,
		D3DXVECTOR2 rotationCentre, float rotation, D3DXVECTOR2 position, D3DXCOLOR colorFilter);
	// Intialise Text Data
	void InitText(D3DXVECTOR2 scalingCentre, float scalingRotation, D3DXVECTOR2 scaling, 
		D3DXVECTOR2 rotationCentre, float rotation, D3DXVECTOR2 position, 
		int textLength, UINT format, D3DXCOLOR colorFilter);
	// Create Texture
	void CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath);
	// Create Font
	void CreateFontType(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath);
	// Render Sprite
	void RenderSprite(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat);
	// Render Text
	void RenderText(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat, LPCSTR textContent);
	// Clean up sprite
	void CleanUpSprite();
	// Clean up text
	void CleanUpText();
	// Get Position
	D3DXVECTOR2 GetPosition();
	// Get Scaling
	D3DXVECTOR2 GetScaling();
	// Get ScalingCentre
	D3DXVECTOR2 GetScalingCentre();
	// Get RotationCentre
	D3DXVECTOR2 GetRotationCentre();
protected:
	LPDIRECT3DTEXTURE9 texture = NULL;
	RECT rect;
	D3DXVECTOR2 scalingCentre;
	float scalingRotation;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 rotationCentre;
	float rotation;
	D3DXVECTOR2 position;
	D3DCOLOR colorFilter;
	LPD3DXFONT font = NULL;
	int textLength = -1;
	UINT format = 0;
};

