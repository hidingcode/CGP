#include "Character.h"

void Character::InitCharacter(D3DXVECTOR2 characterPosition,  D3DXVECTOR2 characterScaling, D3DXVECTOR2 characterSpriteCentre, 
	float characterMass, float characterMovForce, float characterRotationSpeed)
{	
	
	characterAnimRect.left = 0;
	characterAnimRect.right = characterAnimRect.left + characterSpriteWidth;
	characterAnimRect.top = 0;
	characterAnimRect.bottom = characterAnimRect.top + characterSpriteHeight;

	characterColRect.left = 0;
	characterAnimRect.right = characterAnimRect.left + characterSpriteWidth;
	characterAnimRect.top = 0;
	characterAnimRect.bottom = characterAnimRect.top + characterSpriteHeight;

	characterPosition = D3DXVECTOR2(100, 300);
	characterVelocity = D3DXVECTOR2(0, 0);
	characterAcceleration = D3DXVECTOR2(0, 0);
	characterMovForce = 1;
	characterDirection = 0;
	characterMass = 1;
	characterFrameCounter = 0;

	characterScaling = D3DXVECTOR2(1, 1);
	characterSpriteCentre = D3DXVECTOR2(characterSpriteWidth / 2, characterSpriteHeight / 2);
	characterRotationSpeed = 0.01;
}

void Character::UpdateCharacterAnim()
{
	characterAnimRect.left = 0;
	characterAnimRect.top = characterFrameCounter * characterSpriteHeight;
	characterAnimRect.right = characterAnimRect.left + characterSpriteWidth;
	characterAnimRect.bottom = characterAnimRect.top + characterSpriteHeight;
}

void Character::RenderCharacter()
{
}
