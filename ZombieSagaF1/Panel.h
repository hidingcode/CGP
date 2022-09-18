#pragma once
#include <d3dx9.h>
#include "Button.h"

class Panel
{
public:
	Panel(D3DXVECTOR2 position);
	~Panel();
	void Begin();
private:
	D3DXVECTOR2 position = D3DXVECTOR2(0, 0);
};

