#pragma once
#include <Windows.h>
#include <d3dx9.h>

class Character 
{
	public:
		Character();
		// Initialise Character
		void InitCharacter(D3DXVECTOR2 characterPosition, D3DXVECTOR2 characterMovForce, D3DXVECTOR2 characterScaling, D3DXVECTOR2 characterSpriteCentre, float characterMass, float characterRotationSpeed);
		void UpdateCharacter();
	private:
		// Character Animation Rectangle
		RECT characterAnimRect;
		// Character Collision Rectangle
		RECT characterColRect;
		// Character Position
		D3DXVECTOR2 characterPosition;
		// Character Velocity
		D3DXVECTOR2 characterVelocity;
		// Character Acceleration
		D3DXVECTOR2 characterAcceleration;
		// Character Movement Force
		float characterMovForce = 0;
		// Character Facing Direction
		float characterDirection = 0;
		// Character Mass
		float characterMass = 0;
		// Character Frame Counter for Animation
		int characterFrameCounter = 0;
		// Character Scalling
		D3DXVECTOR2 characterScaling;
		// Character Sprite Centre
		D3DXVECTOR2 characterSpriteCentre;
		// Character Rotate Speed
		float playerRotationSpeed = 0;
};