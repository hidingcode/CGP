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
	// Update
	void Update(int WindowWidth, int WindowHeight);
	// Update Animation
	void UpdateAnim();
	RECT GetColRectangle();
	
	
	
private:
	// Store Moving Direction
	int currentDirection = 0;
	// Moving Direction
	enum movDirection { FORWARD, LEFT, RIGHT };
	//Collision Rectangle
	RECT ColRect;
	
};

