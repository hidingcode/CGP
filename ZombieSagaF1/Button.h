#pragma once
#include "Background.h"

class Button : public Background
{
public:
	Button(int textureWidth, int textureHeight);
	~Button();
	// Check If There is Any Collision With The Button
	void CheckCollision();
	// Set Position of Panel
	void SetPosition(D3DXVECTOR2 position);
	// Get Position of Panel
	D3DXVECTOR2 GetPosition();
	// Get Position of Panel
	int	GetTextureWidth();
	// Get Position of Panel
	int GetTextureHeight();
private:
	int textureWidth = 0;
	int textureHeight = 0;
	D3DXVECTOR2 position;
};

