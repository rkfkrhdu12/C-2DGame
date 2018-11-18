#include "Sprite.h"

#include "Frame.h"
#include <json.h>
#include <fstream>
#include <string>

#define WALK1 0
#define IDLE 1
#define WALK2 2

#define Character0 0
#define Character1 3
#define Character2 6
#define Character3 9

Sprite::Sprite()
{
	_isClassDown = false;
}


Sprite::~Sprite()
{
	for (int i = 0; i < _frameList.size(); i++)
	{
		delete _frameList[i];
	}
	_frameList.clear();

	if (_textureDX)
	{
		_textureDX->Release();
		_textureDX = NULL;
	}
}

void Sprite::Init
(IDirect3DDevice9* dxDevice, std::wstring fileName, ID3DXSprite* spriteDX)
{
	_fileName = fileName;
	_dxDevice = dxDevice;
	_spriteDX = spriteDX;

	HRESULT hr = D3DXGetImageInfoFromFile(_fileName.c_str(), &_texInfo);
	if (FAILED(hr)) { _isClassDown = true; }

	//  이미지 데이터 로드
	hr = D3DXCreateTextureFromFileEx(
		_dxDevice, _fileName.c_str(),
		_texInfo.Width, _texInfo.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_ARGB(255, 255, 255, 255),
		&_texInfo,
		NULL,
		&_textureDX);
	if (FAILED(hr)) { _isClassDown = true; }

	_frameIdx = 0;
	_frameTime = 0;

	std::ifstream infile("Test.json");
	if (infile.is_open())
	{
		char recordString[1000];
		while (!infile.eof())
		{
			infile.getline(recordString, 1000);

			Json::Value root;
			Json::Reader reader;
			bool isSuccess = reader.parse(recordString, root);
			if (isSuccess)
			{
				int x = root["x"].asInt();
				int y = root["y"].asInt();
				int width = root["width"].asInt();
				int height = root["height"].asInt();
				float frameInterval = root["frameInterval"].asDouble();
			
				Frame* frame = new Frame();
				frame->Init(_spriteDX, _textureDX, x, y, width, height, frameInterval, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f);
				_frameList.push_back(frame);
			}
		}
	}
}
void Sprite::Update(float deltaTime)
{
	_frameTime += deltaTime;
	float interval = _frameList[_frameIdx]->GetInterval();
	if (interval < _frameTime)
	{
		_frameTime = 0;
		_frameIdx++;
		if (_frameList.size() <= _frameIdx)
		{
			_frameIdx = 0;
		}
	}
}

void Sprite::Release()
{
	for (int i = 0; i < _frameList.size(); i++)
	{
		delete _frameList[i];
	}
	_frameList.clear();


	if (_textureDX)
	{
		_textureDX->Release();
		_textureDX = 0;
	}
}

void Sprite::Reset()
{
	HRESULT hr = D3DXCreateTextureFromFileEx(
		_dxDevice, _fileName.c_str(),
		_texInfo.Width, _texInfo.Height,
		1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_DEFAULT,
		D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_ARGB(255, 255, 255, 255),
		&_texInfo, 0, &_textureDX);
}

void Sprite::Render()
{
	if (_frameIdx < _frameList.size())
	{
		_frameList[_frameIdx]->SetPosition(_x, _y);
		_frameList[_frameIdx]->Render();
	}
}

void Sprite::SetPosition(float x, float y)
{
	_x = x;
	_y = y;
}