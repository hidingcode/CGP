#pragma once
#include <d3dx9.h>

class Texture 
{
	public:
		void CreateGameTexture();
		
	private:
		LPDIRECT3DTEXTURE9 Texture = NULL;
		int textureWidth;
		int textureHeight;
		int spriteWidth;
		int spriteHeight;
};