#pragma once
#include "NormalEnemies.h"

#define APPLEJUMPDISTANCE 300.0f
#define APPLEJUMPTIME 0.15f

#define APPLESPEED 400.0f
#define APPLECHANGETIME 2.0f
#define APPLESITTIME 0.1f
#define APPLEDECELERATIONSPEED APPLESPEED
#define APPLEMAXSPEED APPLESPEED / APPLECHANGETIME

#define APPLEIDLESPIN 0.2f
#define APPLEJUMPSPIN APPLEIDLESPIN * 0.5f

// Ό³Έν :
class Apple : public NormalEnemies
{
public:
	// constrcuter destructer
	Apple();
	~Apple();

	// delete Function
	Apple(const Apple& _Other) = delete;
	Apple(Apple&& _Other) noexcept = delete;
	Apple& operator=(const Apple& _Other) = delete;
	Apple& operator=(Apple&& _Other) noexcept = delete;


protected:

	void IdleStart() override;
	void SitStart() override;
	void JumpStart() override;


	void IdleUpdate(float _Delta) override;
	void SitUpdate(float _Delta) override;
	void JumpUpdate(float _Delta) override;

private:

	void Start() override;
	void Update(float _Delta) override;
};

