
#ifndef CANVA_H
#define CANVA_H
#include "Image.h"
#include "Text.h"
#include "VerticalPanel.h"
#include <iostream>

using namespace std;

class Canva : public Image
{
public:
	Canva();
	~Canva();
	
	void CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath);
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat);
	void OnCollide(RECT Colrect);

private:
	Text* instruction1 = new Text();
	VerticalPanel* panel1 = new VerticalPanel(D3DXVECTOR2(310, 300));
};
#endif

