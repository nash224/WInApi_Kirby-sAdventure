#pragma once
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsActor.h"
#include "ContentsEnum.h"

// 설명 : GameEffect를 제외한 모든 Effect 의 부모입니다. 자식 클래스에게 필요한 기능을 제공합니다.
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


	// 외부에서 텍스처 맵을 지정하는 함수
	void SetGroundTexture(const std::string& _GroundTextureName);

	// 외부에서 충돌을 지정하는 함수
	virtual void SetActorCollision(CollisionOrder _Order, CollisionType _Type, const float4& _CollisionScale = float4::ZERO);


	void SetEffectDir(const float4& _Dir)
	{
		EffectDir = _Dir;
	}

	void SetSpeed(const float _Speed)
	{
		Speed = _Speed;
	}


protected:

	class GameEngineRenderer* MainRenderer = nullptr;

	float4 Scale = float4::ZERO;
	float4 EffectDir = float4::ZERO;
	float Speed = 0.0f;
	float EffectDuration = 0.0f;



	// 카메라 위치 반환
	float4 GetCameraPos();

	float4 FrontCheckPoint = float4::ZERO;
	float4 CenterCheckPoint = float4::ZERO;

	void SetCheckPoint(const float4& _ScaleSize);
	bool CheckFrontPoint();
	bool CheckCenterPoint();




	// 충돌
	GameEngineCollision* EffectCollision = nullptr;

	bool IsPlayerCollision = true;
	bool IsAbilityCollisionCheck = false;

	virtual void AbilityToActorCollisionCheck(CollisionOrder _ActorBodyCol, bool _IsDeath = false);
	void AbilityToBossCollisionCheck(CollisionOrder _ActorBodyCol, int _Damage = 1, bool _IsDeath = false);
	virtual void SkillDeathEffect() {}
	virtual void DataStructRelease() {}
	void Call_DisapearEffect(bool _Sound = true);




	// 벽에 막히거나 벽을 통과하는 기능을 구분시켜줌
	bool IsPassGround = true;


public:
	// 메모리 해제
	void EffectPointerRelease();

};

