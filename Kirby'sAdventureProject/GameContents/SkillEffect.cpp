#include "SkillEffect.h"
#include "ContentsEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "GlobalContents.h"
#include "ActorUtils.h"
#include "Boss.h"



SkillEffect::SkillEffect() 
{
}

SkillEffect::~SkillEffect() 
{
}




void SkillEffect::AbilityToActorCollisionCheck(CollisionOrder _ActorBodyCol, bool _IsDeath /*= false*/)
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


			if (true == _IsDeath)
			{
				IsAbilityCollisionCheck = true;
				Death();
				EffectPointerRelease();
				return;
			}
		}
	}
}



void SkillEffect::AbilityToBossCollisionCheck(CollisionOrder _ActorBodyCol, int _Damage/* = 1*/, bool _IsDeath /*= false*/)
{
	if (nullptr == EffectCollision)
	{
		MsgBoxAssert("�浹ü�� Null �Դϴ�.");
		return;
	}

	std::vector<GameEngineCollision*> BossCol;
	if (true == EffectCollision->Collision(CollisionOrder::BossBody, BossCol, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < BossCol.size(); i++)
		{
			GameEngineCollision* BossCollision = BossCol[i];
			if (nullptr == BossCollision)
			{
				MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
				return;
			}

			GameEngineActor* BossActorPtr = BossCollision->GetActor();
			if (nullptr == BossActorPtr)
			{
				MsgBoxAssert("������ Actor �� Null �Դϴ�.");
				return;
			}

			Boss* Actor = dynamic_cast<Boss*>(BossActorPtr);
			if (nullptr == Actor)
			{
				MsgBoxAssert("�ٿ� ĳ���� �����Դϴ�.");
				return;
			}

			// ���� ���� ���� Ʈ���� On
			Actor->IsHitted = true;
			Actor->m_BossHp -= _Damage;

			if (true == _IsDeath)
			{
				Death();
				EffectPointerRelease();
				return;
			}
		}
	}
}



float4 SkillEffect::GetCameraPos()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	return CameraPos;
}

void SkillEffect::SetActorCollision(CollisionOrder _Order, CollisionType _Type)
{
	EffectCollision = CreateCollision(_Order);

	if (nullptr == EffectCollision)
	{
		MsgBoxAssert("�ݸ����� Null�Դϴ�.");
		return;
	}

	EffectCollision->SetCollisionScale(Scale);
	EffectCollision->SetCollisionType(_Type);

	
	switch (_Order)
	{
	case CollisionOrder::PlayerAbility:
		IsPlayerCollision = true;
		break;
	case CollisionOrder::MonsterAbility:
		IsPlayerCollision = false;
		break;
	default:
		break;
	}
}


void SkillEffect::SetCheckPoint(const float4& _ScaleSize)
{
	CenterCheckPoint = { 0.0f , 0.0f };
	FrontCheckPoint = { -_ScaleSize.Half().X, 0.0f};
}

void SkillEffect::SetGroundTexture(const std::string& _GroundTextureName)
{
	GroundTexture = ResourcesManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTexture)
	{
		MsgBoxAssert(" �ȼ��浹 ���� ã�� �� �����ϴ�. " + _GroundTextureName);
		return;
	}

	IsPassGround = false;
}

int SkillEffect::GetGroundColor(unsigned int _DefaultColor, float4 _Pos/* = float4::ZERO*/)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("�ȼ� �浹 �ؽ�ó�� �������� �ʽ��ϴ�.");
		return 0;
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}

bool SkillEffect::CheckFrontPoint()
{
	unsigned int FrontColor = GetGroundColor(RGB(255, 255, 255), FrontCheckPoint);
	if ((RGB(0, 255, 255) == FrontColor))
	{
		return true;
	}

	return false;
}

bool SkillEffect::CheckCenterPoint()
{
	unsigned int CenterColor = GetGroundColor(RGB(255, 255, 255), CenterCheckPoint);
	if ((RGB(0, 255, 255) == CenterColor))
	{
		return true;
	}

	return false;
}



void SkillEffect::EffectPointerRelease()
{
	if (nullptr != MainRenderer)
	{
		MainRenderer = nullptr;
	}
	if (nullptr != EffectCollision)
	{
		EffectCollision = nullptr;
	}
	if (nullptr != GroundTexture)
	{
		GroundTexture = nullptr;
	}
}