#pragma once
#include <GameEngineCore/GameEngineActor.h>

#define UNIT 1.0f

enum class ActorDir
{
	Right,
	Left,
	Max,
};

enum class AttributeType
{
	None,
	Fire,
	Electricity,
	Ice,
	Max,
};


// 설명 :
class ContentsActor : public GameEngineActor
{
public:
	// constrcuter destructer
	ContentsActor();
	~ContentsActor();

	// delete Function
	ContentsActor(const ContentsActor& _Other) = delete;
	ContentsActor(ContentsActor&& _Other) noexcept = delete;
	ContentsActor& operator=(const ContentsActor& _Other) = delete;
	ContentsActor& operator=(ContentsActor&& _Other) noexcept = delete;

protected:
	AttributeType Attribute = AttributeType::Max;
	ActorDir Dir = ActorDir::Max;
	const float4 SmallTypeScale = float4{ 48.0f , 48.0f };

	float CurrentSpeed = 0.0f;


	virtual void DecelerationUpdate(float _Delta, float _Speed);
	virtual void HorizontalSpeedLimit(float _Speed);
	virtual void HorizontalUpdate(float _Delta);


	// 디버그
	const int DebugRenderText_YInter = 18;

private:

};

