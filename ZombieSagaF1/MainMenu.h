#pragma once
#include "Image.h"
#include "VerticalPanel.h"
#include <iostream>

using namespace std;

class MainMenu : public Image
{
public:
	MainMenu();
	~MainMenu();
	
	void CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath);
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat);
	void OnCollide(RECT rect);

private:
	VerticalPanel* panel1 = new VerticalPanel(D3DXVECTOR2(310, 300));
};

