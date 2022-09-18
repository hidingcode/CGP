#pragma once
#include "GameState.h"
#include <iostream>
using namespace std;

class MainMenu:public GameState
{
	void GetInput();
	void Update(int framesToUpdate);
	void Render();
};

