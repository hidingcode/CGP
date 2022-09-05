#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "Texture.h"

class GameObject
{
public:
	GameObject();
	// Initialise GameObject
	void Init();
	// Render Game Object
	void Render();
private:
	// Character Animation Rectangle
	RECT animRect;
	// Character Collision Rectangle
	RECT colRect;
	// Character Position
	D3DXVECTOR2 position;
	// Character Velocity
	D3DXVECTOR2 velocity;
	// Character Acceleration
	D3DXVECTOR2 acceleration;
	// Character Movement Force
	float movForce = 0;
	// Character Facing Direction
	float direction = 0;
	// Character Mass
	float mass = 0;
	// Character Frame Counter for Animation
	int frameCounter = 0;
	// Character Scalling
	D3DXVECTOR2 characterScaling;
	// Character Sprite Centre
	D3DXVECTOR2 characterSpriteCentre;
	// Character Rotate Speed
	float rotationSpeed = 0;
};

