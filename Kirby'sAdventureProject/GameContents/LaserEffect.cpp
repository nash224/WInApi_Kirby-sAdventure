#include "LaserEffect.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/ResourcesManager.h>

#include "GlobalContents.h"
#include "ActorUtils.h"
#include "DustEffect.h"


LaserEffect::LaserEffect() 
{
}

LaserEffect::~LaserEffect() 
{
}


void LaserEffect::Start() 
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("LaserEffect_1x1_32x8.bmp", "Resources\\Effect\\SkillEffect");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처가 널일리가 없어..");
		return;
	}
	

	MainRenderer->SetTexture("LaserEffect_1x1_32x8.bmp");

	Scale = Texture->GetScale();
	SetCheckPoint(Scale);
}

void LaserEffect::init(const float4& _Pos, const float4& _MaterScale , const float4& _Dir)
{
	EffectDir = _Dir;
	SetPos(_Pos + EffectDir * (_MaterScale.Half().X + Scale.Half().X) + float4{ 0.0f, -_MaterScale.Half().Y });
}


void LaserEffect::Update(float _Delta) 
{
	if (true == IsPassGround)
	{
		GroundPassUpdate(_Delta);
	}
	else if (false == IsPassGround)
	{
		GroundNotPassUpdate(_Delta);
	}
}


void LaserEffect::GroundPassUpdate(float _Delta)
{
	AddPos(EffectDir * LaserEffectSPEED * _Delta);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();

	if (GetCameraPos().X > GetPos().X && GetPos().X > GetCameraPos().X + WinScale.X)
	{
		Death();
		EffectPointerRelease();
		return;
	}


	if (true == IsPlayerCollision)
	{
		AbilityToActorCollisionCheck(CollisionOrder::MonsterBody);
	}
	else if (false == IsPlayerCollision)
	{
		AbilityToActorCollisionCheck(CollisionOrder::PlayerBody);
	}

}


void LaserEffect::GroundNotPassUpdate(float _Delta)
{

}



// 재정의 충돌 함수
void LaserEffect::AbilityToActorCollisionCheck(CollisionOrder _ActorBodyCol)
{

	if (nullptr == EffectCollision)
	{
		MsgBoxAssert("충돌체가 Null 입니다.");
		return;
	}


	std::vector<GameEngineCollision*> ActorCol;
	if (true == EffectCollision->Collision(_ActorBodyCol, ActorCol, CollisionType::Rect, CollisionType::Rect))
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

			ActorUtils* Actor = dynamic_cast<ActorUtils*>(ActorBodyPtr->GetActor());
			if (nullptr == Actor)
			{
				MsgBoxAssert("다운 캐스팅 오류입니다.");
				return;
			}

			// 몬스터 상태 변경 트리거 On
			Actor->IsHitted = true;

			// 맞으면 먼지효과
			DustEffect* DustEffectPtr = GetLevel()->CreateActor<DustEffect>(UpdateOrder::Ability);
			if (nullptr == DustEffectPtr)
			{
				MsgBoxAssert("액터를 생성하지 못했습니다.");
				return;
			}

			DustEffectPtr->init(GetPos(), float4::ZERO, EffectDir);



			Death();
			EffectPointerRelease();
			return;
		}
	}
}