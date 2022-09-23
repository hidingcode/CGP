#include "Player.h"
using namespace std;

Player::Player()
{
}

Player::~Player()
{

}

void Player::MovForward()
{	
	// Set the current direction to change to the move forward animation
	currentDirection = FORWARD;
	frameCounter++;
	acceleration.x = sin(rotation) * thrust / mass;
	acceleration.y = -cos(rotation) * thrust / mass;
}

void Player::TurnLeft()
{	
	// Set the current direction to change to the move left animation
	currentDirection = LEFT;
	rotation -= rotationSpeed;
}

void Player::TurnRight()
{	
	// Set the current direction to change to the move right animation
	currentDirection = RIGHT;
	rotation += rotationSpeed;
}

void Player::MovBackward()
{	
	// Set the current direction to change to the move forward animation
	currentDirection = FORWARD;
	frameCounter++;
	acceleration.x = -sin(rotation) * thrust / mass;
	acceleration.y = cos(rotation) * thrust / mass;
}

void Player::Update(int WindowWidth, int WindowHeight)
{
	GameObject::Update(WindowWidth, WindowHeight);
	UpdateAnim();
}

// Update Animation
void Player::UpdateAnim()
{
	// Crop texture into required rectangle
	rect.left = frameCounter % textureColumn * spriteWidth;
	rect.right = rect.left + spriteWidth;
	rect.top = currentDirection * spriteHeight;
	rect.bottom = rect.top + spriteHeight;

	//collision rectangle
	colRect.top = position.y;
	colRect.left = position.x;
	colRect.bottom = colRect.top + (spriteWidth * scaling.y);
	colRect.right = colRect.left + (spriteHeight * scaling.x);

	// If the frame counter exceed max frame set the frame counter back to 0
	// to loop the animation
	if (frameCounter > maxFrame)
	{
		frameCounter = 0;
	}
}




