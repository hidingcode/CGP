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
#include "Button.h"

// ScoreBoard
#include "ScoreBoard.h"

class Level1: public GameState
{
public:
	Level1();
	~Level1();
	void InitLevel(IDirect3DDevice9* d3dDevice) override;
	void Update(IDirect3DDevice9* d3dDevice) override;
	void Render(LPD3DXSPRITE spriteBrush) override;
	void RenderLine() override;
	void CleanUpLevel() override;

private:
	// Image, Text and Box (Line)
	Image* background = new Image();
	Image* eKey = new Image();
	Text* text = new Text();
	Box* box = new Box();
	Button* retryButton = new Button();
	Button* quitButton = new Button();

	//ScoreBoard 
	ScoreBoard* scoreBoard = new ScoreBoard();

	// Game Object 
	Player* F1 = new Player();
	// Number of Zombie to be spawn
	int spawnNum = 2;
	// zombie[x]  x -> maximum size of zombie array
	Enemy* zombie[20];
};
#endif
