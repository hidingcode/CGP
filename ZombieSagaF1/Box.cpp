#include "Box.h"

Box::Box()
{

}

Box::~Box()
{
}

void Box::CreateLine(IDirect3DDevice9* d3dDevice)
{
	HRESULT hr = D3DXCreateLine(d3dDevice, &line);

	if (FAILED(hr)) {
		cout << "Create line failed" << endl;
	}
}

void Box::CleanUpLine()
{
	line->Release();
	line = NULL;
}

void Box::Init(int boxWidth, int boxHeight, D3DXVECTOR2 boxPosition)
{	
	this->boxPosition = boxPosition;

	pointX = this->boxPosition.x + boxWidth;
	pointY = this->boxPosition.y + boxHeight;

	point1 = boxPosition;
	point2 = D3DXVECTOR2(pointX, this->boxPosition.y);
	point3 = D3DXVECTOR2(pointX, pointY);
	point4 = D3DXVECTOR2(this->boxPosition.y, pointY);

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

D3DXVECTOR2 Box::GetBoxPosition()
{
	return boxPosition;
}
