#include "Level1.h"
#include "MainMenu.h"

Level1::Level1()
{
}

Level1::~Level1()
{
}

void Level1::InitLevel(IDirect3DDevice9* d3dDevice)
{	
	srand(time(0));

	// Create Texture and Initialise Game Object, UI and Images
	background->CreateTexture(d3dDevice, "Assets/roadBG.png");
	background->Init(840, 650, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(1, 1), 
		D3DCOLOR_XRGB(255, 255, 255));

	F1->CreateTexture(d3dDevice, "Assets/F1.png");
	F1->Init(768, 450, 3, 6, 5, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(395, 580), 1.0f, 0.0f, 2.0f,
		D3DXVECTOR2(0.4f, 0.4f), 0.05f, 0.05f, D3DCOLOR_XRGB(255, 255, 255));

	for (int i = 0; i < spawnNum; i++)
	{
		zombie[i] = Enemy();
		zombie[i].CreateTexture(d3dDevice, "Assets/zombie_idle.png");
		// Spawn the zombie in random position
		D3DXVECTOR2 randomSpawn = D3DXVECTOR2(rand() % (WindowWidth - zombie[i].GetSpriteWidth() - 100),
			rand() % (WindowHeight - zombie[i].GetSpriteHeight() - 100));

		zombie[i].Init(3774, 230, 1, 17, 16, D3DXVECTOR2(0, 0), 0.0f, randomSpawn, 0.0f, 0.0f, 1.0f,
			D3DXVECTOR2(0.3f, 0.3f), 0.0f, 0.01f, D3DCOLOR_XRGB(255, 255, 255), 2);
	}

	retryButton->CreateTexture(d3dDevice, "Assets/retryButton.png");
	retryButton->Init(205, 75, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(310, 310), 0.0f,
		D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(255, 255, 255));
	eKey->CreateTexture(d3dDevice, "Assets/e-key.png");
	eKey->Init(215, 220, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(550, 330), 0.0f, D3DXVECTOR2(0.18, 0.18),
		D3DCOLOR_XRGB(255, 255, 255));

	box->CreateLine(d3dDevice);
	box->Init(120, 30, D3DXVECTOR2(0, 0));

	text->CreateFontType(d3dDevice, "Arial");
	text->Init(200, 200, D3DXVECTOR2(1, 1), 0.0f, D3DXVECTOR2(1, 1), text->GetPosition(), 0.0f,
		box->GetPosition(), -1, 0, D3DCOLOR_XRGB(0, 0, 0));

}

void Level1::Update(vector<GameState*> gameState, IDirect3DDevice9* d3dDevice)
{	
	// Update Sound
	audioManager->UpdateSound();
	// Manage the playing state of the car engine sound
	audioManager->ManageCarEngineSound(inputManager->GetKeyPress(DIK_W), inputManager->GetKeyPress(DIK_S));
	// Pan the car engine sound left to right according to the F1 position
	audioManager->DynamicCarEngineSound(WindowWidth, F1->GetPosition().x);

	if (inputManager->GetKeyPress(DIK_W)) {
		F1->MovForward();
	}
	if (inputManager->GetKeyPress(DIK_S)) {
		F1->MovBackward();
	}
	if (inputManager->GetKeyPress(DIK_A)) {
		F1->TurnLeft();
	}
	if (inputManager->GetKeyPress(DIK_D)) {
		F1->TurnRight();
	}
	if (inputManager->GetKeyPress(DIK_P)) {
		cout << "P Pressed" << endl;
		gameState.pop_back();
		gameState.push_back(new Level1());
		gameState.back()->InitLevel(d3dDevice);
	}

	for (int i = 0; i < spawnNum; i++)
	{
		if (zombie[i].GetHP() > 0)
		{
			if (F1->CircleColDetection(F1->GetSpriteWidth() / 2, zombie[i].GetSpriteWidth() / 2, F1->GetPosition() , zombie[i].GetPosition()))
			{
				cout << "Collision occurs" << endl;
				audioManager->PlayCollisionSound();

				// Calculate the bouncing vector of F1 after collision
				D3DXVECTOR2 f1FVelocity = F1->GetVelocity() * (F1->GetMass() - zombie[i].GetMass()) + 
					2 * zombie[i].GetMass() * zombie[i].GetVelocity() / (F1->GetMass() + zombie[i].GetMass());

				// Calculate the bouncing vector of zombie after collision
				D3DXVECTOR2 zombieFVelocity = zombie[i].GetVelocity() * (zombie[i].GetMass() - F1->GetMass()) + 
					2 * F1->GetMass() * F1->GetVelocity() / (F1->GetMass() + zombie[i].GetMass());

				F1->SetVelocity(-f1FVelocity);
				zombie[i].SetVelocity(zombieFVelocity);
				zombie[i].DecreaseHP(1);
				scoreBoard->IncreaseScore(10);
			}
		}
		// Update zombie
		zombie[i].Update();
	}
	// Update F1
	F1->Update();

	if (scoreBoard->GetScore() >= 40)
	{	
		if (retryButton->RectColDetection(retryButton->GetColRectangle(), F1->GetColRectangle()))
		{
			retryButton->SetColorFilter(D3DCOLOR_XRGB(255, 0, 0));
		}
		else {
			retryButton->SetColorFilter(D3DCOLOR_XRGB(255, 255, 255));
		}
	}
	inputManager->SetAllKeyPressToFalse();
}

void Level1::Render(LPD3DXSPRITE spriteBrush)
{	
	D3DXMATRIX mat;

	// Draw background
	background->RenderSprite(spriteBrush, &mat);

	// Render Retry Button when the score is equal than 40
	if (scoreBoard->GetScore() >= 40)
	{
		retryButton->RenderSprite(spriteBrush, &mat);
		if (retryButton->RectColDetection(retryButton->GetColRectangle(), F1->GetColRectangle()))
		{
			eKey->RenderSprite(spriteBrush, &mat);
		}
	}

	// Draw F1
	F1->RenderSprite(spriteBrush, &mat);


	// Draw Text
	// .c_str() is to change the score from string to LPCSTR
	text->RenderText(spriteBrush, &mat, scoreBoard->DisplayScore().c_str());

	for (int i = 0; i < spawnNum; i++)
	{	
		// Only Draw Zombie when the zombie hp is higher than 0
		if (zombie[i].GetHP() > 0)
		{
			zombie[i].RenderSprite(spriteBrush, &mat);
		}
	}
}

void Level1::RenderLine()
{
	// Draw Box
	box->RenderLine(D3DCOLOR_XRGB(255, 0, 0));
}

void Level1::CleanUpLevel()
{	
	F1->CleanUpSprite();
	F1 = NULL;

	for (int i = 0; i < spawnNum; i++)
	{
		zombie[i].CleanUpSprite();
	}
	
	retryButton->CleanUpSprite();
	retryButton = NULL;
	eKey->CleanUpSprite();
	eKey = NULL;
	background->CleanUpSprite();
	background = NULL;
	box->CleanUpLine();
	box = NULL;
	text->CleanUpText();
	text = NULL;
}

