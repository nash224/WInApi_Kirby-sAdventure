#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� : Stage Ŭ������ ��ǥ�Դϴ�. Ŀ���� �����̵尡 �������ϴ�.
class Flag : public GameEngineActor
{
	friend class VegetableValleyHub;
public:
	// constrcuter destructer
	Flag();
	~Flag();

	// delete Function
	Flag(const Flag& _Other) = delete;
	Flag(Flag&& _Other) noexcept = delete;
	Flag& operator=(const Flag& _Other) = delete;
	Flag& operator=(Flag&& _Other) noexcept = delete;


	void StageOneBillBoardinit(const float4& _StageOneDoorPos);

protected:
	GameEngineRenderer* FlagRenderer = nullptr;

private:
	void Start() override;
	void Update(float _Delta) override;


};

