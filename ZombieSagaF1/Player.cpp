#include "Player.h"
using namespace std;

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

// Render the image
void Player::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat)
{
	D3DXMatrixTransformation2D(mat, &scalingCentre, scalingRotation, &scaling, &spriteCentre, direction, &position);

	// Set the transformation
	spriteBrush->SetTransform(mat);

	// Draw the sprite
	HRESULT hr = spriteBrush->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	if (FAILED(hr)) {
		cout << "Draw Game Object failed" << endl;
	}
}

