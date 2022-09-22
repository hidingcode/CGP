#include "GameLevel.h"

void GameLevel::InitLevel(IDirect3DDevice9* d3dDevice)
{
}

void GameLevel::Update(int framesToUpdate, InputManager* inputManager, AudioManager* audioManager,
	vector<GameLevel*> gameLevel)
{
}

void GameLevel::Render(LPD3DXSPRITE spriteBrush)
{

}

void GameLevel::RenderLine()
{
}

void GameLevel::CleanUpLevel()
{

}

int GameLevel::GetLevelState()
{
	return levelState;
}

void GameLevel::SetLevelState(int levelState)
{
	this->levelState = levelState;
}
