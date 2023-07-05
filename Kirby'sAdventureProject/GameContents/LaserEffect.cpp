#include "LaserEffect.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>


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
		MsgBoxAssert("�������� ���� ������ ����..");
		return;
	}

	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("LaserEffect_1x1_32x8.bmp", "Resources\\Effect\\SkillEffect");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� ���ϸ��� ����..");
		return;
	}
	

	MainRenderer->SetTexture("LaserEffect_1x1_32x8.bmp");

	Scale = Texture->GetScale();
	SetCheckPoint(Scale);


	// ���� �ε�
	GlobalContents::SoundFileLoad("Kirby_Laser.wav", "Resources\\SoundResources\\EffectVoice");
	GlobalContents::SoundFileLoad("Enemy_Laser.wav", "Resources\\SoundResources\\EffectVoice");

}

void LaserEffect::init(const float4& _Pos, const float4& _MaterScale , const float4& _Dir)
{
	EffectDir = _Dir;
	SetPos(_Pos + EffectDir * (_MaterScale.Half().X + Scale.Half().X) + float4{ 0.0f, -_MaterScale.Half().Y });


}

void LaserEffect::Soundinit()
{
	if (true == IsPlayerCollision)
	{
		GameEngineSound::SoundPlay("Kirby_Laser.wav");
	}
	else if (false == IsPlayerCollision)
	{
		GameEngineSound::SoundPlay("Enemy_Laser.wav");
	}
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


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
	if (false == IsSoundinit)
	{
		IsSoundinit = true;

		Soundinit();
	}


	AddPos(EffectDir * EffectSpeed * _Delta);

	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	float4 CameraPos = GetCameraPos();
	if (CameraPos.X > GetPos().X && GetPos().X > CameraPos.X + WinScale.X)
	{
		Death();
		EffectPointerRelease();
		return;
	}


	if (true == IsPlayerCollision)
	{
		AbilityToActorCollisionCheck(CollisionOrder::MonsterBody, true);

		if (false == IsAbilityCollisionCheck)
		{
			int DamageValue = GameEngineRandom::MainRandom.RandomInt(2, 3);
			AbilityToBossCollisionCheck(CollisionOrder::BossBody, DamageValue, true);
		}
	}
	else if (false == IsPlayerCollision)
	{
		AbilityToActorCollisionCheck(CollisionOrder::PlayerBody, true);
	}

}


void LaserEffect::GroundNotPassUpdate(float _Delta)
{

}


void LaserEffect::SkillDeathEffect()
{
	// ���� ȿ��
	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
		return;
	}

	DustEffect* DustEffectPtr = CurLevelPtr->CreateActor<DustEffect>(UpdateOrder::Ability);
	if (nullptr == DustEffectPtr)
	{
		MsgBoxAssert("���Ͱ� Null �Դϴ�.");
		return;
	}

	DustEffectPtr->init(GetPos(), Scale, EffectDir);
}




/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */

void LaserEffect::LevelEnd()
{
	Death();
	EffectPointerRelease();
}