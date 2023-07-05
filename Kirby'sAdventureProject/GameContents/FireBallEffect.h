#pragma once
#include "SkillEffect.h"


// ���� : Hot Head �� �����Ÿ����� Ŀ�� ����մϴ�. ������ ���� ���ѵǾ� �־� ���߱� ����� �մϴ�.
class FireBallEffect : public SkillEffect
{
public:
	// constrcuter destructer
	FireBallEffect();
	~FireBallEffect();

	// delete Function
	FireBallEffect(const FireBallEffect& _Other) = delete;
	FireBallEffect(FireBallEffect&& _Other) noexcept = delete;
	FireBallEffect& operator=(const FireBallEffect& _Other) = delete;
	FireBallEffect& operator=(FireBallEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir);

protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel override
	void LevelEnd() override;


	// this
	const float EffectSpeed = 400.0f;
};

