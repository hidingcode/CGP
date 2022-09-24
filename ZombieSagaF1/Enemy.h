#ifndef ENEMY_H
#define ENEMY_H
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
	void Init(int textureWidth, int textureHeight, int textureRow, int textureColumn,
		int maxFrame, D3DXVECTOR2 scalingCentre, float scalingRotation, D3DXVECTOR2 position, float thrust,
		float rotation, float mass, D3DXVECTOR2 scaling, float rotationSpeed, float friction, 
		D3DXCOLOR colorFilter, int hp);
	void Update();
	void UpdateAnim();
	// Get the HP of zombie
	int GetHP();
	// Decrease HP
	void DecreaseHP(int damage);
private:
	int hp = 0;
};
#endif

