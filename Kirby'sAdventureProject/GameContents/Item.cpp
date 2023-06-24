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