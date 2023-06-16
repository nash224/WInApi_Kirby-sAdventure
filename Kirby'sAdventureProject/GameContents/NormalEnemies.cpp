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
	case NormalState::Sweep:				return SweepUpdate(_Delta);
	case NormalState::BeInhaled:			return BeInhaledUpdate(_Delta);
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
		case NormalState::Sweep:				SweepStart();					break;
		case NormalState::BeInhaled:			BeInhaledStart();				break;
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
	std::vector<GameEngineCollision*> InhaledCol;
	if (true == BodyCollision->Collision(CollisionOrder::KirbyInhaleAbility, InhaledCol, CollisionType::Rect, CollisionType::Rect))
	{
		if (true == IsInhaledStateOn)
		{
			IsInhaledStateOn = false;
			BodyCollision->Off();
			ChangeState(NormalState::BeInhaled);
			return;
		}
	}

	std::vector<GameEngineCollision*> AbilityCol;
	if (true == BodyCollision->Collision(CollisionOrder::PlayerAbility, AbilityCol, CollisionType::Rect, CollisionType::Rect))
	{
		/*ChangeState(HotHeadState::Hitted);*/
		return;
	}
}