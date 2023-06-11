#pragma once
#include "SkillEffect.h"

#define BEAMSPEED 1200.0f


// Ό³Έν :
class Beam : public SkillEffect
{
public:
	// constrcuter destructer
	Beam();
	~Beam();

	// delete Function
	Beam(const Beam& _Other) = delete;
	Beam(Beam&& _Other) noexcept = delete;
	Beam& operator=(const Beam& _Other) = delete;
	Beam& operator=(Beam&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir);

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	void GroundPassUpdate(float _Delta) override;
	void GroundNotPassUpdate(float _Delta) override;
};

