#ifndef PLAYER_H
#define PLAYER_H
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
	// Get Collision Rectangle
	RECT GetColRectangle();

private:
	// Store Moving Direction
	int currentDirection = 0;
	// Moving Direction
	enum movDirection { FORWARD, LEFT, RIGHT };
};
#endif

