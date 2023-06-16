#include "SkillEffect.h"
#include "ContentsEnum.h"

#include <GameEngineCore/ResourcesManager.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "GlobalContents.h"

SkillEffect::SkillEffect() 
{
}

SkillEffect::~SkillEffect() 
{
}



float4 SkillEffect::GetCameraPos()
{
	float4 CameraPos = GetLevel()->GetMainCamera()->GetPos();
	return CameraPos;
}

void SkillEffect::SetActorCollision(CollisionOrder _Order, CollisionType _Type)
{
	EffectCollision = CreateCollision(_Order);
	EffectCollision->SetCollisionScale(Scale);
	EffectCollision->SetCollisionType(_Type);
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
