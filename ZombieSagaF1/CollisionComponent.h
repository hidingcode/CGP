#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H
#include <d3dx9.h>

class CollisionComponent
{
public:
	// Circle Collision Detection - position = Midpoint of circle
	bool CircleColDetection(int radiusA, int radiusB, D3DXVECTOR2 positionA,
		D3DXVECTOR2 positionB);
	// Rectangle Collision Detection
	bool RectColDetection(RECT colRectA, RECT colRectB);
};

#endif

