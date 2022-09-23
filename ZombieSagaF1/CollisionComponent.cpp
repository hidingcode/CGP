#include "CollisionComponent.h"

//Get radius between two object and also the current positon of both object
//We will get the centre position instead of the postion of the object
bool CollisionComponent::CircleColDetection(int radiusA, int radiusB, D3DXVECTOR2 positionA, 
	D3DXVECTOR2 positionB)
{	
	//The distance between two object's centre position of circle


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

// This is Rectangle Collision detection.  it can detect the collision between two object with rectangle collision detection.
bool CollisionComponent::RectColDetection(RECT colRectA, RECT colRectB)
{	
	//It basically check all situation when both of them is not collide together
	// if it miss all the 'Not collide' condition, it will return true to shows they are collided to each other.
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

