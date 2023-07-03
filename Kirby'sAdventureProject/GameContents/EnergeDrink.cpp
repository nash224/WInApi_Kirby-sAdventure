#include "EnergeDrink.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "VegetableValleyPlayLevel.h"
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
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}


	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("Items_4x3_48x48.bmp", "Resources\\Unit\\Object");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
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
		MsgBoxAssert("Null 일리가 없어");
		return;
	}

	BodyCollision->SetCollisionPos(float4{ 0.0f , -Scale.Half().Y });
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
		// 벡터 순회
		for (size_t i = 0; i < PlayerCollision.size(); i++)
		{
			// 몬스터 콜리전 참조
			GameEngineCollision* ActorBodyPtr = PlayerCollision[i];
			if (nullptr == ActorBodyPtr)
			{
				MsgBoxAssert("충돌체를 읽어오지 못했습니다.");
				return;
			}

			GameEngineActor* PlayerActor = ActorBodyPtr->GetActor();
			if (nullptr == PlayerActor)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}


			Kirby* KirbyPtr = dynamic_cast<Kirby*>(PlayerActor);
			if (nullptr == KirbyPtr)
			{
				MsgBoxAssert("다운 캐스팅 변환에 실패했습니다.");
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




void EnergeDrink::Render(float _Delta)
{
	if (false == VegetableValleyPlayLevel::Level_DebugRenderValue)
	{
		return;
	}


	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	int TextRenderNum = 0;


	float4 ActorScenePos = ActorCameraPos();

	int TextXPos = ActorScenePos.iX() - Scale.Half().iX();
	int TextYPos = ActorScenePos.iY() - (Scale * 2.0f).iY();


	ThisDebugRender(dc, TextRenderNum, TextXPos, TextYPos);
}


void EnergeDrink::ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos)
{
	{
		std::string Text = "";
		Text += "Hp 2++";
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}
}





void EnergeDrink::LevelEnd()
{
	Death();
	ObjectPointerRelease();
}