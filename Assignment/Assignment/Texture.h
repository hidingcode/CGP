#pragma once
#include <d3dx9.h>

class Texture 
{
	public:
		void CreateTexture();
		
	private:
		LPDIRECT3DTEXTURE9 playerTexture = NULL;
		int textureWidth;
		int textureHeight;
		int spriteWidth;
		int spriteHeight;
};