#include "AerialEnemies.h"

#include <GameEngineCore/GameEngineRenderer.h>


AerialEnemies::AerialEnemies()
{
}

AerialEnemies::~AerialEnemies()
{
}


void AerialEnemies::init(const std::string& _FileName, const float4& _Pos)
{
	Attribute = AttributeType::None;

	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	SetPos(RespawnLocation);
}