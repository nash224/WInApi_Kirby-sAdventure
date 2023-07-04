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


// 설명 : 컨텐츠의 최상위 액터 클래스이며, SkillEffect 와 Actor 에게 필요한 기능을 제공해줍니다.
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
	// 속성 추가할 예정이었으나 시간이 부족해서 사용하지 않음
	AttributeType Attribute = AttributeType::Max;

	// 
	const float4 SmallTypeScale = float4{ 48.0f , 48.0f };
	ActorDir Dir = ActorDir::Max;


	// 카메라 기준의 액터 위치
	float4 ActorCameraPos();


	// X축 이동로직
	float CurrentSpeed = 0.0f;
	virtual void DecelerationUpdate(float _Delta, float _Speed);
	virtual void HorizontalSpeedLimit(float _Speed);
	virtual void HorizontalUpdate(float _Delta);


	// 디버그
	const int DebugRenderText_YInter = 18;

private:

};

