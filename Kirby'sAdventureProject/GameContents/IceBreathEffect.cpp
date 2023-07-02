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
		MsgBoxAssert("�������� ���� ������ ����..");
		return;
	}


	GlobalContents::SpriteFileLoad("Left_Ice_Breath.bmp", "Resources\\Effect\\SkillEffect", 6, 1);
	GameEngineSprite* Sprite = GlobalContents::SpriteFileLoad("Right_Ice_Breath.bmp", "Resources\\Effect\\SkillEffect", 6, 1);

	MainRenderer->CreateAnimation("Left_IceBreathEffect", "Left_Ice_Breath.bmp", 0, 4, 0.08f, false);
	MainRenderer->CreateAnimation("Right_IceBreathEffect", "Right_Ice_Breath.bmp", 0, 4, 0.08f, false);


	if (nullptr == Sprite)
	{
		MsgBoxAssert("��������Ʈ�� �ҷ����� ���߽��ϴ�.");
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




	// ���� ������ Death
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
		MsgBoxAssert("�浹ü�� Null �Դϴ�.");
		return;
	}


	std::vector<GameEngineCollision*> ActorCol;
	if (true == EffectCollision->Collision(_ActorBodyCol, ActorCol, CollisionType::Rect, CollisionType::Rect))
	{
		// ���� ��ȸ
		for (size_t i = 0; i < ActorCol.size(); i++)
		{
			// ���� �ݸ��� ����
			GameEngineCollision* Collision = ActorCol[i];
			if (nullptr == Collision)
			{
				MsgBoxAssert("������ Actor �� Null �Դϴ�.");
				return;
			}

			GameEngineActor* ActorPtr = Collision->GetActor();
			if (nullptr == ActorPtr)
			{
				MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
				return;
			}

			ActorPtr->Off();
			float4 EnemyPos = ActorPtr->GetPos();

			Enemy* EnemyPtr = dynamic_cast<Enemy*>(ActorPtr);
			if (nullptr == EnemyPtr)
			{
				MsgBoxAssert("�ٿ� ĳ���ÿ� �����߽��ϴ�.");
				return;
			}

			float4 EnemyScale = EnemyPtr->Scale;



			GameEngineLevel* CurLevelPtr = GetLevel();
			if (nullptr == CurLevelPtr)
			{
				MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
				return;
			}

			VegetableValleyPlayLevel* VegetableValleyPlayLevelPtr = dynamic_cast<VegetableValleyPlayLevel*>(CurLevelPtr);
			if (nullptr == VegetableValleyPlayLevelPtr)
			{
				MsgBoxAssert("���� �ٿ�ĳ���ÿ� �����߽��ϴ�.");
				return;
			}



			IceBlock* IceBlockPtr = CurLevelPtr->CreateActor<IceBlock>(UpdateOrder::Ability);
			if (nullptr == IceBlockPtr)
			{
				MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
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
