#pragma once
#include "Image.h"

class Button : public Image
{
public:
	Button();
	~Button();
	// Check If There is Any Collision With The Button
	bool OnCollide(RECT rect);
	// Set Position of Panel
	void SetPosition(D3DXVECTOR2 position);
	// Get Position of Panel
	D3DXVECTOR2 GetPosition();
	// Get Position of Panel
	int	GetTextureWidth();
	// Get Position of Panel
	int GetTextureHeight();
	// Get Rectangle
	RECT GetRect();
private:
	int textureWidth = 0;
	int textureHeight = 0;
	D3DXVECTOR2 position;
};

