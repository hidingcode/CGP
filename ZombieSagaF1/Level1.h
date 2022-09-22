#pragma once
#include "GameLevel.h"
#include <d3dx9.h>

// Game Object
#include "Player.h"
#include "Enemy.h"

// Image, Text, Box
#include "Image.h"
#include "Text.h"
#include "Box.h"

// ScoreBoard
#include "ScoreBoard.h"

class Level1: public GameLevel
{
public:
	Level1();
	~Level1();
	
	bool CircleCollisionDetection(int radiusA, int radiusB, D3DXVECTOR2 positionA, D3DXVECTOR2 positionB);
	void InitLevel(IDirect3DDevice9* d3dDevice);
	void Update(int framesToUpdate, InputManager* inputManager, AudioManager* audioManager,
		vector<GameLevel*> gameLevel);
	void Render(LPD3DXSPRITE spriteBrush);
	void RenderLine();
	void CleanUpLevel();

private:
	// Image 
	Image* background = new Image();

	// Game Object 
	Player* F1 = new Player();
	int spawnNum = 5;
	Enemy zombie[5];

	// Text and Box (Line)
	Text* text = new Text();
	Box* box = new Box();

	//ScoreBoard 
	ScoreBoard* scoreBoard = new ScoreBoard();
};

