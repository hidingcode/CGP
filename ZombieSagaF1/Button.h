#ifndef BUTTON_H
#define BUTTON_H
#include "Image.h"

class Button : public Image
{
public:
	Button();
	~Button();
	// Check If There is Any Collision With The Button
	bool OnCollide(RECT ColRect);
	// Set Position of Panel

	void GetColStuff();
};
#endif

