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


	void init(const float4& _StageOneDoorPos);

protected:

private:
	// GameEngineObject ���
	void Start() override;


	// ����
	GameEngineRenderer* FlagRenderer = nullptr;
};

