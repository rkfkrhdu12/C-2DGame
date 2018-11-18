#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <string>
#include "Sprite.h"
#include "Map.h"

Map::Map()
{
}

Map::~Map()
{
}

void Map::Init(LPDIRECT3DDEVICE9 dxDevice, ID3DXSprite* spriteDX)
{
	// �ʿ� ��������Ʈ ����Ʈ �۾�.
	// Ÿ�� �����ϰ� ���� Ÿ�� ũ�� ���� �Ϸ� (32x32, 256)
	int srcX = 0;
	int srcY = 0;
	int tileSize = 32;
	LPCWSTR fileName = L"../Resources/Images/PathAndObjects.png";
	IDirect3DTexture9* textureDX;
	D3DXIMAGE_INFO texInfo;

	// ���Ϸ� ���� �̹����� �ʺ�� ���̸� ��´�
	HRESULT hr = D3DXGetImageInfoFromFile(fileName, &texInfo);
	if (FAILED(hr))
	{
		return;
	}

	// �̹�������Ÿ �ε�
	hr = D3DXCreateTextureFromFileEx(dxDevice,
		fileName,
		texInfo.Width, texInfo.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_ARGB(255, 255, 255, 255),
		&texInfo,
		NULL,
		&textureDX);
	if (FAILED(hr))
	{
		return;
	}


	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			Sprite* sprite = new Sprite();
			/*
			sprite->Init(fileName,
			srcX, srcY, tileSize, tileSize, 1.0f,
			dxDevice, spriteDX);
			
			sprite->Init(
				textureDX, texInfo,
				srcX, srcY, tileSize, tileSize, 1.0f,
				dxDevice, spriteDX);
			_spriteList.push_back(sprite);
			*/
			srcX += tileSize;
		}

		srcX = 0;
		srcY += tileSize;
	}

	// Map ����
	int tileMapIndex[16][16];
	// ��ũ��Ʈ ��ü
	/*
	int idx = 0;
	for (int y = 0; y < 16; y++)
	{
	for (int x = 0; x < 16; x++)
	{
	tileMapIndex[y][x] = idx++;
	}
	}
	*/
	{
		std::string fileName = "map.csv";
		std::vector<std::string> recordList;
		std::ifstream infile(fileName);
		if (true == infile.is_open())	// ������ ���������� ��������
		{
			char recordString[1000];
			while (false == infile.eof())	// ������ ���� �� ���� ��ȯ
			{
				// ���پ� �о ����Ʈ�� ����
				infile.getline(recordString, 1000);
				recordList.push_back(recordString);
			}
		}

		// ���ڵ带 ��ū���� �и��ؼ� ���ӿ� ����
		char record[1000];
		for (int y = 0; y < 16; y++)
		{
			// ���� record�� ����
			strcpy(record, recordList[y].c_str());
			char* token = strtok(record, ",");
			for (int x = 0; x < 16; x++)
			{
				int tileIndex = atoi(token);
				tileMapIndex[y][x] = tileIndex;
				token = strtok(NULL, ",");
			}
		}
	}

	// ��������Ʈ��  ����
	//LPCWSTR fileName = L"../Resources/Images/PathAndObjects.png";
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			int spriteIndex = tileMapIndex[y][x];
			_tileSprite[y][x] = _spriteList[spriteIndex];
		}
	}
}

void Map::Update(float deltaTime)
{
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			_tileSprite[y][x]->Update(deltaTime);
		}
	}
}

void Map::Render()
{
	float startX = 0.0f;
	float startY = 0.0f;
	float posX = startX;
	float posY = startY;
	int tileSize = 32;
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			_tileSprite[y][x]->SetPosition(posX + 30, posY + 30);
			_tileSprite[y][x]->Render();
			posX += (tileSize);
		}
		posX = startX;
		posY += (tileSize);
	}
}

void Map::Release()
{
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			_tileSprite[y][x]->Release();
		}
	}
}

void Map::Reset()
{
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			_tileSprite[y][x]->Reset();
		}
	}
}

void Map::Deinit()
{
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			if (NULL != _tileSprite[y][x])
			{
				delete _tileSprite[y][x];
			}
		}
	}
}
