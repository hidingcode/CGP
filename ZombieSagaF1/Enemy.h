#pragma once
#include "GameObject.h"
#include <d3dx9.h>
#include <iostream>

class Enemy : public GameObject
{
public:
	// Constructor
	Enemy();
	// Destructor
	~Enemy();
	Enemy(int textureWidth, int textureHeight, int textureRow, int textureColumn, int maxFrame);
	void Init(D3DXVECTOR2 position, float thrust, float direction, float mass,
		D3DXVECTOR2 scaling, float rotationSpeed, float friction, int hp);
	void UpdateAnim();
	// Render the image
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat);
	// Get the HP of zombie
	int GetHP();
	// Decrease HP
	void DecreaseHP(int damage);
private:
	int hp = 0;
};

