#include "NormalEnemies.h"
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


NormalEnemies::NormalEnemies()
{
}

NormalEnemies::~NormalEnemies()
{
}


void NormalEnemies::init(const std::string& _FileName, NormalState _State, const float4& _Pos)
{
	Attribute = AttributeType::None;
	Ability = AbilityStar::Normal;

	SetGroundTexture(_FileName);
	RespawnLocation = _Pos;
	RespawnState = _State;
	SetPos(RespawnLocation);
	ChangeState(_State);
	StringRespawnState = CurState;
}


/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */

void NormalEnemies::StateUpdate(float _Delta)
{
	switch (State)
	{
	case NormalState::Idle:					return IdleUpdate(_Delta);
	case NormalState::Walk:					return WalkUpdate(_Delta);
	case NormalState::Sit:					return SitUpdate(_Delta);
	case NormalState::Jump:					return JumpUpdate(_Delta);
	case NormalState::Fall:					return FallUpdate(_Delta);
	case NormalState::Bounce:				return BounceUpdate(_Delta);
	case NormalState::Roll:					return RollUpdate(_Delta);
	case NormalState::BounceMove:			return BounceMoveUpdate(_Delta);
	case NormalState::Sweep:				return SweepUpdate(_Delta);
	case NormalState::BeInhaled:			return BeInhaledUpdate(_Delta);
	case NormalState::Hitted:				return HittedUpdate(_Delta);
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
		case NormalState::Fall:					FallStart();					break;
		case NormalState::Bounce:				BounceStart();					break;
		case NormalState::Roll:					RollStart();					break;
		case NormalState::BounceMove:			BounceMoveStart();				break;
		case NormalState::Sweep:				SweepStart();					break;
		case NormalState::BeInhaled:			BeInhaledStart();				break;
		case NormalState::Hitted:				HittedStart();					break;
		default:
			break;
		}
	}

	State = _State;
}

void NormalEnemies::ChangeRespawnState()
{
	ChangeState(RespawnState);
}

/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void NormalEnemies::EnemyCollisionCheck()
{
	if (true == IsInhaledStateOn)
	{
		ChangeState(NormalState::BeInhaled);
		return;
	}

	if (true == IsHitted)
	{
		ChangeState(NormalState::Hitted);
		return;
	}
}