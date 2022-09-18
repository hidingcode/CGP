#pragma once
#include "GameObject.h"
#include <d3dx9.h>
#include <iostream>

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(int textureWidth, int textureHeight, int textureRow, int textureColumn, int maxFrame);
	void UpdateAnim();
	// Render the image
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat);
	// Prevent the Game Object from going out the screen
	void CheckBoundary(int WindowWidth, int WindowHeight);
};

