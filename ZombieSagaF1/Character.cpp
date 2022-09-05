#include "Character.h"

void Character::Init()
{	
	
	this->characterAnimRect.left = 0;
	this->characterAnimRect.right = this->characterAnimRect.left + characterSpriteWidth;
	this->characterAnimRect.top = 0;
	this->characterAnimRect.bottom = this->characterAnimRect.top + characterSpriteHeight;

	this->characterColRect.left = 0;
	this->characterAnimRect.right = this->characterAnimRect.left + characterSpriteWidth;
	this->characterAnimRect.top = 0;
	this->characterAnimRect.bottom = this->characterAnimRect.top + characterSpriteHeight;

	this->characterPosition = D3DXVECTOR2(100, 300);
	this->characterVelocity = D3DXVECTOR2(0, 0);
	this->characterAcceleration = D3DXVECTOR2(0, 0);
	this->characterMovForce = 1;
	this->characterDirection = 0;
	this->characterMass = 1;
	this->characterFrameCounter = 0;

	this->characterScaling = D3DXVECTOR2(1, 1);
	this->characterSpriteCentre = D3DXVECTOR2(characterSpriteWidth / 2, characterSpriteHeight / 2);
	this->characterRotationSpeed = 0.01;
}

void Character::UpdateAnim()
{
	characterAnimRect.left = 0;
	characterAnimRect.top = characterFrameCounter * characterSpriteHeight;
	characterAnimRect.right = characterAnimRect.left + characterSpriteWidth;
	characterAnimRect.bottom = characterAnimRect.top + characterSpriteHeight;
}

void Character::Render()
{
}
