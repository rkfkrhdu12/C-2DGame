#include <Windows.h>

#include <d3dx9.h>
#include "Sprite.h"
#include "GameTimer.h"

// GameGraphicSprite https://opengameart.org/
// json Data Converter https://shancarter.github.io/mr-data-converter/
// ������ ���ν��� �Լ� : ������� ���� ���� �̺�Ʈ�� ó���ϴ� �Լ� (���� ó���Ѵ�)
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		DestroyWindow(hWnd);
		return 0;
	case WM_KEYDOWN:
		if (VK_ESCAPE == wParam)
		{
			DestroyWindow(hWnd);
		} // ESCŰ �Է½� ������ �ı��䱸
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(
	HINSTANCE hInstance,		// ���� ���� ���α׷��� ���� �ڵ�
	HINSTANCE hPrevInstance,	// �Ⱦ���
	PSTR pCmdLine,				// �����ϴµ� ���̴� ������ �Ǵ� �μ�
	int nCmdShow)				// �������α׷� ǥ�� ���. �ּ�ȭ/�ִ�ȭ �ؼ� �����ٰų� ����
{
	int width;
	int height;
	bool isWindow = true; // WndStyle, D3DFORMAT


	if (isWindow) { width = 1280; height = 768; }
	else { width = 1920; height = 1080; }

	// ������ ��Ÿ���� ����� ������ ��Ÿ�� ���
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	// ������ ���ν��� �Լ� ���
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"2DTileFrameWnd";			// �� ������ ��Ÿ���� �̸�
	if (FALSE == RegisterClass(&wc)) { return 0; }


	// isWindow == true �������� �ΰ����� ��Ҹ� ����
	DWORD style;
	if (isWindow) { style = WS_OVERLAPPEDWINDOW; }
	else { style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP; }


	// â �ڵ�(���̵�)�� ���� �߱��� ����
	HWND hWnd;
	hWnd = CreateWindow(
		L"2DTileFrameWnd",				// ����� ������ ��Ÿ�� �̸�. OS�� ��� �Ǿ�����.
		L"2D Tile Frame",
		style,							// ������ ��Ÿ�� 
		CW_USEDEFAULT, CW_USEDEFAULT,	// ������ġ :  x, y
		width, height,					// �ػ�. �ʺ�/����
		0,								// �θ� â�� �ڵ�. ��� ����
		0,								// �޴� �ڵ�. ��� ����
		hInstance,						// OS�� ������ ����. OS���� �����츦 ������ �� �ִ�.
		0);
	if (NULL == hWnd) { return 0; }

	// hWnd : �ϳ��� �����츦 ����Ű�� �ڵ�(���̵�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���� ���� ���� Ȯ�� 
	if (isWindow)
	{
		RECT clientRect;
		GetClientRect(hWnd, &clientRect);
		MoveWindow(hWnd, 0, 0,
			width + (width - clientRect.right), // 1280 1264 
			height + (height - clientRect.bottom), // 768 729
			TRUE);
	}

	// DirectX

	// ������  ���� �ϵ���� ���� ������ ���� ���� ��û
	// DirectX ����          dxDevice			���� ��û

	// �׷����� ����ϴ� direct
	IDirect3D9* direct3d;//
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == direct3d) { return 0; }

	D3DFORMAT format;
	if (isWindow) { format = D3DFMT_UNKNOWN; } // ������ ������� ����
	else { format = D3DFMT_X8R8G8B8; } // ���� ���� ������ ���

	//Device�� �����ϱ���
	//Device�� ���� ȭ���� ��� ���������� ����
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));	// �޸𸮸� ���� 0���� �ʱ�ȭ
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = format;
	d3dpp.BackBufferCount = 1;			// ���� ���� 
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = isWindow;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Device ���� ��û
	IDirect3DDevice9* dxDevice;
	HRESULT hr = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,						 // GPU�� ����
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, // GPU�� ����
		&d3dpp,
		&dxDevice);
	if (FAILED(hr)) { return 0; }

	// Sprite COM �������̽� ����

	ID3DXSprite* spriteDX;
	hr = D3DXCreateSprite(dxDevice, &spriteDX);
	if (FAILED(hr)) { return 0; }

	// �̹��� �ε�
	int tileMapIndex[16][16];
	int idx = 0;
	for (int y = 0; y < 16; y++)
	{

	}
	// Sprite
	Sprite* sprite = new Sprite();
	sprite->Init(dxDevice, fileName, spriteDX);

	float fps = 60.0f;
	float frameInterval = 1.0f / fps;
	float frameTime = 0.0f;
	float deltaTime = 0.0f;

	GameTimer gameTimer;
	gameTimer.Init();

	// Update
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		// �޼����� ������ �޼��� ó�� ������ ���Ӿ�����Ʈ
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) // msg�� �޼����� ������ true ������ false
		{
			TranslateMessage(&msg);		// Ű���� ��ȯ ����
			DispatchMessage(&msg);		// �޽��� â�� ����� ��û�Ѵ�.
		}
		else
		{
			gameTimer.Update();
			deltaTime = gameTimer.GetDelta();

			sprite->Update(deltaTime);

			frameTime = frameTime + deltaTime;
			if (frameInterval <= frameTime)
			{
				frameTime = 0.0f;

				// �� �����Ӹ��� ȭ���� ���� ä���.
				dxDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);

				// BeginScene :  Scene �۾�����
				dxDevice->BeginScene();

				// Scene �۾� : ���� ȭ��� ���õ� ��� �۾� ����
				spriteDX->Begin(D3DXSPRITE_ALPHABLEND);

				// ��������Ʈ ����
				float startX = 0.0f;
				float startY = 0.0f;
				float posX = startX;
				float posY = startY;
				int tileSize = 32;
				for (int y = 0; y < 16; y++)
				{
					for (int x = 0; x < 16; x++)
					{
						sprite->SetPosition(posX, posY);
						sprite->Render();
						posX += tileSize;
					}
					posX = startX;
					posY += tileSize;
					
				}

				spriteDX->End();

				// LostDevice Reset
				{
					// ����̽� ���� Ȯ��
					hr = dxDevice->TestCooperativeLevel();
					if (FAILED(hr))	// ����̽� ���¿� ����Ȯ��
					{
						// ���� ���� Ȯ��  �� ���� (��ĥ�����»���, ��ĥ���ִ»���, ����������)
						// ��ĥ�����»���  ��ĥ���ִ� ���°� �ɶ����� ���(IDLE)
						if (D3DERR_DEVICELOST == hr) { Sleep(100); }
						// ��ĥ���ִ»���  ���� ����
						else if (D3DERR_DEVICENOTRESET == hr)
						{
							// ����̽��� �� �� ����̽��� ���� ������ ��� ���ҽ��� ���� (spriteDX, textureDX)
							// ������ ������� �͵��� ��� ����

							sprite->Release();

							// ���� ����
							direct3d = Direct3DCreate9(D3D_SDK_VERSION);
							if (0 != direct3d)
							{
								hr = direct3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &dxDevice);
								if (SUCCEEDED(hr))
								{
									hr = D3DXCreateSprite(dxDevice, &spriteDX);
									if (SUCCEEDED(hr))
									{
										sprite->Reset();
									}
								}
							}
						}
					}
				} // lostDevice

				dxDevice->EndScene();

				// ä�� ���� ����͸� ���� �����ش�.
				dxDevice->Present(NULL, NULL, NULL, NULL);
			}
		}
	}

	if (dxDevice)
	{
		dxDevice->Release();
		dxDevice = NULL;
	}

	if (direct3d)
	{
		direct3d->Release();
		direct3d = NULL;
	}

	// �ؽ��� ������ ��������Ʈ�� �ı��ɶ�
	/*if (textureDX)
	{
	textureDX->Release();
	textureDX = 0;
	}*/

	if (sprite)
	{
		delete sprite;
	}

	return 0;
}