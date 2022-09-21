#pragma once
#include "GameLevel.h"

class MainMenu : public GameLevel
{
public:
	MainMenu();
	~MainMenu();

	void InitLevel();
	void Update(int framesToUpdate, InputManager inputManager, AudioManager audioManager);
	void Render();
};