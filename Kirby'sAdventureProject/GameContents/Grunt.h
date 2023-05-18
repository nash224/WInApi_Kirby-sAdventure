#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <list>

// Ό³Έν :
class Grunt : public GameEngineActor
{
private: 
	static std::list<Grunt*> AllGrunt;

public:
	static void AllMonsterDeath();

public:
	// constrcuter destructer
	Grunt();
	~Grunt();

	// delete Function
	Grunt(const Grunt& _Other) = delete;
	Grunt(Grunt&& _Other) noexcept = delete;
	Grunt& operator=(const Grunt& _Other) = delete;
	Grunt& operator=(Grunt&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

};

