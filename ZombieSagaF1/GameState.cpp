#include "GameState.h"

GameState::~GameState()
{
}

void GameState::InitLevel(IDirect3DDevice9* d3dDevice, MyWindowManager* windowManager)
{
}

void GameState::Update(int framesToUpdate, InputManager* inputManager, AudioManager* audioManager,
	vector<GameState*> gameState, MyWindowManager* windowManager)
{
}

void GameState::Render(LPD3DXSPRITE spriteBrush)
{

}

void GameState::RenderLine()
{
}

void GameState::CleanUpLevel()
{

}

//int GameState::GetLevelState()
//{
//	return levelState;
//}
//
//void GameState::SetLevelState(int levelState)
//{
//	this->levelState = levelState;
//}

void GameState::ChangeState(GameStateManager* game, GameState* state, IDirect3DDevice9* d3dDevice)
{

}

GameState::GameState()
{
}
