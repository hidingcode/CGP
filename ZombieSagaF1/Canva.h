#ifndef CANVA_H
#define CANVA_H
#include "Image.h"
#include "VerticalPanel.h"
#include "Button.h"
#include "Text.h"
#include <vector>
using namespace std;

// Testing stuff
class Canva: public Image
{
public:
	Canva();
	~Canva();

	void CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath);
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat);
	void OnCollide(RECT Colrect);
	void AddNewText(Text text);
	void AddNewVPanel(VerticalPanel vPanel);
	void AddNewButton(Button button);
private:
	vector<Text*> textList;
	vector<VerticalPanel*> vPanelList;
	vector<Button*> buttonList;
};
#endif

