#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
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
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;


private:
	// 렌더
	GameEngineRenderer* MainRenderer = nullptr;


	// 요청
	bool IsDoorIdle = false;
	bool IsDoorOpen = false;
	bool IsDoorClose = false;
	bool IsDoorClear = false;
	bool IsDoorStar = false;
	bool IsDoorBlocked = false;


public:
	// 디버깅 렌더 스위치
	void SwitchEffect();

};

