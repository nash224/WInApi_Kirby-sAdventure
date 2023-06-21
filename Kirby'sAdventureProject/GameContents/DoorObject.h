#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
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
	GameEngineRenderer* MainRenderer = nullptr;

private:

	void Start() override;
	void Update(float _Delta) override;


private:
	bool IsDoorIdle = false;
	bool IsDoorOpen = false;
	bool IsDoorClose = false;
	bool IsDoorClear = false;

};

