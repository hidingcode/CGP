#pragma once
#include "RenderComponent.h"
#include <iostream>
using namespace std;

class GameObject: public RenderComponent
{
public:
	// Constructor
	GameObject();
	// Destructor
	~GameObject();
	
	// Initialise GameObject
	void Init(int textureWidth, int textureHeight, int textureRow, int textureColumn,
		int maxFrame, D3DXVECTOR2 scalingCentre, float scalingRotation, D3DXVECTOR2 position, float thrust,
		float rotation, float mass, D3DXVECTOR2 scaling, float rotationSpeed, float friction, D3DXCOLOR colorFilter);

	// Update Game Object Physics
	void Update(int WindowWidth, int WindowHeight);

	// Update Animation
	void UpdateAnim();

	// Get Velocty
	D3DXVECTOR2 GetVelocity();

	// Set Velocity
	void SetVelocity(D3DXVECTOR2 velocity);
	
	// Get Sprite Width
	int GetSpriteWidth();

	// Get Sprite Height
	int GetSpriteHeight();

	// Get Mass
	int GetMass();

protected:
	// Game Object Texture Data
	int textureWidth = 0;
	int textureHeight = 0;
	int textureRow = 0;
	int textureColumn = 0;
	int spriteWidth = 0;
	int spriteHeight = 0;
	int maxFrame = 0;

	// Movement and Physics Calculation Variable
	D3DXVECTOR2 velocity = D3DXVECTOR2(0, 0);
	D3DXVECTOR2 acceleration = D3DXVECTOR2(0, 0);
	// Force
	float thrust = 0.0f;
	float mass = 0.0f;
	float rotationSpeed = 0.0f;
	// Frcition
	float friction = 0.0f;
	// Frame counter for animation
	int frameCounter = 0.0f;
};

