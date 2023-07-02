#include "IceBreathEffect.h"
#include "ContentsEnum.h"

#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSprite.h>


#include "GlobalContents.h"
#include "VegetableValleyPlayLevel.h"
#include "Enemy.h"
#include "ActorUtils.h"
#include "ObejctDisapearingEffect.h"
#include "IceBlock.h"




IceBreathEffect::IceBreathEffect()
{
}

IceBreathEffect::~IceBreathEffect()
{
}


void IceBreathEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}


	GlobalContents::SpriteFileLoad("Left_Ice_Breath.bmp", "Resources\\Effect\\SkillEffect", 6, 1);
	GameEngineSprite* Sprite = GlobalContents::SpriteFileLoad("Right_Ice_Breath.bmp", "Resources\\Effect\\SkillEffect", 6, 1);

	MainRenderer->CreateAnimation("Left_IceBreathEffect", "Left_Ice_Breath.bmp", 0, 4, 0.08f, false);
	MainRenderer->CreateAnimation("Right_IceBreathEffect", "Right_Ice_Breath.bmp", 0, 4, 0.08f, false);


	if (nullptr == Sprite)
	{
		MsgBoxAssert("스프라이트를 불러오지 못했습니다.");
		return;
	}



	Scale = Sprite->GetSprite(0).RenderScale;
	SetCheckPoint(Scale);
}

void IceBreathEffect::init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir)
{
	EffectDir = _Dir;
	SetPos(_Pos + EffectDir * (_MaterScale.Half().X + Scale.Half().X) + float4{ 0.0f, -_MaterScale.Half().Y });


	if (EffectDir.X < 0.0f)
	{
		MainRenderer->ChangeAnimation("Left_IceBreathEffect");
	}
	else if (EffectDir.X >= 0.0f)
	{
		MainRenderer->ChangeAnimation("Right_IceBreathEffect");
	}
}


void IceBreathEffect::Update(float _Delta)
{
	if (GetLiveTime() > Total_Effect_FrameTime)
	{
		Death();
		EffectPointerRelease();
		return;
	}


	AbilityToActorCollisionCheck(CollisionOrder::MonsterBody, true);

	int Damage = GameEngineRandom::MainRandom.RandomInt(2, 3);
	AbilityToBossCollisionCheck(CollisionOrder::BossBody, Damage);


	float EffectSpeed = Effect_FrameDistance / Total_Effect_FrameTime;
	AddPos(EffectDir * EffectSpeed * _Delta);




	// 땅에 닿으면 Death
	if (true == CheckCenterPoint())
	{
		Call_DisapearEffect(false);
		Death();
		EffectPointerRelease();
		return;
	}
}




void IceBreathEffect::AbilityToActorCollisionCheck(CollisionOrder _ActorBodyCol, bool _IsDeath /*= false*/)
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
			GameEngineCollision* Collision = ActorCol[i];
			if (nullptr == Collision)
			{
				MsgBoxAssert("참조한 Actor 가 Null 입니다.");
				return;
			}

			GameEngineActor* ActorPtr = Collision->GetActor();
			if (nullptr == ActorPtr)
			{
				MsgBoxAssert("액터를 불러오지 못했습니다.");
				return;
			}

			ActorPtr->Off();
			float4 EnemyPos = ActorPtr->GetPos();

			Enemy* EnemyPtr = dynamic_cast<Enemy*>(ActorPtr);
			if (nullptr == EnemyPtr)
			{
				MsgBoxAssert("다운 캐스팅에 실패했습니다.");
				return;
			}

			float4 EnemyScale = EnemyPtr->Scale;



			GameEngineLevel* CurLevelPtr = GetLevel();
			if (nullptr == CurLevelPtr)
			{
				MsgBoxAssert("레벨을 불러오지 못했습니다.");
				return;
			}

			VegetableValleyPlayLevel* VegetableValleyPlayLevelPtr = dynamic_cast<VegetableValleyPlayLevel*>(CurLevelPtr);
			if (nullptr == VegetableValleyPlayLevelPtr)
			{
				MsgBoxAssert("레벨 다운캐스팅에 실패했습니다.");
				return;
			}



			IceBlock* IceBlockPtr = CurLevelPtr->CreateActor<IceBlock>(UpdateOrder::Ability);
			if (nullptr == IceBlockPtr)
			{
				MsgBoxAssert("액터를 생성하지 못했습니다.");
				return;
			}

			IceBlockPtr->init(EnemyPos, EnemyScale);
			IceBlockPtr->SetGroundTexture(VegetableValleyPlayLevelPtr->GetLevelBitMapFileName());
			IceBlockPtr->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect);
		}
	}
}






void IceBreathEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}
