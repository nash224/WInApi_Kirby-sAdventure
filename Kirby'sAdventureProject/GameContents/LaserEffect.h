#pragma once
#include "SkillEffect.h"



// ���� : Ŀ��� ������ ���� ��� ���Դϴ�. �Ƹ� ���� ���� �����ϰ̴ϴ�.
class LaserEffect : public SkillEffect
{
public:
	// constrcuter destructer
	LaserEffect();
	~LaserEffect();

	// delete Function
	LaserEffect(const LaserEffect& _Other) = delete;
	LaserEffect(LaserEffect&& _Other) noexcept = delete;
	LaserEffect& operator=(const LaserEffect& _Other) = delete;
	LaserEffect& operator=(LaserEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir);
	void Soundinit();

protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;


	// SkillEffect override
	void SkillDeathEffect() override;



	// this
	void GroundPassUpdate(float _Delta);
	void GroundNotPassUpdate(float _Delta);


	const float EffectSpeed = 1200.0f;

	// ����
	bool IsSoundinit = false;
};

