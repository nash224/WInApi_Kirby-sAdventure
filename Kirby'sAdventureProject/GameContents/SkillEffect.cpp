#include "SkillEffect.h"
#include "ContentsEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "GlobalContents.h"
#include "ActorUtils.h"



SkillEffect::SkillEffect() 
{
}

SkillEffect::~SkillEffect() 
{
}




void SkillEffect::AbilityToActorCollisionCheck(CollisionOrder _ActorBodyCol)
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
		MsgBoxAssert("콜리전이 Null입니다.");
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
		MsgBoxAssert(" 픽셀충돌 맵을 찾을 수 없습니다. " + _GroundTextureName);
		return;
	}

	IsPassGround = false;
}

int SkillEffect::GetGroundColor(unsigned int _DefaultColor, float4 _Pos/* = float4::ZERO*/)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("픽셀 충돌 텍스처가 존재하지 않습니다.");
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