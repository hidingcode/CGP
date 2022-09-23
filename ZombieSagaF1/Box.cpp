#include "Box.h"

Box::Box()
{

}

Box::~Box()
{
}

void Box::Init(int boxWidth, int boxHeight, D3DXVECTOR2 boxPosition)
{	
	this->position = position;

	pointX = this->position.x + boxWidth;
	pointY = this->position.y + boxHeight;

	point1 = boxPosition;
	point2 = D3DXVECTOR2(pointX, this->position.y);
	point3 = D3DXVECTOR2(pointX, pointY);
	point4 = D3DXVECTOR2(this->position.y, pointY);

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

