#pragma once

#include <d3dx9.h>
#include <string>
#include <vector>

class Sprite;

class Map
{
	Sprite* _tileSprite[16][16];
	std::vector<Sprite*> _spriteList;

public:
	Map();
	~Map();

	void Init(LPDIRECT3DDEVICE9 dxDevice, ID3DXSprite* spriteDX);
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();
	void Deinit();
};
