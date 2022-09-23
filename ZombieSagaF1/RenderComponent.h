#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H
#include <d3dx9.h>
#include <iostream>
using namespace std;

class RenderComponent
{
public:
	RenderComponent();
	~RenderComponent();
	// Calculate Collision Rectangle
	void CalColRect();
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
	// Get Rectangle
	RECT GetRectangle();
	// Get collision rectangle
	RECT GetColRectangle();
	// Set Scaling Centre
	void SetScalingCentre(D3DXVECTOR2 scalingCentre);
	// Get Scaling Centre
	D3DXVECTOR2 GetScalingCentre();
	// Set Scaling Rotation
	void SetScalingRotation(float scalingRotation);
	// Get Scaling Rotation
	float GetScalingRotation();
	// Set Scaling
	void SetScaling(D3DXVECTOR2 scaling);
	// Get Scaling
	D3DXVECTOR2 GetScaling();
	// Set Rotation Centre
	void SetRotationCentre(D3DXVECTOR2 position);
	// Get Rotation Centre
	D3DXVECTOR2 GetRotationCentre();
	// Set Rotation
	void SetRotation(float rotation);
	// Get Rotation
	float GetRotation();
	// Set Position
	void SetPosition(D3DXVECTOR2 position);
	// Get Position
	D3DXVECTOR2 GetPosition();
	// Set Color Filter
	void SetColorFilter(D3DCOLOR colorFilter);
	// Get Color Filter
	D3DCOLOR GetColorFilter();

protected:
	LPDIRECT3DTEXTURE9 texture = NULL;
	RECT rect;
	RECT colRect;
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
#endif

