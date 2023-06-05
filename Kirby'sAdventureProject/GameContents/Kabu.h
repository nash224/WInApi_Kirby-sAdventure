#pragma once
#include "NormalEnemies.h"

#define KABUJUMPDISTANCE 300.0f * JumpRatio
#define KABUJUMPTIME 0.15f

#define KABUSPEED 400.0f
#define KABUCHANGETIME 2.0f
#define KABUSITTIME 0.1f
#define KABUDECELERATIONSPEED KABUSPEED
#define KABUMAXSPEED KABUSPEED / KABUCHANGETIME

#define KABUIDLESPIN 0.2f
#define KABUJUMPSPIN KABUIDLESPIN * 0.5f

// Ό³Έν :
class Kabu : public NormalEnemies
{
public:
	// constrcuter destructer
	Kabu();
	~Kabu();

	// delete Function
	Kabu(const Kabu& _Other) = delete;
	Kabu(Kabu&& _Other) noexcept = delete;
	Kabu& operator=(const Kabu& _Other) = delete;
	Kabu& operator=(Kabu&& _Other) noexcept = delete;


protected:

	void IdleStart() override;
	void SitStart() override;
	void JumpStart() override;


	void IdleUpdate(float _Delta) override;
	void SitUpdate(float _Delta) override;
	void JumpUpdate(float _Delta) override;

private:
	float JumpRatio = 1.0f;

	void Start() override;
	void Update(float _Delta) override;
};

