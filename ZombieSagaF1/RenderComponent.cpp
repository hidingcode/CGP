#include "RenderComponent.h"

RenderComponent::RenderComponent()
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::InitSprite(D3DXVECTOR2 scalingCentre, float scalingRotation, D3DXVECTOR2 scaling, 
	D3DXVECTOR2 rotationCentre, float rotation, D3DXVECTOR2 position, D3DXCOLOR colorFilter)
{	
	//this->rect.top = rectTop;
	//this->rect.bottom = rectBtm;
	//this->rect.left = rectLeft;
	//this->rect.right = rectRight;
	this->scalingCentre = scalingCentre;
	this->scalingRotation = scalingRotation;
	this->scaling = scaling;
	this->rotationCentre = rotationCentre;
	this->rotation = rotation;
	this->position = position;
	this->colorFilter = colorFilter;
}

void RenderComponent::InitText(D3DXVECTOR2 scalingCentre, float scalingRotation, D3DXVECTOR2 scaling,
	D3DXVECTOR2 rotationCentre, float rotation, D3DXVECTOR2 position,
	int textLength, UINT format, D3DXCOLOR colorFilter)
{
	this->scalingCentre = scalingCentre;
	this->scalingRotation = scalingRotation;
	this->scaling = scaling;
	this->rotationCentre = rotationCentre;
	this->rotation = rotation;
	this->position = position;
	this->textLength = textLength;
	this->format = format;
	this->colorFilter = colorFilter;
}


void RenderComponent::CreateTexture(IDirect3DDevice9* d3dDevice, LPCSTR textureFilePath)
{
	// Create texture from file
	HRESULT hr = D3DXCreateTextureFromFile(d3dDevice, textureFilePath, &texture);

	if (FAILED(hr)) {
		cout << "Create background texture failed" << endl;
	}
}

void RenderComponent::CreateFontType(IDirect3DDevice9* d3dDevice, LPCSTR fontType)
{
	HRESULT hr = D3DXCreateFont(d3dDevice, 25, 0, 0, 1, false, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, fontType, &font);

	if (FAILED(hr)) {
		cout << "Create font failed" << endl;
	}
}

void RenderComponent::RenderSprite(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat)
{
	// Change the position when the scaling change
	D3DXMatrixTransformation2D(mat, &scalingCentre, scalingRotation, &scaling, &rotationCentre, rotation, &position);

	// Set the transformation
	spriteBrush->SetTransform(mat);

	// Draw the sprite
	HRESULT hr = spriteBrush->Draw(texture, &rect, NULL, NULL, colorFilter);
	if (FAILED(hr)) {
		cout << "Draw sprite failed" << endl;
	}
}

void RenderComponent::RenderText(LPD3DXSPRITE spriteBrush, D3DXMATRIX* mat, LPCSTR textContent)
{
	D3DXMatrixTransformation2D(mat, &scalingCentre, scalingRotation, &scaling, &rotationCentre, rotation, &position);
	spriteBrush->SetTransform(mat);
	HRESULT hr = font->DrawText(spriteBrush, textContent, textLength, &rect, format, colorFilter);
	if (FAILED(hr)) {
		cout << "Draw Text failed" << endl;
	}
}

void RenderComponent::CleanUpSprite()
{
	texture->Release();
	texture = NULL;
}

void RenderComponent::CleanUpText()
{
	font->Release();
	font = NULL;
}

D3DXVECTOR2 RenderComponent::GetPosition()
{
	return position;
}

D3DXVECTOR2 RenderComponent::GetScaling()
{
	return scaling;
}

D3DXVECTOR2 RenderComponent::GetScalingCentre()
{
	return scalingCentre;
}

D3DXVECTOR2 RenderComponent::GetRotationCentre()
{
	return rotationCentre;
}
