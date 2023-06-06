#pragma once
#include "NormalEnemies.h"

#define POPPYBROSJRSPEED 100.0f
#define POPPYBROSJRCHANGETIME 0.1f

#define POPPYBROSJRJUMPTIME 0.05f
#define POPPYBROSJRJUMPDISTANCE 5.0f

// Ό³Έν :
class PoppyBrosJr : public NormalEnemies
{
public:
	// constrcuter destructer
	PoppyBrosJr();
	~PoppyBrosJr();

	// delete Function
	PoppyBrosJr(const PoppyBrosJr& _Other) = delete;
	PoppyBrosJr(PoppyBrosJr&& _Other) noexcept = delete;
	PoppyBrosJr& operator=(const PoppyBrosJr& _Other) = delete;
	PoppyBrosJr& operator=(PoppyBrosJr&& _Other) noexcept = delete;


protected:

	void IdleStart() override;
	//void WalkStart() override;
	void JumpStart() override;
	void FallStart() override;


	void IdleUpdate(float _Delta) override;
	//void WalkUpdate(float _Delta) override;
	void JumpUpdate(float _Delta) override;
	void FallUpdate(float _Delta) override;

private:

	void Start() override;
	void Update(float _Delta) override;
};

