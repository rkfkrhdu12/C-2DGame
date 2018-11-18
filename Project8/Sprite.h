#pragma once
#include <d3dx9.h>
#include <string>
#include <vector>

class Frame;

class Sprite
{
private:

	std::wstring _fileName;

	D3DXIMAGE_INFO _texInfo;

	ID3DXSprite* _spriteDX;
	IDirect3DTexture9* _textureDX;
	IDirect3DDevice9* _dxDevice;

	std::vector<Frame*> _frameList;
	int _frameIdx;
	float _frameTime;

	float _x;
	float _y;

	bool _isClassDown;
public:
	Sprite();
	~Sprite();

	void Init(IDirect3DDevice9*, std::wstring, ID3DXSprite*);
	void Release();
	void Reset();
	void Update(float);

	void Render();

	void SetPosition(float, float);
};

