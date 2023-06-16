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
	virtual void SetActorCollision(CollisionOrder _Order, CollisionType _Type);

	// ���� �� �ӵ��� �����ϴ� �Լ�
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
	GameEngineCollision* EffectCollision = nullptr;

	float4 Scale = float4::ZERO;
	float4 EffectDir = float4::ZERO;
	float Speed = 0.0f;
	float EffectDuration = 0.0f;


	// ī�޶� ��ġ ��ȯ �Լ�
	float4 GetCameraPos();


	// �浹 ���� �Լ�
	void SetCheckPoint(const float4& _ScaleSize);
	int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);
	bool CheckFrontPoint();
	bool CheckCenterPoint();


	// ���� �����ų� ���� ����ϴ� ����� ���н����ִ� �Լ�
	bool IsPassGround = true;
	virtual void GroundPassUpdate(float _Delta) {}
	virtual void GroundNotPassUpdate(float _Delta) {}


	// �޸� ���� �Լ�
	void EffectPointerRelease();

private:
	class GameEngineWindowTexture* GroundTexture = nullptr;

	// ��Ʈ�� �浹 ��ġ
	float4 FrontCheckPoint = float4::ZERO;
	float4 CenterCheckPoint = float4::ZERO;

};

