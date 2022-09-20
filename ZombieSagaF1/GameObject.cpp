#include "GameObject.h"

GameObject::GameObject()
{
}

// Destructor
GameObject::~GameObject()
{

}

// Initialise Game Object
void GameObject::Init(int textureWidth, int textureHeight, int textureRow, int textureColumn, 
	int maxFrame, D3DXVECTOR2 scalingCentre,float scalingRotation, D3DXVECTOR2 position, float thrust, 
	float rotation, float mass, D3DXVECTOR2 scaling, float rotationSpeed,float friction, D3DXCOLOR colorFilter)
{
	this->textureWidth = textureWidth;
	this->textureHeight = textureHeight;
	this->textureRow = textureRow;
	this->textureColumn = textureColumn;
	this->maxFrame = maxFrame;

	// Calculate Sprite Width and Spite Height
	spriteWidth = textureWidth / textureColumn;
	spriteHeight = textureHeight / textureRow;
	
	// Crop texture into required rectangle
	rect.left = frameCounter % textureColumn * spriteWidth;
	rect.right = rect.left + spriteWidth;
	rect.top = 0;
	rect.bottom = rect.top + spriteHeight;
	
	RenderComponent::InitSprite(scalingCentre, scalingRotation, scaling, D3DXVECTOR2(spriteWidth * scaling.x / 2, spriteHeight * scaling.y / 2),
		rotation, position, colorFilter);

	this->position = position;
	velocity = D3DXVECTOR2(0, 0);
	acceleration = D3DXVECTOR2(0, 0);
	this->thrust = thrust;
	this->mass = mass;

	this->scaling = scaling;
	// Caculate the sprite centre by dividing the sprite widht and sprite height by 2
	this->rotationSpeed = rotationSpeed;
	this->friction = friction;
}

// Check the boundary to prevent the game object from going out oute the screen
void GameObject::CheckBoundary(int WindowWidth, int WindowHeight) {
	if (position.x <0 || position.x > WindowWidth - spriteWidth * scaling.x) {
		velocity.x *= -1;
	}
	if (position.y <0 || position.y > WindowHeight - spriteHeight * scaling.y) {
		velocity.y *= -1;
	}
}

void GameObject::UpdatePhysics()
{ 
	//step1: bounce back to prevent overlapping
	/*position.x += bounceDistanceX;
	position.y += bounceDistanceY;*/

	//step2: bounce force applied



	//step3: velocity of object bla bla bla

	//friction stuff
	velocity += acceleration;
	velocity *= 1 - friction;

	position += velocity;
	acceleration = D3DXVECTOR2(0, 0);
}

D3DXVECTOR2 GameObject::GetVelocity()
{
	return velocity;
}

void GameObject::SetVelocity(D3DXVECTOR2 velocity)
{
	this->velocity = velocity;
}

// Get Sprite Width
int GameObject::GetSpriteWidth()
{	
	return spriteWidth * scaling.x;
}

// Get Sprite Height
int GameObject::GetSpriteHeight()
{
	return spriteHeight * scaling.y;
}

int GameObject::GetMass()
{
	return mass;
}



