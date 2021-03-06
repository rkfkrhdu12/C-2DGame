#include <Windows.h>

#include <d3dx9.h>
#include "Sprite.h"
#include "GameTimer.h"

// GameGraphicSprite https://opengameart.org/
// json Data Converter https://shancarter.github.io/mr-data-converter/
// 윈도우 프로시저 함수 : 윈도우로 부터 받은 이벤트를 처리하는 함수 (내가 처리한다)
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
		} // ESC키 입력시 윈도우 파괴요구
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(
	HINSTANCE hInstance,		// 현재 응용 프로그램의 메인 핸들
	HINSTANCE hPrevInstance,	// 안쓰임
	PSTR pCmdLine,				// 실행하는데 쓰이는 명령줄 또는 인수
	int nCmdShow)				// 응용프로그램 표시 방식. 최소화/최대화 해서 보여줄거냐 결정
{
	int width;
	int height;
	bool isWindow = true; // WndStyle, D3DFORMAT


	if (isWindow) { width = 1280; height = 768; }
	else { width = 1920; height = 1080; }

	// 윈도우 스타일을 만들고 윈도우 스타일 등록
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	// 윈도우 프로시저 함수 등록
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = L"2DTileFrameWnd";			// 이 윈도우 스타일의 이름
	if (FALSE == RegisterClass(&wc)) { return 0; }


	// isWindow == true 윈도우의 부가적인 요소를 제거
	DWORD style;
	if (isWindow) { style = WS_OVERLAPPEDWINDOW; }
	else { style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP; }


	// 창 핸들(아이디)를 먼저 발급을 받자
	HWND hWnd;
	hWnd = CreateWindow(
		L"2DTileFrameWnd",				// 사용할 윈도우 스타일 이름. OS에 등록 되어있음.
		L"2D Tile Frame",
		style,							// 윈도우 스타일 
		CW_USEDEFAULT, CW_USEDEFAULT,	// 시작위치 :  x, y
		width, height,					// 해상도. 너비/높이
		0,								// 부모 창의 핸들. 사용 안함
		0,								// 메뉴 핸들. 사용 안함
		hInstance,						// OS와 윈도우 연결. OS에서 윈도우를 관리할 수 있다.
		0);
	if (NULL == hWnd) { return 0; }

	// hWnd : 하나의 윈도우를 가리키는 핸들(아이디)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 실제 게임 영역 확보 
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

	// 누군가  한테 하드웨어 접근 가능한 무언가 생성 요청
	// DirectX 한테          dxDevice			생성 요청

	// 그래픽을 담당하는 direct
	IDirect3D9* direct3d;//
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (NULL == direct3d) { return 0; }

	D3DFORMAT format;
	if (isWindow) { format = D3DFMT_UNKNOWN; } // 색상을 윈도우로 지정
	else { format = D3DFMT_X8R8G8B8; } // 전용 색상 포맷을 사용

	//Device를 생성하기전
	//Device를 통해 화면을 어떻게 보여질지를 결정
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));	// 메모리를 전부 0으로 초기화
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = format;
	d3dpp.BackBufferCount = 1;			// 버퍼 갯수 
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = isWindow;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Device 생성 요청
	IDirect3DDevice9* dxDevice;
	HRESULT hr = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,						 // GPU에 접근
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, // GPU에 접근
		&d3dpp,
		&dxDevice);
	if (FAILED(hr)) { return 0; }

	// Sprite COM 인터페이스 생성

	ID3DXSprite* spriteDX;
	hr = D3DXCreateSprite(dxDevice, &spriteDX);
	if (FAILED(hr)) { return 0; }

	// 이미지 로드
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
		// 메세지가 있으면 메세지 처리 없으면 게임업데이트
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) // msg에 메세지가 있으면 true 없으면 false
		{
			TranslateMessage(&msg);		// 키보드 변환 수행
			DispatchMessage(&msg);		// 메시지 창에 배분을 요청한다.
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

				// 매 프레임마다 화면의 색을 채운다.
				dxDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);

				// BeginScene :  Scene 작업공간
				dxDevice->BeginScene();

				// Scene 작업 : 게임 화면과 관련된 모든 작업 공간
				spriteDX->Begin(D3DXSPRITE_ALPHABLEND);

				// 스프라이트 렌더
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
					// 디바이스 상태 확인
					hr = dxDevice->TestCooperativeLevel();
					if (FAILED(hr))	// 디바이스 상태에 문제확인
					{
						// 문제 종류 확인  세 종류 (고칠수없는상태, 고칠수있는상태, 고쳐진상태)
						// 고칠수없는상태  고칠수있는 상태가 될때까지 대기(IDLE)
						if (D3DERR_DEVICELOST == hr) { Sleep(100); }
						// 고칠수있는상태  복구 시작
						else if (D3DERR_DEVICENOTRESET == hr)
						{
							// 디바이스와 그 외 디바이스를 통해 생성된 모든 리소스를 복구 (spriteDX, textureDX)
							// 기존에 만들어진 것들을 모두 리셋

							sprite->Release();

							// 새로 생성
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

				// 채운 색을 모니터를 통해 보여준다.
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

	// 텍스쳐 해제는 스프라이트가 파괴될때
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