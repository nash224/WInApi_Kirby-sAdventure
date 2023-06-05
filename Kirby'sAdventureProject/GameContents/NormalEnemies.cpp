#include "NormalEnemies.h"

#include <GameEngineCore/GameEngineRenderer.h>


NormalEnemies::NormalEnemies()
{
}

NormalEnemies::~NormalEnemies()
{
}


void NormalEnemies::init(const std::string _FileName, const float4& _Pos)
{
	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	SetPos(RespawnLocation);
	SetDirectionAndFirstAnimation();
}

void NormalEnemies::StateUpdate(float _Delta)
{
	switch (State)
	{
	case NormalState::Idle:					return IdleUpdate(_Delta);
	case NormalState::Walk:					return WalkUpdate(_Delta);
	case NormalState::Sit:					return SitUpdate(_Delta);
	case NormalState::Jump:					return JumpUpdate(_Delta);
	case NormalState::Sweep:				return SweepUpdate(_Delta);
	default:
		break;
	}
}

void NormalEnemies::ChangeState(NormalState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case NormalState::Idle:					IdleStart();					break;
		case NormalState::Walk:					WalkStart();					break;
		case NormalState::Sit:					SitStart();						break;
		case NormalState::Jump:					JumpStart();					break;
		case NormalState::Sweep:				SweepStart();					break;
		default:
			break;
		}
	}

	State = _State;
}

void NormalEnemies::ChangeAnimationState(const std::string& _StateName)
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