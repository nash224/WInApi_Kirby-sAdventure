#include "SkillEffect.h"
#include "ContentsEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "GlobalContents.h"
#include "ActorUtils.h"
#include "ObejctDisapearingEffect.h"
#include "Boss.h"



SkillEffect::SkillEffect() 
{
}

SkillEffect::~SkillEffect() 
{
}




// 카메라 위치 반환
float4 SkillEffect::GetCameraPos()
{
	static float4 ReturnValue;

	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return ReturnValue;
	}

	GameEngineCamera* MainCameraPtr = CurLevelPtr->GetMainCamera();
	if (nullptr == MainCameraPtr)
	{
		MsgBoxAssert("카메라를 불러오지 못했습니다.");
		return ReturnValue;
	}

	float4 CameraPos = MainCameraPtr->GetPos();
	return CameraPos;
}



// this->비트맵 지정
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


// 체크포인트 세팅
void SkillEffect::SetCheckPoint(const float4& _ScaleSize)
{
	CenterCheckPoint = { 0.0f , 0.0f };
	FrontCheckPoint = { -_ScaleSize.Half().X, 0.0f };
}



// 앞쪽 비트맵 체크
bool SkillEffect::CheckFrontPoint()
{
	unsigned int FrontColor = GetGroundColor(RGB(255, 255, 255), FrontCheckPoint);
	if ((RGB(0, 255, 255) == FrontColor) || (RGB(255, 255, 0) == FrontColor))
	{
		return true;
	}

	return false;
}

// 중앙 비트맵 체크
bool SkillEffect::CheckCenterPoint()
{
	unsigned int CenterColor = GetGroundColor(RGB(255, 255, 255), CenterCheckPoint);
	if ((RGB(0, 255, 255) == CenterColor) || (RGB(255, 255, 0) == CenterColor))
	{
		return true;
	}

	return false;
}




// 충돌 검사
void SkillEffect::AbilityToActorCollisionCheck(CollisionOrder _ActorBodyCol, bool _IsDeath /*= false*/)
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


			if (true == _IsDeath)
			{
				IsAbilityCollisionCheck = true;

				SkillDeathEffect();
				DataStructRelease();
				Death();
				EffectPointerRelease();
				return;
			}
		}
	}
}


// 보스와 충돌 검사
void SkillEffect::AbilityToBossCollisionCheck(CollisionOrder _ActorBodyCol, int _Damage/* = 1*/, bool _IsDeath /*= false*/)
{
	if (nullptr == EffectCollision)
	{
		MsgBoxAssert("충돌체가 Null 입니다.");
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
				MsgBoxAssert("보스를 불러오지 못했습니다.");
				return;
			}

			GameEngineActor* BossActorPtr = BossCollision->GetActor();
			if (nullptr == BossActorPtr)
			{
				MsgBoxAssert("참조한 Actor 가 Null 입니다.");
				return;
			}

			Boss* Actor = dynamic_cast<Boss*>(BossActorPtr);
			if (nullptr == Actor)
			{
				MsgBoxAssert("다운 캐스팅 오류입니다.");
				return;
			}

			// 몬스터 상태 변경 트리거 On
			Actor->IsHitted = true;
			Actor->m_BossHp -= _Damage;

			if (true == _IsDeath)
			{
				SkillDeathEffect();
				Death();
				DataStructRelease();
				EffectPointerRelease();
				return;
			}
		}
	}
}



// 사라지는 효과 호출
void SkillEffect::Call_DisapearEffect(bool _Sound /*= true*/)
{
	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("레벨을 불러오지 못했습니다.");
		return;
	}


	ObejctDisapearingEffect* ObejctDisapearingEffectPtr = CurLevelPtr->CreateActor<ObejctDisapearingEffect>(UpdateOrder::Ability);
	if (nullptr == ObejctDisapearingEffectPtr)
	{
		MsgBoxAssert("액터를 생성하지 못했습니다.");
		return;
	}

	ObejctDisapearingEffectPtr->init(GetPos(), false);

}



// 외부) 충돌 init
void SkillEffect::SetActorCollision(CollisionOrder _Order, CollisionType _Type, const float4& _CollisionScale)
{
	// Create Collision
	EffectCollision = CreateCollision(_Order);
	if (nullptr == EffectCollision)
	{
		MsgBoxAssert("콜리전이 Null입니다.");
		return;
	}

	// Set CollsionScale
	if (float4::ZERO == _CollisionScale)
	{
		EffectCollision->SetCollisionScale(Scale);
	}
	else if (float4::ZERO != _CollisionScale)
	{
		EffectCollision->SetCollisionScale(_CollisionScale);
	}

	// Set CollisionType
	EffectCollision->SetCollisionType(_Type);

	
	// Set Whose Collision
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


// 메모리 해제
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