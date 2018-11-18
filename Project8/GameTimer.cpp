#include "GameTimer.h"

#include <Windows.h>

GameTimer::GameTimer()
{
	__int64 countPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countPerSec);

	_secondsPerCount = 1.0f / (double)countPerSec;
}


GameTimer::~GameTimer()
{
}

void GameTimer::Init()
{
	__int64 curTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&curTime);

	_deltaTime = 0;
	_prevTime = curTime;
}

void GameTimer::Update()
{
	__int64 curTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&curTime);

	_deltaTime = (curTime - _prevTime) * _secondsPerCount;
	_prevTime = curTime;
}

float GameTimer::GetDelta()
{
	return _deltaTime;
}