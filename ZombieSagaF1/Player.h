#pragma once
#include "GameObject.h"

class Player: public GameObject 
{
public:
	// Constructor
	Player(int textureWidth, int textureHeight, int textureRow, int textureColumn, int maxFrame);
	// Move the player forward
	void MovForward();
	// Move the player left
	void TurnLeft();
	// Move the player right
	void TurnRight();
	// Move the player backward
	void MovBackward();
	// Update Physics
	void UpdatePhysics(float pushX, float pushY);
	// Update Animation
	void UpdateAnim();
	// Render the image
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat);
	
};

