#include "CollisionComponent.h"

bool CollisionComponent::CircleColDetection(int radiusA, int radiusB, D3DXVECTOR2 positionA, 
	D3DXVECTOR2 positionB)
{	
	D3DXVECTOR2 distance = positionA - positionB;
	if (radiusA + radiusB < D3DXVec2Length(&distance))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CollisionComponent::RectColDetection(RECT colRectA, RECT colRectB)
{	
	if (colRectA.left > colRectB.right)
	{
		return false;
	}
	if (colRectA.right < colRectB.left)
	{
		return false;
	}
	if (colRectA.top > colRectB.bottom)
	{
		return false;
	}
	if (colRectA.bottom < colRectB.top)
	{
		return false;
	}
	return true;
}

