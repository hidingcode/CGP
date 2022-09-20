#include "Text.h"

Text::Text()
{
}

Text::~Text()
{

}

void Text::Init(int rectWidth, int rectHeight, D3DXVECTOR2 scalingCentre, float scalingRotation, 
	D3DXVECTOR2 scaling, D3DXVECTOR2 rotationCentre, float rotation, D3DXVECTOR2 position, 
	LPCSTR textContent, int textLength, UINT format, D3DXCOLOR colorFilter)
{	

	rect.left = 0;
	rect.right = rectWidth;
	rect.top = 0;
	rect.bottom = rectHeight;
	
	RenderComponent::InitText(scalingCentre, scalingRotation, scaling, rotationCentre, rotation, position, textContent,
		textLength, format, colorFilter);
}
