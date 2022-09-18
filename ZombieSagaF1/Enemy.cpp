#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(int textureWidth, int textureHeight, int textureRow, int textureColumn, int maxFrame)
	:GameObject(textureWidth, textureHeight, textureRow, textureColumn, maxFrame)
{

}

void Enemy::UpdateAnim()
{	
	IncreaseFrameCounter();

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
void Enemy::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat)
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

void Enemy::CheckBoundary(int WindowWidth, int WindowHeight)
{
	if (position.x <0 || position.x > WindowWidth - spriteWidth * scaling.x) {
		velocity.x *= -1;
	}
	if (position.y <0 || position.y > WindowHeight - spriteHeight * scaling.y) {
		velocity.y *= -1;
	}
}



