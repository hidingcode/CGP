#include "MainMenu.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::InitLevel(IDirect3DDevice9* d3dDevice)
{	
	menuBG->CreateTexture(d3dDevice, "Assets/Textures/mainMenu.png");
	menuBG->Init(840, 650, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(1, 1),
		D3DCOLOR_XRGB(255, 255, 255));

	instruction->CreateFontType(d3dDevice, "Arial");
	instruction->Init(800, 200, D3DXVECTOR2(1, 1), 0.0f, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 0), 0.0f,
		D3DXVECTOR2(0, 0), -1, 0, D3DCOLOR_XRGB(255, 255, 255));

	startButton->CreateTexture(d3dDevice, "Assets/Textures/startButton.png");
	startButton->Init(210, 75, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(310, 300), 0.0f,
		D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(255, 255, 255));

	quitButton->CreateTexture(d3dDevice, "Assets/Textures/quitButton.png");
	quitButton->Init(165, 70, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(310, 450),
		0.0f, D3DXVECTOR2(1, 1), D3DCOLOR_XRGB(255, 255, 255));

	eKey->CreateTexture(d3dDevice, "Assets/Textures/e-key.png");
	eKey->Init(215, 220, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(550, 330), 0.0f, D3DXVECTOR2(0.18, 0.18),
		D3DCOLOR_XRGB(255, 255, 255));

	F1->CreateTexture(d3dDevice, "Assets/Textures/F1.png");
	F1->Init(768, 450, 3, 6, 5, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(600, 400), 1.0f, 0.0f, 2.0f,
		D3DXVECTOR2(0.4f, 0.4f), 0.05f, 0.05f, D3DCOLOR_XRGB(255, 255, 255));
}

void MainMenu::Update(IDirect3DDevice9* d3dDevice)
{	
	audioManager->UpdateSound();
	audioManager->ManageCarEngineSound(inputManager->GetKeyPress(DIK_W), inputManager->GetKeyPress(DIK_S));
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
	F1->Update();

	// User Interface
	if (quitButton->RectColDetection(quitButton->GetColRectangle(), F1->GetColRectangle()))
	{
		quitButton->SetColorFilter(D3DCOLOR_XRGB(255, 0, 0));
		if (inputManager->GetKeyPress(DIK_E))
		{
			// Quit the game
			exit(0);
		}	
	}
	else
	{
		quitButton->SetColorFilter(D3DCOLOR_XRGB(255, 255, 255));
	}

	if (startButton->RectColDetection(startButton->GetColRectangle(), F1->GetColRectangle()))
	{
		startButton->SetColorFilter(D3DCOLOR_XRGB(255, 0, 0));
		if (inputManager->GetKeyPress(DIK_E))
		{
			gameState.back()->CleanUpLevel();
			gameState.pop_back();
			gameState.push_back(new Level1());
			gameState.back()->InitLevel(d3dDevice);
		}
	}
	else {
		startButton->SetColorFilter(D3DCOLOR_XRGB(255, 255, 255));
	}

	inputManager->SetAllKeyPressToFalse();
}

void MainMenu::Render(LPD3DXSPRITE spriteBrush)
{	
	D3DXMATRIX mat;

	menuBG->RenderSprite(spriteBrush, &mat);
	instruction->RenderText(spriteBrush, &mat,
		"Move your car with W, A, S ,D to Start Button to start your game");
	startButton->RenderSprite(spriteBrush, &mat);
	quitButton->RenderSprite(spriteBrush, &mat);

	if (startButton->RectColDetection(startButton->GetColRectangle(), F1->GetColRectangle()))
	{	
		eKey->SetPosition(D3DXVECTOR2(550, startButton->GetPosition().y + 15));
		eKey->RenderSprite(spriteBrush, &mat);
	}
	else{
	}
	if (quitButton->RectColDetection(quitButton->GetColRectangle(), F1->GetColRectangle()))
	{	
		eKey->SetPosition(D3DXVECTOR2(550, quitButton->GetPosition().y + 15));
		eKey->RenderSprite(spriteBrush, &mat);
	}
	else{
	}
	// Draw F1
	F1->RenderSprite(spriteBrush, &mat);
}

void MainMenu::CleanUpLevel()
{	
	menuBG->CleanUpSprite();
	menuBG = NULL;

	instruction->CleanUpText();
	instruction = NULL;

	startButton->CleanUpSprite();
	startButton = NULL;

	quitButton->CleanUpSprite();
	quitButton = NULL;

	eKey->CleanUpSprite();
	eKey = NULL;

	F1->CleanUpSprite();
	F1 = NULL;
}


