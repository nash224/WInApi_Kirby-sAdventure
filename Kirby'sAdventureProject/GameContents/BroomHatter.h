#pragma once
#include "NormalEnemies.h"

#define BROOMHATTERSPEED 300.0f
#define BROOMHATTERCHANGETIME 0.5f
#define BROOMHATTERDECELERATIONSPEED BROOMHATTERSPEED / BROOMHATTERCHANGETIME
#define BROOMHATTERMAXSPEED BROOMHATTERSPEED / BROOMHATTERCHANGETIME

// 설명 :
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

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// NormalEnemies 상속
	// 상태 패턴
	void IdleStart() override;
	void IdleUpdate(float _Delta) override;

	void SweepStart() override;
	void SweepUpdate(float _Delta) override;

	size_t SweepCount = 0;


};

