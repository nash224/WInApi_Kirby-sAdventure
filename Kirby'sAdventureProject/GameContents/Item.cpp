#include "Item.h"
#include "ContentsEnum.h"


#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/ResourcesManager.h>


#include "Kirby.h"


Item::Item() 
{
}

Item::~Item() 
{
}



void Item::SetGroundTexture(const std::string& _GroundTextureName)
{
	GroundTexture = ResourcesManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTexture)
	{
		MsgBoxAssert(" 픽셀충돌 맵을 찾을 수 없습니다. " + _GroundTextureName);
		return;
	}
}




void Item::StateUpdate(float _Delta)
{
	switch (State)
	{
	case ItemState::Idle:					return IdleUpdate(_Delta);
	case ItemState::BounceOff:				return BounceOffUpdate(_Delta);
	case ItemState::BeInhaled:				return BeInhaledUpdate(_Delta);
	default:
		break;
	}
}

void Item::ChangeState(ItemState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case ItemState::Idle:					IdleStart();					break;
		case ItemState::BounceOff:				BounceOffStart();				break;
		case ItemState::BeInhaled:				BeInhaledStart();				break;
		default:
			break;
		}
	}

	State = _State;
}



// 상태 패턴
void Item::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = GetName();
	CurState = _StateName;
	AnimationName += "_";
	AnimationName += _StateName;
	MainRenderer->ChangeAnimation(AnimationName);
}



// 아이템와 커비 사이의 거리를 반환
float4 Item::GetKirbyOpponentDistance()
{
	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("커비를 불러오지 못했습니다.");
		return float4::ZERO;
	}

	float4 OpponentDistance = KirbyPtr->GetPos() - GetPos();
	return OpponentDistance;
}




void Item::ItemCollisionCheck()
{
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("충돌체가 Null 입니다.");
		return;
	}


	std::vector<GameEngineCollision*> ActorCol;
	if (true == BodyCollision->Collision(CollisionOrder::PlayerBody, ActorCol, CollisionType::Rect, CollisionType::Rect))
	{
		// 벡터 순회
		for (size_t i = 0; i < ActorCol.size(); i++)
		{
			// 몬스터 콜리전 참조
			GameEngineCollision* ActorBodyPtr = ActorCol[i];
			if (nullptr == ActorBodyPtr)
			{
				MsgBoxAssert("참조한 Actor 가 Null 입니다.");
				return;
			}

			Kirby* Actor = dynamic_cast<Kirby*>(ActorBodyPtr->GetActor());
			if (nullptr == Actor)
			{
				MsgBoxAssert("다운 캐스팅 오류입니다.");
				return;
			}

			// 커비 상태 변경 트리거 On
			switch (ItemNumber)
			{
			case 1:
				Actor->IsReachedStarStick = true;
				break;
			case 2:
				break;
			case 3:
				break;
			default:
				break;
			}
		}

		IsReached = true;
	}

}




void Item::ItemPointerRelease()
{
	if (nullptr != MainRenderer)
	{
		MainRenderer = nullptr;
	}
	if (nullptr != BodyCollision)
	{
		BodyCollision = nullptr;
	}
	if (nullptr != GroundTexture)
	{
		GroundTexture = nullptr;
	}
}


void Item::ObjectPointerRelease()
{
	if (nullptr != MainRenderer)
	{
		MainRenderer = nullptr;
	}
	if (nullptr != BodyCollision)
	{
		BodyCollision = nullptr;
	}
	if (nullptr != GroundTexture)
	{
		GroundTexture = nullptr;
	}
}

