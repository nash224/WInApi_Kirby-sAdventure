#pragma once
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsActor.h"
#include "ContentsEnum.h"

// 설명 :
class SkillEffect : public ContentsActor
{
public:
	// constrcuter destructer
	SkillEffect();
	~SkillEffect();

	// delete Function
	SkillEffect(const SkillEffect& _Other) = delete;
	SkillEffect(SkillEffect&& _Other) noexcept = delete;
	SkillEffect& operator=(const SkillEffect& _Other) = delete;
	SkillEffect& operator=(SkillEffect&& _Other) noexcept = delete;

	class GameEngineRenderer* MainRenderer = nullptr;

	void SetGroundTexture(const std::string& _GroundTextureName);
	virtual void SetActorCollision(CollisionOrder _Order, CollisionType _Type);

	void SetEffectDir(const float4& _Dir)
	{
		EffectDir = _Dir;
	}

	void SetSpeed(const float _Speed)
	{
		Speed = _Speed;
	}


protected:
	GameEngineCollision* EffectCollision = nullptr;

	bool IsPassGround = true;
	float Speed = 0.0f;
	float4 EffectDir = float4::ZERO;
	float4 Scale = float4::ZERO;


	float4 CameraPos();


	// 충돌 감지
	void SetCheckPoint(const float4& _ScaleSize);
	int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);
	void CheckFrontPoint();
	void CheckCenterPoint();

	bool GetFrontPoint() const
	{
		return IsFrontPointReachGround;
	}

	bool GetCenterPoint() const
	{
		return IsCenterPointReachGround;
	}


	virtual void GroundPassUpdate(float _Delta) {}
	virtual void GroundNotPassUpdate(float _Delta) {}


private:
	class GameEngineWindowTexture* GroundTexture = nullptr;

	bool IsCenterPointReachGround = false;
	bool IsFrontPointReachGround = false;


	float4 FrontCheckPoint = float4::ZERO;
	float4 CenterCheckPoint = float4::ZERO;
};

