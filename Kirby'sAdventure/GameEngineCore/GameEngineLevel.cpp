#include "GameEngineLevel.h"

GameEngineLevel::GameEngineLevel() 
{
}

GameEngineLevel::~GameEngineLevel() 
{
}

void GameEngineLevel::ActorInit(GameEngineActor* _Actor)
{
	_Actor->Start();
}