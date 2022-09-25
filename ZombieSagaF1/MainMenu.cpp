#include "MainMenu.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::InitLevel(IDirect3DDevice9* d3dDevice)
{
	F1->CreateTexture(d3dDevice, "Assets/F1.png");
	F1->Init(768, 450, 3, 6, 5, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(600, 400), 1.0f, 0.0f, 2.0f,
		D3DXVECTOR2(0.4f, 0.4f), 0.05f, 0.05f, D3DCOLOR_XRGB(255, 255, 255));

	canva->CreateTexture(d3dDevice, "Assets/mainMenu.png");
	canva->Init(840, 650, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(1, 1),
		D3DCOLOR_XRGB(255, 255, 255));
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
	if (inputManager->GetKeyPress(DIK_O)) {

	}

	if (inputManager->GetKeyPress(DIK_P)) {
		cout << "P Pressed" << endl;
		gameState.pop_back();
		gameState.push_back(new Level1());
		gameState.back()->InitLevel(d3dDevice);
	}
	F1->Update();
	inputManager->SetAllKeyPressToFalse();

	// Check Collision
	canva->OnCollide(F1->GetColRectangle(), d3dDevice);
}

void MainMenu::Render(LPD3DXSPRITE spriteBrush)
{	
	D3DXMATRIX mat;
	canva->Render(spriteBrush, &mat);
	// Draw F1
	F1->RenderSprite(spriteBrush, &mat);
}

void MainMenu::CleanUpLevel()
{
	F1->CleanUpSprite();
	F1 = NULL;
	
	canva->CleanUpSprite();
	canva = NULL;
}


