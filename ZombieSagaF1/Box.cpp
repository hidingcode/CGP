#include "Box.h"

Box::Box()
{

}

Box::~Box()
{
}

void Box::Init(int boxWidth, int boxHeight, D3DXVECTOR2 boxPosition)
{	
	// Calculate the X position for point 2 and 3 according to the box width
	pointX = boxPosition.x + boxWidth;
	// Calculate the X position for point 3 and 4 according to the box height
	pointY = boxPosition.y + boxHeight;

	// 1----------------2
	// |				|
	// |				|
	// 4----------------3
	// 1 - Point 1
	// 2 - Point 2
	// 3 - Point 3
	// 4 - Point 4

	// Set the point to draw line
	point1 = boxPosition;
	point2 = D3DXVECTOR2(pointX, boxPosition.y);
	point3 = D3DXVECTOR2(pointX, pointY);
	point4 = D3DXVECTOR2(boxPosition.y, pointY);

	lineVertices[0] = point1;
	lineVertices[1] = point2;
	lineVertices[2] = point3;
	lineVertices[3] = point4;
	lineVertices[4] = point1;
}

void Box::RenderLine(D3DXCOLOR color)
{
	line->Begin();
	line->Draw(lineVertices, 5, color);
	line->End();
}

