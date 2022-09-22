#pragma once
#include "Image.h"
#include "Text.h"
#include "VerticalPanel.h"
#include <iostream>

using namespace std;

class UI : public Image
{
public:
	UI();
	~UI();
	
	void CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath);
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat);
	void OnCollide(RECT Colrect);

private:
	Text* instruction = new Text();
	VerticalPanel* panel1 = new VerticalPanel(D3DXVECTOR2(310, 300));
};

