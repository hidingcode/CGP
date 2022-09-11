#pragma once
#include <Windows.h>
#include <d3dx9.h>

class GameObject
{
public:
	// Constructor
	GameObject(int textureWidth,int textureHeight,int textureRow, int textureColumn,int spriteFPS,int maxFrame);
	
	// Initialise GameObject
	void Init(D3DXVECTOR2 position, float engineForce, float direction, float mass, D3DXVECTOR2 scaling, float rotationSpeed);
	
	// Create Texture
	HRESULT CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath);
	
	// Render Game Object
	void Update();
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat);
	
	// Getter
	LPDIRECT3DTEXTURE9 GetTexture();
	int GetFrameCounter();

	// Increase the frame counter to animate the player object
	void IncreaseFrameCounter();
	
private:
	// Texture and animation variables

	// Game Object Texture
	LPDIRECT3DTEXTURE9 texture = NULL;
	int textureWidth = 0;
	int textureHeight = 0;
	int textureRow = 0;
	int textureColumn = 0;
	int spriteWidth = 0;
	int spriteHeight = 0;
	int spriteFPS = 0;
	int maxFrame = 0;

	// Spirte Rectangle
	RECT spriteRect;
	// Frame counter for animation
	int frameCounter = 0;

	// Movement and Physics Calculation Variable

	D3DXVECTOR2 position;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 acceleration;
	D3DXVECTOR2 scalingCentre = D3DXVECTOR2(0,0);
	float scalingRotation = 0.0f;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 spriteCentre;
	float engineForce = 0;
	// Facing Direction
	float direction = 0;
	float mass = 0;
	float rotationSpeed = 0;
};

