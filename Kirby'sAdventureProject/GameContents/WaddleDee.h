#pragma once
#include "NormalEnemies.h"


// ���� : �ܼ��� �ȱ⸸ �һ��� ����Դϴ�. 
// TMI) Waddle Doo �� �����Դϴ�.
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
	// GameEngineObject ���
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// NormalEnemies ���
	void WalkStart() override;
	void WalkUpdate(float _Delta) override;


	const float WaddleSpeed = 80.0f;


};

