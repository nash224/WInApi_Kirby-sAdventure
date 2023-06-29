#include "EnergeDrink.h"
#include "ContentsEnum.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "GlobalContents.h"
#include "CrossDeathEffect.h"
#include "Kirby.h"
#include <vector>



EnergeDrink::EnergeDrink()
{
}

EnergeDrink::~EnergeDrink()
{
}




void EnergeDrink::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}


	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("Items_4x3_48x48.bmp", "Resources\\Unit\\Object");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}


	SetName("EnergeDrink");


	Scale = float4{ 48.0f , 48.0f };

	MainRenderer->SetTexture("Items_4x3_48x48.bmp");
	MainRenderer->SetCopyPos(float4{ 0.0f , Scale.Y * 2.0f });
	MainRenderer->SetCopyScale(Scale);
	MainRenderer->SetRenderPos(float4{ 0.0f , -Scale.Half().Y });
	MainRenderer->SetRenderScale(Scale);


	Scale = float4{ 24.0f , 48.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;

	ChangeState(ItemState::Idle);


	BodyCollision = CreateCollision(CollisionOrder::Item);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("Null �ϸ��� ����");
		return;
	}

	BodyCollision->SetCollisionScale(float4{ 24.0f , 48.0f });
	BodyCollision->SetCollisionType(CollisionType::Rect);
}


void EnergeDrink::init(const float4& _Pos)
{
	SetPos(_Pos);
}




void EnergeDrink::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);
}



void EnergeDrink::IdleStart()
{
	ChangeAnimationState("Idle");
}

void EnergeDrink::IdleUpdate(float _Delta)
{

	BlockedByGround();
	BlockedByWall();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}



	std::vector<GameEngineCollision*> PlayerCollision;
	if (true == BodyCollision->Collision(CollisionOrder::PlayerBody, PlayerCollision, CollisionType::Rect, CollisionType::Rect))
	{
		// ���� ��ȸ
		for (size_t i = 0; i < PlayerCollision.size(); i++)
		{
			// ���� �ݸ��� ����
			GameEngineCollision* ActorBodyPtr = PlayerCollision[i];
			if (nullptr == ActorBodyPtr)
			{
				MsgBoxAssert("�浹ü�� �о���� ���߽��ϴ�.");
				return;
			}

			GameEngineActor* PlayerActor = ActorBodyPtr->GetActor();
			if (nullptr == PlayerActor)
			{
				MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
				return;
			}


			Kirby* KirbyPtr = dynamic_cast<Kirby*>(PlayerActor);
			if (nullptr == KirbyPtr)
			{
				MsgBoxAssert("�ٿ� ĳ���� ��ȯ�� �����߽��ϴ�.");
				return;
			}

			KirbyPtr->m_KirbyHp += 2;

			if (KirbyPtr->m_KirbyHp > 6)
			{
				KirbyPtr->m_KirbyHp = 6;
			}


			Death();
			ObjectPointerRelease();
			return;
		}
	}
}




void EnergeDrink::LevelEnd()
{
	Death();
	ObjectPointerRelease();
}