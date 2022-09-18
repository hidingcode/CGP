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
	// Update Animation
	void UpdateAnim();
	// Set Current Direction to Forward
	void SetForward();
	// Set Current Direction to Left
	void SetLeft();
	// Set Current Direction to Right
	void SetRight();

private:
	// Store Moving Direction
	int currentDirection = 0;
	// Moving Direction
	enum movDirection { FORWARD, LEFT, RIGHT };
};

