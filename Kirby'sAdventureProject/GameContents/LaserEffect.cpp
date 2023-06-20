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



// ������ �浹 �Լ�
void LaserEffect::AbilityToActorCollisionCheck(CollisionOrder _ActorBodyCol)
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
			GameEngineCollision* ActorBodyPtr = ActorCol[i];
			if (nullptr == ActorBodyPtr)
			{
				MsgBoxAssert("������ Actor �� Null �Դϴ�.");
				return;
			}

			ActorUtils* Actor = dynamic_cast<ActorUtils*>(ActorBodyPtr->GetActor());
			if (nullptr == Actor)
			{
				MsgBoxAssert("�ٿ� ĳ���� �����Դϴ�.");
				return;
			}

			// ���� ���� ���� Ʈ���� On
			Actor->IsHitted = true;

			// ������ ����ȿ��
			DustEffect* DustEffectPtr = GetLevel()->CreateActor<DustEffect>(UpdateOrder::Ability);
			if (nullptr == DustEffectPtr)
			{
				MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
				return;
			}

			DustEffectPtr->init(GetPos(), float4::ZERO, EffectDir);



			Death();
			EffectPointerRelease();
			return;
		}
	}
}