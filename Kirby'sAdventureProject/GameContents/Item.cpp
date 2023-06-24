#include "Item.h"
#include "ContentsEnum.h"


#include <GameEngineCore/GameEngineCollision.h>


#include "Kirby.h"


Item::Item() 
{
}

Item::~Item() 
{
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