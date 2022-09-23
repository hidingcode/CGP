#ifndef CANVA_H
#define CANVA_H
#include "Image.h"
#include "VerticalPanel.h"
#include "Button.h"

class Canva: public Image
{
public:
	Canva();
	~Canva();

	void CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath);
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat);
	void OnCollide(RECT Colrect);

private:
	//VerticalPanel vPanel[];
	//Button button[];
	//D3DXVECTOR2(310, 300)
};
#endif

