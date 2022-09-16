#pragma once
#include "GameObject.h"
#include <d3dx9.h>

class Enemy : public GameObject
{
public:
	Enemy(int textureWidth, int textureHeight, int textureRow, int textureColumn, int maxFrame);

	void UpdateAnim();
};

