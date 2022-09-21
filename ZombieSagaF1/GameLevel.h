#pragma once
#include "MyWindowManager.h"
#include "InputManager.h"
#include "AudioManager.h"

class GameLevel
{
public:
	virtual void InitLevel();
	virtual void Update(int framesToUpdate, InputManager* inputManager, AudioManager* audioManager);
	virtual void Render();
	void CleanUpLevel();
};

