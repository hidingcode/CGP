#include "Level1.h"
#define WindowWidth 840
#define WindowHeight 650

Level1::Level1()
{
}

Level1::~Level1()
{
}

bool Level1::CircleCollisionDetection(int radiusA, int radiusB, D3DXVECTOR2 positionA, D3DXVECTOR2 positionB)
{
	D3DXVECTOR2 distance = positionA - positionB;
	if (radiusA + radiusB < D3DXVec2Length(&distance))
	{
		return false;
	}
	else
	{
		return true;
	}
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

	box->CreateLine(d3dDevice);
	box->Init(120, 30, D3DXVECTOR2(10, 10));

	text->CreateFontType(d3dDevice, "Arial");
	text->Init(200, 200, D3DXVECTOR2(1, 1), 0.0f, D3DXVECTOR2(1, 1), text->GetPosition(), 0.0f,
		box->GetBoxPosition(), -1, 0, D3DCOLOR_XRGB(0, 0, 0));

}

void Level1::Update(int framesToUpdate, InputManager* inputManager, AudioManager* audioManager,
	vector<GameLevel*> gameLevel)
{	
	audioManager->UpdateSound();
	audioManager->ManageCarEngineSound(inputManager->GetKeyPress(DIK_W), inputManager->GetKeyPress(DIK_S));
	audioManager->DynamicCarEngineSound(WindowWidth, F1->GetPosition().x);

	for (int i = 0; i < framesToUpdate; i++) {
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
			gameLevel.front()->SetLevelState(2);
		}
		if (inputManager->GetKeyPress(DIK_U)) {
			gameLevel.front()->SetLevelState(4);
		}

		for (int i = 0; i < spawnNum; i++)
		{
			if (zombie[i].GetHP() > 0)
			{
				if (CircleCollisionDetection(F1->GetSpriteWidth() / 2, zombie[i].GetSpriteWidth() / 2, F1->GetPosition() /* + F1->GetSpriteCentre()*/, zombie[i].GetPosition()/* + zombie[i].GetSpriteCentre()*/))
				{
					cout << "Collision occurs" << endl;
					audioManager->PlayCollisionSound();

					// Calculate the bouncing vector of zombie after collision
					D3DXVECTOR2 f1FVelocity = F1->GetVelocity() * (F1->GetMass() - zombie[i].GetMass()) + 2 * zombie[i].GetMass() * zombie[i].GetVelocity() / (F1->GetMass() + zombie[i].GetMass());

					// Calculate the bouncing vector of zombie after collision
					D3DXVECTOR2 zombieFVelocity = zombie[i].GetVelocity() * (zombie[i].GetMass() - F1->GetMass()) + 2 * F1->GetMass() * F1->GetVelocity() / (F1->GetMass() + zombie[i].GetMass());

					F1->SetVelocity(-f1FVelocity);
					zombie[i].SetVelocity(zombieFVelocity);
					zombie[i].DecreaseHP(1);
					scoreBoard->IncreaseScore(10);
				}
			}
			zombie[i].Update(WindowWidth, WindowHeight);
		}
		F1->Update(WindowWidth, WindowHeight);

		if (scoreBoard->GetScore() == 100)
		{
			gameLevel.front()->SetLevelState(2);
		}
	}
	inputManager->SetAllKeyPressToFalse();
}

void Level1::Render(LPD3DXSPRITE spriteBrush)
{	
	D3DXMATRIX mat;

	// Draw background
	background->RenderSprite(spriteBrush, &mat);

	// Draw F1
	F1->RenderSprite(spriteBrush, &mat);

	// Draw Text
	// .c_str() is to change the score to LPCSTR
	text->RenderText(spriteBrush, &mat, scoreBoard->DisplayScore().c_str());

	// Draw Zombie
	for (int i = 0; i < spawnNum; i++)
	{
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
	
	background->CleanUpSprite();
	background = NULL;
	box->CleanUpLine();
	box = NULL;
	text->CleanUpText();
	text = NULL;
}

