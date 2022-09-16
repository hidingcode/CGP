#include "Enemy.h"
#include "GameObject.h"

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