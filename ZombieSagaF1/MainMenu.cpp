#include "MainMenu.h"
#define WindowWidth 840
#define WindowHeight 650

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

	ui->CreateTexture(d3dDevice, "Assets/mainMenu.png");
	ui->Init(840, 650, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(0, 0), 0.0f, D3DXVECTOR2(1, 1),
		D3DCOLOR_XRGB(255, 255, 255));
}

void MainMenu::Update(int framesToUpdate, InputManager* inputManager, AudioManager* audioManager)
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

		F1->Update(WindowWidth, WindowHeight);
		inputManager->SetAllKeyPressToFalse();

		ui->OnCollide(F1->GetRectangle(), F1->GetPosition());
	}
}

void MainMenu::Render(LPD3DXSPRITE spriteBrush)
{	
	D3DXMATRIX mat;
	ui->Render(spriteBrush, &mat);
	// Draw F1
	F1->RenderSprite(spriteBrush, &mat);
}


