#include "GameObject.h"
#include <iostream>

using namespace std;

// Constructor
GameObject::GameObject(int textureWidth, int textureHeight, int textureRow, int textureColumn, int spriteFPS, int maxFrame)
{	
	this->textureWidth = textureWidth;
	this->textureHeight = textureHeight;
	this->textureRow = textureRow;
	this->textureColumn = textureColumn;
	this->spriteFPS = spriteFPS;
	this->maxFrame = maxFrame;
}

// Initialise Game Object
void GameObject::Init(D3DXVECTOR2 position, float engineForce, float direction, float mass, D3DXVECTOR2 scaling, float rotationSpeed)
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
	this->engineForce = engineForce;
	this->direction = direction;
	this->mass = mass;

	this->scaling = scaling;
	// Caculate the sprite centre by dividing the sprite widht and sprite height by 2
	spriteCentre = D3DXVECTOR2(spriteWidth / 2, spriteHeight / 2);
	this->rotationSpeed = rotationSpeed;
}

HRESULT GameObject::CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath)
{
	return D3DXCreateTextureFromFile(d3dDevice, textureFilePath, &texture);
}

void GameObject::Update()
{	
	// Crop texture into required rectangle
	spriteRect.left = frameCounter % textureColumn * spriteWidth;
	spriteRect.right = spriteRect.left + spriteWidth;
	spriteRect.top = 0;
	spriteRect.bottom = spriteRect.top + spriteHeight;

	// If the frame counter exceed max frame set the frame counter back to 0
	// to loop the animation
	if (frameCounter > maxFrame)
	{
		frameCounter = 0;
	}
}
 
void GameObject::Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat)
{	
	D3DXMatrixTransformation2D(mat, &scalingCentre, scalingRotation, &scaling, &spriteCentre, direction, &position);
	
	// Set the transformation
	spriteBrush->SetTransform(mat);

	// Draw the sprite
	HRESULT hr = spriteBrush->Draw(texture, &spriteRect,NULL,NULL, D3DCOLOR_XRGB(255, 255, 255));
	if (FAILED(hr)) {
		cout << "Draw failed" << endl;
	}
}

LPDIRECT3DTEXTURE9 GameObject::GetTexture()
{
	return texture;
}

int GameObject::GetFrameCounter() {
	return frameCounter;
}

void GameObject::IncreaseFrameCounter()
{
	frameCounter++;
}

