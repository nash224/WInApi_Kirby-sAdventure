#include "AerialEnemies.h"

#include <GameEngineCore/GameEngineRenderer.h>


AerialEnemies::AerialEnemies()
{
}

AerialEnemies::~AerialEnemies()
{
}


void AerialEnemies::init(const std::string _FileName, const float4& _Pos)
{
	Attribute = AttributeType::None;

	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	SetPos(RespawnLocation);
}


void AerialEnemies::ChangeAnimationState(const std::string& _StateName)
{

	std::string AnimationName = "";

	switch (Dir)
	{
	case ActorDir::Left:
		AnimationName = "Left_";
		break;
	case ActorDir::Right:
		AnimationName = "Right_";
		break;
	default:
		break;
	}

	AnimationName += _StateName;

	CurState = _StateName;

	MainRenderer->ChangeAnimation(AnimationName);
}