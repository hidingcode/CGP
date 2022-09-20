#pragma once
#include "Image.h"
#include "Panel.h"
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
	Panel* panel1 = new Panel(D3DXVECTOR2(310, 300));
};

