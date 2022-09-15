#include "Player.h"

Player::Player(int textureWidth, int textureHeight, int textureRow, int textureColumn, int maxFrame)
	:GameObject(textureWidth, textureHeight, textureRow, textureColumn, maxFrame)
{
}

void Player::MovForward() // ! (Bug)--> Velocity does not decrease
{
	acceleration.x = sin(direction) * thrust / mass;
	acceleration.y = -cos(direction) * thrust / mass;
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

void Player::IncreaseFrameCounter()
{
	frameCounter++;
}
