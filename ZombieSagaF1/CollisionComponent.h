#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H
#include <d3dx9.h>

class CollisionComponent
{
public:
	bool CircleColDetection(int radiusA, int radiusB, D3DXVECTOR2 positionA,
		D3DXVECTOR2 positionB);
	bool RectColDetection(RECT colRectA, RECT colRectB);
};

#endif

