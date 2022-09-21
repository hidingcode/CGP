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
};

