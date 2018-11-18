#pragma once
#include <d3dx9.h>

class Frame
{
private:
	ID3DXSprite * _spriteDX;
	IDirect3DTexture9* _textureDX;

	RECT _textureRect;
	D3DCOLOR _textureColor;
	float _scale;

	float _frameInterval;
	float _width;
	float _height;

	float _x;
	float _y;
public:
	Frame();
	~Frame();

	void Init(ID3DXSprite*, IDirect3DTexture9*,
		int left, int top, int width, int height,
		float frameInterval, D3DCOLOR, float scale);
	void Reset();
	void Render();

	float GetInterval() { return _frameInterval; }

	void SetPosition(float, float);
};

