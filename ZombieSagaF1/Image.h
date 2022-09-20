#pragma once
#include "RenderComponent.h"

class Image: public RenderComponent
{
public:
	// Constructor
	Image();
	// Destructor
	~Image();

	void Init(int textureWidth, int textureHeight, D3DXVECTOR2 scalingCentre, 
		float scalingRotation, D3DXVECTOR2 position, float rotation, D3DXVECTOR2 scaling, 
		D3DXCOLOR colorFilter);

};