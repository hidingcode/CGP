#pragma once
#include "Image.h"

class Button : public Image
{
public:
	Button();
	~Button();
	// Check If There is Any Collision With The Button
	bool OnCollide(RECT rect, D3DXVECTOR2 position);
	// Set Position of Panel
};

