#pragma once
#include <Windows.h>
#include <d3dx9.h>

class GameObject
{
public:
	// Constructor
	GameObject();
	GameObject(int texture,int textureHeight,int textureRow, int textureColumn,int spriteFPS,int maxFrame);
	
	// Initialise GameObject
	void Init(D3DXVECTOR2 position, float thrust, float direction, float mass, D3DXVECTOR2 scaling, float rotationSpeed, float friction);
	
	// Create Texture
	HRESULT CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath);
	
	//// Update movement
	//void MovForward();
	//void TurnLeft();
	//void TurnRight();
	//void MovBackward();

	// Update Physics
	void UpdatePhysics();
	// Update Animation
	void UpdateAnim();
	// Render Game Object
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat);
	// Prevent the Game Object from going out the screen
	void CheckBoundary(int WindowWidth, int WindowHeight);
	// Get Texture
	LPDIRECT3DTEXTURE9 GetTexture();
	
protected:
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
	
	// Movement and Physics Calculation Variable
	D3DXVECTOR2 position;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 acceleration;
	D3DXVECTOR2 scalingCentre = D3DXVECTOR2(0,0);
	float scalingRotation = 0.0f;
	D3DXVECTOR2 scaling;
	D3DXVECTOR2 spriteCentre;
	float thrust = 0;
	// Facing Direction
	float direction = 0;
	float mass = 0;
	float rotationSpeed = 0;

	// Frcition
	float friction = 0.0f;
	// Frame counter for animation
	int frameCounter = 0;
};

