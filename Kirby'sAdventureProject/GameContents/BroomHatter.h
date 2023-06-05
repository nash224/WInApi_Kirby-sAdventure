#pragma once
#include "NormalEnemies.h"

#define BROOMHATTERSPEED 100.0f

// Ό³Έν :
class BroomHatter : public NormalEnemies
{
public:
	// constrcuter destructer
	BroomHatter();
	~BroomHatter();

	// delete Function
	BroomHatter(const BroomHatter& _Other) = delete;
	BroomHatter(BroomHatter&& _Other) noexcept = delete;
	BroomHatter& operator=(const BroomHatter& _Other) = delete;
	BroomHatter& operator=(BroomHatter&& _Other) noexcept = delete;

protected:

	void IdleStart() override;
	void SweepStart() override;


	void IdleUpdate(float _Delta) override;
	void SweepUpdate(float _Delta) override;

private:
	void Start() override;
	void Update(float _Delta) override;
};

