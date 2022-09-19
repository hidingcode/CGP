#include "GameObject.h"

GameObject::GameObject()
{
}

// Destructor
GameObject::~GameObject()
{

}

// Constructor
GameObject::GameObject(int textureWidth, int textureHeight, int textureRow, int textureColumn, int maxFrame)
{	
	this->textureWidth = textureWidth;
	this->textureHeight = textureHeight;
	this->textureRow = textureRow;
	this->textureColumn = textureColumn;
	this->maxFrame = maxFrame;
}

// Initialise Game Object
void GameObject::Init(D3DXVECTOR2 position, float thrust, float direction, float mass, 
	D3DXVECTOR2 scaling, float rotationSpeed, float friction)
{	
	// Calculate Sprite Width and Spite Height
	spriteWidth = textureWidth / textureColumn;
	spriteHeight = textureHeight / textureRow;

	// Crop texture into required rectangle
	spriteRect.left = frameCounter % textureColumn * spriteWidth;
	spriteRect.right = spriteRect.left + spriteWidth;
	spriteRect.top = 0;
	spriteRect.bottom = spriteRect.top + spriteHeight;

	this->position = position;
	velocity = D3DXVECTOR2(0, 0);
	acceleration = D3DXVECTOR2(0, 0);
	this->thrust = thrust;
	this->direction = direction;
	this->mass = mass;

	this->scaling = scaling;
	// Caculate the sprite centre by dividing the sprite widht and sprite height by 2
	spriteCentre = D3DXVECTOR2(spriteWidth * scaling.x / 2, spriteHeight * scaling.y / 2);
	this->rotationSpeed = rotationSpeed;
	this->friction = friction;
}

void GameObject::CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath)
{
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, textureFilePath, &texture);

	if (FAILED(hr)) {
		cout << "Create texture failed" << endl;
	}
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

void GameObject::UpdatePhysics(float bounceDistanceX, float bounceDistanceY)
{ 
	//step1: bounce back to prevent overlapping
	position.x += bounceDistanceX;
	position.y += bounceDistanceY;

	//step2: bounce force applied



	//step3: velocity of object bla bla bla

	//friction stuff
	velocity += acceleration;
	velocity *= 1 - friction;

	position += velocity;
	acceleration = D3DXVECTOR2(0, 0);
}

// Render the image
void GameObject::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat)
{	
	D3DXMatrixTransformation2D(mat, &scalingCentre, scalingRotation, &scaling, &spriteCentre, direction, &position);
	
	// Set the transformation
	spriteBrush->SetTransform(mat);

	// Draw the sprite
	HRESULT hr = spriteBrush->Draw(texture, &spriteRect,NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	if (FAILED(hr)) {
		cout << "Draw Game Object failed" << endl;
	}
}

void GameObject::IncreaseFrameCounter()
{
	frameCounter++;
}

// Get Game Object Texture
LPDIRECT3DTEXTURE9 GameObject::GetTexture()
{
	return texture;
}

// Get Gme Object Position
D3DXVECTOR2 GameObject::GetPosition()
{
	return position;
}

// Get Sprite Centre
D3DXVECTOR2 GameObject::GetSpriteCentre()
{
	return spriteCentre;
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



