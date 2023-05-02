#include "GameEngineTime.h"
#include <Windows.h>

GameEngineTime GameEngineTime::MainTimer;
GameEngineTime::GameEngineTime() 
{
	QueryPerformanceCounter(&Count);
	QueryPerformanceFrequency(&Cur);
}

GameEngineTime::~GameEngineTime() 
{
}

