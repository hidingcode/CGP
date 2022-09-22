#ifndef MAINMENU_H
#define MAINMENU_H
#include "GameState.h"
#include "Player.h"
#include "UI.h"
#include "Text.h"

class MainMenu : public GameState
{
public:
	void InitLevel(IDirect3DDevice9* d3dDevice);
	void Update(int framesToUpdate, InputManager* inputManager, AudioManager* audioManager,
		vector<GameState*> gameLevel);
	void Render(LPD3DXSPRITE spriteBrush);
	void CleanUpLevel();

	static MainMenu* Instance() {
		return &mainMenuRef;
	}

protected:
	/*MainMenu();*/

private:
	static MainMenu mainMenuRef;

	Player* F1 = new Player();
	UI* ui = new UI();
	Text* instruction = new Text();
};
#endif