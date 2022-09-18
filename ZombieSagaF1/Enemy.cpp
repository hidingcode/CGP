#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
}

Enemy::Enemy(int textureWidth, int textureHeight, int textureRow, int textureColumn, int maxFrame)
	:GameObject(textureWidth, textureHeight, textureRow, textureColumn, maxFrame)
{
}

void Enemy::Init(D3DXVECTOR2 position, float thrust, float direction, float mass,
	D3DXVECTOR2 scaling, float rotationSpeed, float friction, int hp)
{
	GameObject::Init(position, thrust, direction, mass, scaling, rotationSpeed, friction);
	this->hp = hp;
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

int Enemy::GetHP()
{
	return hp;
}

void Enemy::DecreaseHP(int damage)
{
	hp -= damage;
}




