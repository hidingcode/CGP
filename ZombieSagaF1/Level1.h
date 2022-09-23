#ifndef LEVEL1_H
#define LEVEL1_H
#include "GameState.h"
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

class Level1: public GameState
{
public:
	bool CircleCollisionDetection(int radiusA, int radiusB, D3DXVECTOR2 positionA, D3DXVECTOR2 positionB);
	
	void InitLevel(IDirect3DDevice9* d3dDevice, MyWindowManager* windowManager);
	void Update(int framesToUpdate, InputManager* inputManager, AudioManager* audioManager,
		vector<GameState*> gameState, MyWindowManager* windowManager);
	
	void Render(LPD3DXSPRITE spriteBrush);
	void RenderLine();
	void CleanUpLevel();

	static Level1* Instance() {
		return &level1Ref;
	}

protected:
	/*Level1();*/

private:
	static Level1 level1Ref;

	// Image 
	Image* background = new Image();

	// Game Object 
	Player* F1 = new Player();
	// Number of Zombie to be spawn
	int spawnNum = 5;
	// zombie[x]  x -> maximum size of zombie array
	Enemy zombie[20];

	// Text and Box (Line)
	Text* text = new Text();
	Box* box = new Box();

	//ScoreBoard 
	ScoreBoard* scoreBoard = new ScoreBoard();
};
#endif
