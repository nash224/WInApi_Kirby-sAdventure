#include "IceBlock.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "VegetableValleyPlayLevel.h"
#include "ActorUtils.h"
#include "Kirby.h"
#include "ObejctDisapearingEffect.h"
#include "CrossDeathEffect.h"



IceBlock::IceBlock()
{
	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("커비가 존재하지 않습니다.");
		return;
	}

	std::list<IceBlock*>& IceList = KirbyPtr->GetIceList();
	IceList.push_back(this);
}

IceBlock::~IceBlock()
{
}


void IceBlock::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("IceBlock.bmp", "Resources\\Effect\\SkillEffect");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 불러오지 못했습니다.");
		return;
	}

	MainRenderer->SetTexture("IceBlock.bmp");


	Scale = Texture->GetScale();

	SetCheckPoint(Scale);


	ChangeState(IceBlockState::Idle);



	BlockBodyCollision = CreateCollision(CollisionOrder::IceBlockMoveBody);
	if (nullptr == BlockBodyCollision)
	{
		MsgBoxAssert("충돌체를 생성하지 못했습니다.");
		return;
	}

	BlockBodyCollision->SetCollisionScale(Scale);
	BlockBodyCollision->SetCollisionType(CollisionType::Rect);
	BlockBodyCollision->On();

}

void IceBlock::init(const float4& _Pos, const float4& _MasterPos)
{
	SetPos(_Pos + float4{ 0.0f , -_MasterPos.Half().Y });
}





void IceBlock::Update(float _Delta)
{
	StateUpdate(_Delta);
}


void IceBlock::StateUpdate(float _Delta)
{
	switch (State)
	{
	case IceBlockState::Idle:
		IdleUpdate(_Delta);
		break;
	case IceBlockState::Wing:
		WingUpdate(_Delta);
		break;
	default:
		break;
	}
}


void IceBlock::ChangeState(IceBlockState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case IceBlockState::Idle:
			IdleStart();
			break;
		case IceBlockState::Wing:
			WingStart();
			break;
		default:
			break;
		}

		State = _State;
	}
}



void IceBlock::IdleStart()
{

}

void IceBlock::IdleUpdate(float _Delta)
{

	// 시간지나면 녹음
	if (GetLiveTime() > LiveTime)
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("레벨을 불러오지 못했습니다.");
			return;
		}


		CrossDeathEffect* CrossDeathEffectPtr = CurLevelPtr->CreateActor<CrossDeathEffect>(UpdateOrder::Ability);
		if (nullptr == CrossDeathEffectPtr)
		{
			MsgBoxAssert("액터를 생성하지 못했습니다.");
			return;
		}

		CrossDeathEffectPtr->init(GetPos(), Scale);

		Death();
		ReleaseThisList();
		EffectPointerRelease();
		return;
	}



	BlockToPlayerCollisionCheck();
}



void IceBlock::WingStart()
{
	
}

void IceBlock::WingUpdate(float _Delta)
{
	// 위치 동기화
	AddPos(EffectDir * SMALLSTARFIREEFFECTSPEED * _Delta);



	// 중앙에 비트맵이 닿았는 지 검사
	if (true == CheckCenterPoint())
	{
		Call_DisapearEffect(false);

		Death();
		ReleaseThisList();
		EffectPointerRelease();

		return;
	}


	// 카메라 밖으로 넘어가면 
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = GetCameraPos();
	float XPos = GetPos().X;
	if (XPos < CameraPos.X || XPos > CameraPos.X + WinScale.X)
	{
		// 죽고 정리
		Death();
		ReleaseThisList();
		EffectPointerRelease();

		return;
	}





	// 충돌 체크
	AbilityToActorCollisionCheck(CollisionOrder::MonsterBody, true);

	if (false == IsAbilityCollisionCheck)
	{
		int Damage = GameEngineRandom::MainRandom.RandomInt(3, 5);
		AbilityToBossCollisionCheck(CollisionOrder::BossBody, Damage, true);
	}

}






void IceBlock::BlockToPlayerCollisionCheck()
{
	if (nullptr == BlockBodyCollision)
	{
		MsgBoxAssert("충돌체를 불러오지 못했습니다.");
		return;
	}

	
	std::vector<GameEngineCollision*> PlayerCol;
	if (true == BlockBodyCollision->Collision(CollisionOrder::PlayerBody, PlayerCol, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < PlayerCol.size(); i++)
		{
			GameEngineCollision* Collision = PlayerCol[i];
			if (nullptr == Collision)
			{
				MsgBoxAssert("충돌체를 불러오지 못했습니다.");
				return;
			}

			GameEngineActor* PlayerPtr = Collision->GetActor();
			if (nullptr == PlayerPtr)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			float4 KirbyPos = PlayerPtr->GetPos();

			if (GetPos().X > KirbyPos.X)
			{
				EffectDir = float4::RIGHT;
			}
			else if (GetPos().X <= KirbyPos.X)
			{
				EffectDir = float4::LEFT;
			}

			BlockBodyCollision->Off();
			ChangeState(IceBlockState::Wing);
			return;
		}
	}

}



void IceBlock::SkillDeathEffect()
{
	Call_DisapearEffect();
}

void IceBlock::DataStructRelease()
{
	ReleaseThisList();
}


void IceBlock::ReleaseThisList()
{
	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("커비가 존재하지 않습니다.");
		return;
	}

	std::list<IceBlock*>& IceList = KirbyPtr->GetIceList();
	IceList.remove(this);
	std::list<IceBlock*>& ResultIceList = KirbyPtr->GetIceList();
}




void IceBlock::Render(float _Delta)
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


void IceBlock::ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos)
{

	float4 EffectPos = GetPos();
	{
		std::string Text = "";
		Text += "X 좌표 : ";
		Text += std::to_string(EffectPos.X);
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}


	{
		std::string Text = "";
		Text += "Y 좌표 : ";
		Text += std::to_string(EffectPos.Y);
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}
}





void IceBlock::LevelEnd()
{
	Death();
	ReleaseThisList();
	EffectPointerRelease();
}
