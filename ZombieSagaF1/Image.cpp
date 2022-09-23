#include <iostream>
#include "Image.h"

using namespace std;

Image::Image()
{
}

Image::~Image()
{
}

void Image::Init(int textureWidth, int textureHeight, D3DXVECTOR2 scalingCentre,
	float scalingRotation, D3DXVECTOR2 position, float rotation, D3DXVECTOR2 scaling, D3DXCOLOR colorFilter)
{	
	this->textureWidth = textureWidth;
	this->textureHeight = textureHeight;

	// Crop texture into required rectangle
	rect.left = 0;
	rect.right = textureWidth;
	rect.top = 0;
	rect.bottom = textureHeight;
	
	RenderComponent::InitSprite(textureWidth, textureHeight, scalingCentre, scalingRotation, scaling, D3DXVECTOR2(textureWidth * scaling.x / 2, textureHeight * scaling.y / 2),
		rotation, position, colorFilter);

	
}

