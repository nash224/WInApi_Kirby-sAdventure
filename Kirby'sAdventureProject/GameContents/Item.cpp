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
		MsgBoxAssert(" �ȼ��浹 ���� ã�� �� �����ϴ�. " + _GroundTextureName);
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



// ���� ����
void Item::ChangeAnimationState(const std::string& _StateName)
{
	std::string AnimationName = GetName();
	CurState = _StateName;
	AnimationName += "_";
	AnimationName += _StateName;
	MainRenderer->ChangeAnimation(AnimationName);
}



// �����ۿ� Ŀ�� ������ �Ÿ��� ��ȯ
float4 Item::GetKirbyOpponentDistance()
{
	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("Ŀ�� �ҷ����� ���߽��ϴ�.");
		return float4::ZERO;
	}

	float4 OpponentDistance = KirbyPtr->GetPos() - GetPos();
	return OpponentDistance;
}




void Item::ItemCollisionCheck()
{
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("�浹ü�� Null �Դϴ�.");
		return;
	}


	std::vector<GameEngineCollision*> ActorCol;
	if (true == BodyCollision->Collision(CollisionOrder::PlayerBody, ActorCol, CollisionType::Rect, CollisionType::Rect))
	{
		// ���� ��ȸ
		for (size_t i = 0; i < ActorCol.size(); i++)
		{
			// ���� �ݸ��� ����
			GameEngineCollision* ActorBodyPtr = ActorCol[i];
			if (nullptr == ActorBodyPtr)
			{
				MsgBoxAssert("������ Actor �� Null �Դϴ�.");
				return;
			}

			Kirby* Actor = dynamic_cast<Kirby*>(ActorBodyPtr->GetActor());
			if (nullptr == Actor)
			{
				MsgBoxAssert("�ٿ� ĳ���� �����Դϴ�.");
				return;
			}

			// Ŀ�� ���� ���� Ʈ���� On
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

