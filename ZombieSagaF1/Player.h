#pragma once
#include "GameObject.h"

class Player: public GameObject 
{
public:
	// Constructor
	Player(int textureWidth, int textureHeight, int textureRow, int textureColumn, int spriteFPS, int maxFrame);
	// Move the player forward
	void MovForward();
	// Move the player left
	void TurnLeft();
	// Move the player right
	void TurnRight();
	// Move the player backward
	void MovBackward();
	// Get Frame Counter
	int GetFrameCounter();
	// Increase the frame counter to animate the game object
	void IncreaseFrameCounter();

private:
	// Frame counter for animation
	int frameCounter = 0;
};

