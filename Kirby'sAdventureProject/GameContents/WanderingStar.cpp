#include "WanderingStar.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "VegetableValleyPlayLevel.h"
#include "CrossDeathEffect.h"
#include "Kirby.h"



WanderingStar::WanderingStar()
{
}

WanderingStar::~WanderingStar()
{
}




void WanderingStar::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}


	GameEngineSprite* Sprite = GlobalContents::SpriteFileLoad("SpitStar_1x4_16x16.bmp", "Resources\\Effect\\KirbyBaseEffect", 4, 1);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("스프라이트를 불러오지 못했습니다.");
		return;
	}


	MainRenderer->CreateAnimation("WanderingStar_Idle", "SpitStar_1x4_16x16.bmp", 0, 3, 0.1f, true);


	SetName("WanderingStar");


	Scale = Sprite->GetSprite(0).RenderScale;
	Scale -= float4{ 16.0f , 16.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Left;

	ChangeState(ItemState::Idle);


	BodyCollision = CreateCollision(CollisionOrder::WanderingStarBody);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("Null 일리가 없어");
		return;
	}

	BodyCollision->SetCollisionType(CollisionType::Rect);



	// 사운드 로드
	GlobalContents::SoundFileLoad("Star_Break.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("StarBreakSound.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("StarBounce.wav", "Resources\\SoundResources\\EffectVoice");
}


void WanderingStar::init(const float4& _MasterPos, const float4& _MasterScale, int _Order)
{
	SetPos(_MasterPos + float4{ 0.0f , -_MasterScale.Half().Y});

	Ability = static_cast<AbilityStar>(_Order);
}




void WanderingStar::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);
}



void WanderingStar::IdleStart()
{
	IsChangeState = false;

	StarLive_Time = 6.0f;
	
	// 랜덤으로 방향 설정
	int SetDir = GameEngineRandom::MainRandom.RandomInt(0, 1);

	if (0 == SetDir)
	{
		Dir = ActorDir::Left;
		CurrentSpeed = -m_XSpeed;
	}
	else if (1 == SetDir)
	{
		Dir = ActorDir::Right;
		CurrentSpeed = m_XSpeed;
	}


	GravityReset();

	ChangeAnimationState("Idle");
}

void WanderingStar::IdleUpdate(float _Delta)
{
	if (true == GetGroundState())
	{
		IsChangeState = true;
	}

	if (true == IsChangeState)
	{
		ChangeState(ItemState::BounceOff);
		return;
	}
	

	BlockedByGround();
	BlockedByWall();


	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);

	HorizontalUpdate(_Delta);
}


void WanderingStar::BounceOffStart()
{
	SetGravityVector(float4::UP * v_Bounce_Power);

	// 튕길 때 마다 시간 줄어듬
	StarLive_Time -= Star_ReduceTime_per_Bounce;
}


void WanderingStar::BounceOffUpdate(float _Delta)
{
	if (true == GetGroundState() && GetGravityVector().Y > 0.0f)
	{
		SetGravityVector(float4::UP * v_Bounce_Power);
		GameEngineSound::SoundPlay("StarBounce.wav");
	}

	if (true == CheckCeilingBasedSpeed())
	{
		SetGravityVector(float4::DOWN * v_Bounce_Power);
		GameEngineSound::SoundPlay("StarBounce.wav");
	}


	// 벽에 닿으면 튕기는 효과
	if (true == CheckLeftWallBasedSpeed())
	{
		Dir = ActorDir::Right;
		CurrentSpeed = m_XSpeed;
		GameEngineSound::SoundPlay("StarBounce.wav");
	}
	else if (true == CheckRightWallBasedSpeed())
	{
		Dir = ActorDir::Left;
		CurrentSpeed = -m_XSpeed;
		GameEngineSound::SoundPlay("StarBounce.wav");
	}




	if (GetLiveTime() > StarLive_Time)
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}


		// 별이 흩어지는 효과
		CrossDeathEffect* CrossDeathEffectPtr = CurLevelPtr->CreateActor<CrossDeathEffect>(UpdateOrder::Ability);
		if (nullptr == CrossDeathEffectPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		CrossDeathEffectPtr->init(GetPos(), float4{ 48.0f , 48.0f });

		GameEngineSound::SoundPlay("StarBreakSound.wav");


		Death();
		ObjectPointerRelease();
		return;
	}


	Gravity(_Delta);
	GravityLimit(_Delta);
	VerticalUpdate(_Delta);

	HorizontalUpdate(_Delta);


	CheckStarCollision();
}




void WanderingStar::BeInhaledStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("충돌체를 불러오지 못했습니다.");
		return;
	}

	BodyCollision->Off();

	IsInhaledStateOn = false;

	CurrentSpeed = 0.0f;

	ActorDirUnitVector = GetKirbyOpponentDistance();
}



void WanderingStar::BeInhaledUpdate(float _Delta)
{
	StateTime += _Delta;

	InhaleTargetPos = GetKirbyOpponentDistance();
	InhaleTargetPosYDistance = InhaleTargetPos.Y - KIRBYCENTERYPOINT;
	InhaleTargetPosXDistance = InhaleTargetPos.X;
	CurentVerticalSpeed += InhaleTargetPosYDistance / INHALETIME * _Delta;

	float4 KirbyPos = Kirby::GetMainKirby()->GetPos();


	if (ActorDirUnitVector.X < 0.0f)
	{
		float InhaleXSpeed = InhaleTargetPosXDistance / INHALETIME * _Delta;
		CurrentSpeed += InhaleXSpeed;

		if (GetPos().X < KirbyPos.X)
		{
			Death();
			ObjectPointerRelease();
			return;
		}
	}
	else if (ActorDirUnitVector.X > 0.0f)
	{
		float InhaleXSpeed = InhaleTargetPosXDistance / INHALETIME * _Delta;
		CurrentSpeed += InhaleXSpeed;

		if (GetPos().X > KirbyPos.X)
		{
			Death();
			ObjectPointerRelease();
			return;
		}
	}


	VerticalUpdateBasedlevitation(_Delta);

	HorizontalUpdate(_Delta);
}


void WanderingStar::CheckStarCollision()
{
	if (true == IsInhaledStateOn)
	{
		ChangeState(ItemState::BeInhaled);
		return;
	}
}




void WanderingStar::Render(float _Delta)
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


void WanderingStar::ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos)
{
	{
		std::string Text = "";
		Text += "능력 : ";

		switch (Ability)
		{
		case AbilityStar::Normal:
			Text += "Normal";
			break;
		case AbilityStar::Spark:
			Text += "Spark";
			break;
		case AbilityStar::Laser:
			Text += "Laser";
			break;
		case AbilityStar::Beam:
			Text += "Beam";
			break;
		case AbilityStar::Fire:
			Text += "Fire";
			break;
		case AbilityStar::Thorn:
			Text += "Thorn";
			break;
		case AbilityStar::Sword:
			Text += "Sword";
			break;
		case AbilityStar::Ice:
			Text += "Ice";
			break;
		default:
			break;
		}


		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	{
		std::string Text = "";
		Text += "LiveTime : ";
		Text += std::to_string(StarLive_Time - GetLiveTime());
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}
}



void WanderingStar::LevelEnd()
{
	Death();
	ObjectPointerRelease();
}