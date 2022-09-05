#pragma once
#include <d3dx9.h>

class Texture 
{
	public:
		Texture(int textureWidth, int textureHeight);
		void CreateGameTexture();
		
	private:
		LPDIRECT3DTEXTURE9 texture = NULL;
		int textureWidth;
		int textureHeight;
		int spriteWidth;
		int spriteHeight;
};