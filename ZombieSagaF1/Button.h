#ifndef BUTTON_H
#define BUTTON_H
#include "Image.h"
#include "CollisionComponent.h"

class Button : public Image, public CollisionComponent
{
public:
	Button();
	~Button();
	// Check If There is Any Collision With The Button
	bool OnCollide(RECT colRect);
	void CalColRect();
};
#endif

