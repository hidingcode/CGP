#pragma once
#include <d3dx9.h>

class Box
{
public:
	// Constructor
	Box();
	// Destructor
	~Box();
	// Initialisation of box in Rectangle, box position is the top left corner of the box
	void Init(int boxWidth, int boxHeight, D3DXVECTOR2 boxPosition);
	// Render Line
	void Render(LPD3DXLINE line, D3DXCOLOR color);
	D3DXVECTOR2 GetBoxPosition();
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

	// Box Position (Point 1 position)
	D3DXVECTOR2 boxPosition;

	// Use to determine the X value for point 2 and point 3
	int pointX;
	// Use to determine the X value for point 4 and point 3
	int pointY;
	// Line Vertices 
	D3DXVECTOR2 lineVertices[];
};