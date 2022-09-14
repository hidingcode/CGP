#pragma once
#include "GameObject.h"

class Player: public GameObject 
{
public:
	// Constructor
	Player(int textureWidth, int textureHeight, int textureRow, int textureColumn, int spriteFPS, int maxFrame);
	// Update movement
	void MovForward();
	void TurnLeft();
	void TurnRight();
	void MovBackward();
	// Get Frame Counter
	int GetFrameCounter();
	// Increase the frame counter to animate the game object
	void IncreaseFrameCounter();

private:
	// Frame counter for animation
	int frameCounter = 0;
};

