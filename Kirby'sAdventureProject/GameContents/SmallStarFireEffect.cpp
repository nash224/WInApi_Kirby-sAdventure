#include "SmallStarFireEffect.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineSprite.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "ActorUtils.h"
#include "ObejctDisapearingEffect.h"
#include "Boss.h"



SmallStarFireEffect::SmallStarFireEffect()
{
}

SmallStarFireEffect::~SmallStarFireEffect()
{
}


void SmallStarFireEffect::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� ���� ������ ����..");
		return;
	}

	GameEngineSprite* Sprite = GlobalContents::SpriteFileLoad("SpitStar_1x4_16x16.bmp", "Resources\\Effect\\KirbyBaseEffect", 4, 1);

	MainRenderer->CreateAnimation("SmallStarFire", "SpitStar_1x4_16x16.bmp", 0, 3, FramesInter);
	MainRenderer->ChangeAnimation("SmallStarFire");


	Scale = Sprite->GetSprite(0).RenderScale;
	SetCheckPoint(Scale);
}

void SmallStarFireEffect::init(const std::string& _FileName, const float4& _Pos, const float4& _MaterScale, const float4& _Dir)
{
	EffectDir = _Dir;
	SetPos(_Pos + EffectDir * (_MaterScale.Half().X + Scale.Half().X) + float4{ 0.0f, -_MaterScale.Half().Y });
	SetGroundTexture(_FileName);
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void SmallStarFireEffect::Update(float _Delta)
{
	// ������ ���̸�
	if (true == CheckCenterPoint())
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}

		// ���� ������� ���
		ObejctDisapearingEffect* ObejctDisapearing = CurLevelPtr->CreateActor<ObejctDisapearingEffect>(UpdateOrder::Ability);
		if (nullptr == ObejctDisapearing)
		{
			MsgBoxAssert("���Ͱ� Null �Դϴ�.");
			return;
		}

		ObejctDisapearing->init(GetPos());


		// �װ� ����
		Death();
		EffectPointerRelease();

		return;
	}

	// ī�޶� ������ �Ѿ�� 
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = GetCameraPos();
	if (CameraPos.X > GetPos().X && GetPos().X > CameraPos.X + WinScale.X)
	{
		// �װ� ����
		Death();
		EffectPointerRelease();

		return;
	}



	AbilityToActorCollisionCheck(CollisionOrder::MonsterBody, true);

	if (false == IsAbilityCollisionCheck)
	{
		int Damage = GameEngineRandom::MainRandom.RandomInt(3, 4);
		AbilityToBossCollisionCheck(CollisionOrder::BossBody, Damage, true);
	}

	AddPos(EffectDir * EffectSpeed * _Delta);
}



void SmallStarFireEffect::SkillDeathEffect()
{
	// ���� ������� ���
	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}


	ObejctDisapearingEffect* ObejctDisapearing = CurLevelPtr->CreateActor<ObejctDisapearingEffect>(UpdateOrder::Ability);
	if (nullptr == ObejctDisapearing)
	{
		MsgBoxAssert("���Ͱ� Null �Դϴ�.");
		return;
	}

	ObejctDisapearing->init(GetPos());

}


/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void SmallStarFireEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}