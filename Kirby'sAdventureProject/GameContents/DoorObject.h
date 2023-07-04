#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class DoorObject : public GameEngineActor
{
	friend class VegetableValleyHub;
public:
	// constrcuter destructer
	DoorObject();
	~DoorObject();

	// delete Function
	DoorObject(const DoorObject& _Other) = delete;
	DoorObject(DoorObject&& _Other) noexcept = delete;
	DoorObject& operator=(const DoorObject& _Other) = delete;
	DoorObject& operator=(DoorObject&& _Other) noexcept = delete;


	void init(const float4& _DoorPos);


protected:

private:
	// GameEngineObject ���
	void Start() override;
	void Update(float _Delta) override;


private:
	// ����
	GameEngineRenderer* MainRenderer = nullptr;


	// ��û
	bool IsDoorIdle = false;
	bool IsDoorOpen = false;
	bool IsDoorClose = false;
	bool IsDoorClear = false;
	bool IsDoorStar = false;
	bool IsDoorBlocked = false;


public:
	// ����� ���� ����ġ
	void SwitchEffect();

};

