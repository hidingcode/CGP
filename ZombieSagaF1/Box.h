#ifndef BOX_H
#define BOX_H

#include <d3dx9.h>
#include <iostream>
#include "RenderComponent.h"
using namespace std;

class Box : public RenderComponent
{
public:
	// Constructor
	Box();
	// Destructor
	~Box();
	// Initialisation of box in Rectangle, box position is the top left corner of the box
	void Init(int boxWidth, int boxHeight, D3DXVECTOR2 boxPosition);
	// Render Line
	void RenderLine(D3DXCOLOR color);

private:
	
	// 1----------------2
	// |				|
	// |				|
	// 4----------------3
	// 1 - Point 1
	// 2 - Point 2
	// 3 - Point 3
	// 4 - Point 4
	D3DXVECTOR2 point1;
	D3DXVECTOR2 point2;
	D3DXVECTOR2 point3;
	D3DXVECTOR2 point4;

	// Calculate the X position for point 2 and 3 according to the box width
	int pointX = 0;
	// Calculate the X position for point 3 and 4 according to the box height
	int pointY = 0;
	// Line Vertices 
	D3DXVECTOR2 lineVertices[];
};
#endif
