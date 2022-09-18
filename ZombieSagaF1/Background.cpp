#include <iostream>
#include "Background.h"

using namespace std;

Background::Background(int textureWidth, int textureHeight) {
	spriteCentre = D3DXVECTOR2(textureWidth / 2, textureHeight / 2);

	// Crop texture into required rectangle
	spriteRect.left = 0;
	spriteRect.right = textureWidth;
	spriteRect.top = 0;
	spriteRect.bottom = textureHeight;
}

Background::~Background()
{
}

void Background::CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath) {
	// Create texture from file
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, textureFilePath, &texture);
	
	if (FAILED(hr)) {
		cout << "Create background texture failed" << endl;
	}
}

void Background::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat, D3DXVECTOR2 scaling, D3DXVECTOR2 position) {
	// Change the position when the scaling change
	D3DXVECTOR2 pos = D3DXVECTOR2(position.x * scaling.x, position.y * scaling.y);
	D3DXMatrixTransformation2D(mat, NULL, 0.0f , &scaling, &spriteCentre, 0.0f, &pos);

	// Set the transformation
	spriteBrush->SetTransform(mat);

	// Draw the sprite
	HRESULT hr = spriteBrush->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	if (FAILED(hr)) {
		cout << "Draw failed" << endl;
	}
}