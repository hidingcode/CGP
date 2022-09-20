#pragma once
#include "GameObject.h"

class Player: public GameObject 
{
public:
	// Constructor
	Player();
	~Player();
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

private:
	// Store Moving Direction
	int currentDirection = 0;
	// Moving Direction
	enum movDirection { FORWARD, LEFT, RIGHT };
};

