#pragma once
#include <windows.h>

class GameScene
{
public:
	enum GameMode { GM_MENU, GM_GAMEPLAY, GM_GAMEOVER };

	GameMode current_gamemode;
};

