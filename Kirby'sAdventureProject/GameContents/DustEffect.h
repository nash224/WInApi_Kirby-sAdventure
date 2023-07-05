#pragma once
#include "SkillEffect.h"



// ���� : �޸����� Ư�� ��Ϳ����� ���� ȿ�� �Դϴ�.
class DustEffect : public SkillEffect
{
public:
	// constrcuter destructer
	DustEffect();
	~DustEffect();

	// delete Function
	DustEffect(const DustEffect& _Other) = delete;
	DustEffect(DustEffect&& _Other) noexcept = delete;
	DustEffect& operator=(const DustEffect& _Other) = delete;
	DustEffect& operator=(DustEffect&& _Other) noexcept = delete;

	void init(const float4& _MasterPos, const float4& _MasterScale, const float4& _Dir, int _ItersCount = 1);

protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;


	// this
	const float FrameChangeTime = 0.05f;
	const float EffectSpeed = 400.0f;
};

