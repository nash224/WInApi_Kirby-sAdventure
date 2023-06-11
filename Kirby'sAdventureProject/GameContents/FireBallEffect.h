#pragma once
#include "SkillEffect.h"

#define FIREBALLEFFECTSPEED 600.0f


// ���� :
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

	void init(const std::string& _FileName, const float4& _Pos, const float4& _MaterScale, const float4& _Dir);
	void init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir);

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void GroundPassUpdate(float _Delta) override;
	void GroundNotPassUpdate(float _Delta) override;
};

