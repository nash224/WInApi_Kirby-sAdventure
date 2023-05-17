#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
class GameEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	GameEffect();
	~GameEffect();

	// delete Function
	GameEffect(const GameEffect& _Other) = delete;
	GameEffect(GameEffect&& _Other) noexcept = delete;
	GameEffect& operator=(const GameEffect& _Other) = delete;
	GameEffect& operator=(GameEffect&& _Other) noexcept = delete;

protected:

private:
	std::string FileName = "";

	void Start() override;
	void Update(float _Delta) override;

};

