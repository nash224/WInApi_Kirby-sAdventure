#pragma once
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsActor.h"
#include "ContentsEnum.h"

// ���� : GameEffect�� ������ ��� Effect �� �θ��Դϴ�. �ڽ� Ŭ�������� �ʿ��� ����� �����մϴ�.
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


	// �ܺο��� �ؽ�ó ���� �����ϴ� �Լ�
	void SetGroundTexture(const std::string& _GroundTextureName);

	// �ܺο��� �浹�� �����ϴ� �Լ�
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



	// ī�޶� ��ġ ��ȯ
	float4 GetCameraPos();

	float4 FrontCheckPoint = float4::ZERO;
	float4 CenterCheckPoint = float4::ZERO;

	void SetCheckPoint(const float4& _ScaleSize);
	bool CheckFrontPoint();
	bool CheckCenterPoint();




	// �浹
	GameEngineCollision* EffectCollision = nullptr;

	bool IsPlayerCollision = true;
	bool IsAbilityCollisionCheck = false;

	virtual void AbilityToActorCollisionCheck(CollisionOrder _ActorBodyCol, bool _IsDeath = false);
	void AbilityToBossCollisionCheck(CollisionOrder _ActorBodyCol, int _Damage = 1, bool _IsDeath = false);
	virtual void SkillDeathEffect() {}
	virtual void DataStructRelease() {}
	void Call_DisapearEffect(bool _Sound = true);




	// ���� �����ų� ���� ����ϴ� ����� ���н�����
	bool IsPassGround = true;


public:
	// �޸� ����
	void EffectPointerRelease();

};

