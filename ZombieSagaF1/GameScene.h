#pragma once
#include <windows.h>

class GameScene
{
public: 
	enum GameMode
	{
		GM_MENU,GM_GAMEPLAY,
	};

	GameMode current_gamemode;
	int selector = 0;
};

