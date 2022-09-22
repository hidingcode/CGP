#pragma once
#include <d3dx9.h>
#include <string>
#ifndef TEXT_H
#define TEXT_H
#include "RenderComponent.h" 

class Text: public RenderComponent
{
public:
	// Constructor
	Text();
	// Destructor
	~Text();
	// Initialise Text 
	void Init(int rectWidth, int rectHeight, D3DXVECTOR2 scalingCentre, float scalingRotation,
		D3DXVECTOR2 scaling, D3DXVECTOR2 rotationCentre, float rotation, D3DXVECTOR2 position,
		int textLength, UINT format, D3DXCOLOR colorFilter);	
};
#endif

