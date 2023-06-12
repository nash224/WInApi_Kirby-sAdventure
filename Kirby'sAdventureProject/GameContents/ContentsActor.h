#pragma once
#include <GameEngineCore/GameEngineActor.h>


enum class ActorDir
{
	Right,
	Left,
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
	ActorDir Dir = ActorDir::Max;

private:

};

