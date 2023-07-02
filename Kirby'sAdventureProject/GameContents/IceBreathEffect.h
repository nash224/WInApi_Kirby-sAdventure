#pragma once
#include "SkillEffect.h"



// Ό³Έν :
class IceBreathEffect : public SkillEffect
{
public:
	// constrcuter destructer
	IceBreathEffect();
	~IceBreathEffect();

	// delete Function
	IceBreathEffect(const IceBreathEffect& _Other) = delete;
	IceBreathEffect(IceBreathEffect&& _Other) noexcept = delete;
	IceBreathEffect& operator=(const IceBreathEffect& _Other) = delete;
	IceBreathEffect& operator=(IceBreathEffect&& _Other) noexcept = delete;

	void init(const float4& _Pos, const float4& _MaterScale, const float4& _Dir);

protected:


	// Level override
private:
	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;



	// SkilEffect override
private:
	void AbilityToActorCollisionCheck(CollisionOrder _ActorBodyCol, bool _IsDeath = false) override;


	// this
private:
	float Total_Effect_FrameTime = 0.5f;
	const float Effect_FrameDistance = 200.f;


};

