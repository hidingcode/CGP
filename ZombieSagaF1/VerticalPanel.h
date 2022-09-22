#ifndef VERTICALPANEL_H
#define VERTICALPANEL_H
#include <d3dx9.h>
#include "Button.h"

class VerticalPanel
{
public:
	VerticalPanel(D3DXVECTOR2 position);
	~VerticalPanel();
	// Set the position of widget according to the panel position
	void Init();
	void CreateTexture(IDirect3DDevice9* d3dDevice);
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat);
	void OnCollide(RECT rect, D3DXVECTOR2 position);
private:
	D3DXVECTOR2 position = D3DXVECTOR2(0, 0);
	Button* startButton = new Button();
	Button* quitButton = new Button();
};
#endif

