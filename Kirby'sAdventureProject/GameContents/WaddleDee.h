#pragma once
#include "NormalEnemies.h"


// 설명 : 단순히 걷기만 할뿐인 잡몹입니다. 
// TMI) Waddle Doo 와 사촌입니다.
class WaddleDee : public NormalEnemies
{
public:
	// constrcuter destructer
	WaddleDee();
	~WaddleDee();

	// delete Function
	WaddleDee(const WaddleDee& _Other) = delete;
	WaddleDee(WaddleDee&& _Other) noexcept = delete;
	WaddleDee& operator=(const WaddleDee& _Other) = delete;
	WaddleDee& operator=(WaddleDee&& _Other) noexcept = delete;

protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// NormalEnemies 상속
	void WalkStart() override;
	void WalkUpdate(float _Delta) override;


	const float WaddleSpeed = 80.0f;


};

