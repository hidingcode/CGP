#pragma once
#include <d3dx9.h>
#include <iostream>

using namespace std;

class Text
{
public:
	// Constructor
	Text();
	// Destructor
	~Text();
	// Create Font Type
	void CreateFontType(IDirect3DDevice9* d3dDevice, LPCSTR fontType);
	// Initialise Text 
	void Init(int textRectLeft, int textRectTop, int textRectRight, int textRectBottom);
	//createDefaultText
	void DefaultText(string text);
	//Merge
	void MergedText();

	//Converter
	void IntConvertToString(int score);
	void StrConvertToLPCSTR();
	// Render Text
	void Render(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat, D3DXVECTOR2 scaling, D3DXVECTOR2 textCentre,
		D3DXVECTOR2 fontPosition, float rotation, LPCSTR text, D3DXCOLOR textColor);
	// Clean Up Text
	void CleanUp();
	//variables
	//default text like "score :"
	string text1;
	//number
	string text2;
	//mergedString
	string text3;
	//The final form of the texts (in LPCSTR form)
	LPCSTR text4;

private:
	LPD3DXFONT font = NULL;
	RECT textRect;
};

