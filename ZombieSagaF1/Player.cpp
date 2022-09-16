#include "Player.h"
using namespace std;

Player::Player(int textureWidth, int textureHeight, int textureRow, int textureColumn, int maxFrame)
	:GameObject(textureWidth, textureHeight, textureRow, textureColumn, maxFrame)
{
}

void Player::MovForward() // ! (Bug)--> Velocity does not decrease
{
	acceleration.x = sin(direction) * thrust;
	acceleration.y = -cos(direction) * thrust;
}

void Player::TurnLeft()
{
	direction -= rotationSpeed;
}

void Player::TurnRight()
{
	direction += rotationSpeed;
}

void Player::MovBackward()
{
	acceleration.x = -sin(direction) * thrust / mass;
	acceleration.y = cos(direction) * thrust / mass;
}

void Player::UpdatePhysics() { // Xin Nan part
	cout << "Friction: " << friction << endl;
	velocity += acceleration;
	velocity *= 1 - friction;
	position += velocity;
	acceleration = D3DXVECTOR2(0, 0);
}

// Update Animation
void Player::UpdateAnim()
{
	// Crop texture into required rectangle
	spriteRect.left = frameCounter % textureColumn * spriteWidth;
	spriteRect.right = spriteRect.left + spriteWidth;
	spriteRect.top = 0;
	spriteRect.bottom = spriteRect.top + spriteHeight;

	// If the frame counter exceed max frame set the frame counter back to 0
	// to loop the animation
	if (frameCounter > maxFrame)
	{
		frameCounter = 0;
	}
}
