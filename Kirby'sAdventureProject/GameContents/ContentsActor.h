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


// Ό³Έν :
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

private:

};

