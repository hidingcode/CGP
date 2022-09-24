#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
}

void Enemy::Init(int textureWidth, int textureHeight, int textureRow, int textureColumn,
	int maxFrame, D3DXVECTOR2 scalingCentre, float scalingRotation, D3DXVECTOR2 position, float thrust,
	float rotation, float mass, D3DXVECTOR2 scaling, float rotationSpeed, float friction, D3DXCOLOR colorFilter, 
	int hp)
{
	GameObject::Init(textureWidth, textureHeight, textureRow, textureColumn,
		maxFrame, scalingCentre, scalingRotation, position, thrust,
		rotation, mass, scaling, rotationSpeed, friction, colorFilter);
	this->hp = hp;
}

void Enemy::Update()
{
	GameObject::Update();
	UpdateAnim();
}

void Enemy::UpdateAnim()
{	
	frameCounter++;

	// Crop texture into required rectangle
	rect.left = frameCounter % textureColumn * spriteWidth;
	rect.right = rect.left + spriteWidth;
	rect.top = 0;
	rect.bottom = rect.top + spriteHeight;

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




