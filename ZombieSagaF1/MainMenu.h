#pragma once
#include "GameLevel.h"

class MainMenu :GameLevel
{
public:
	MainMenu();
	~MainMenu();

	void InitLevel();
	void Update(int framesToUpdate, InputManager inputManager, AudioManager audioManager);
	void Render();
};