#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
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


	GameEngineRenderer* init(const std::string& _FileName, const std::string& _Path, int _XCount, int _YCount);



protected:

private:
	GameEngineRenderer* EffectRenderer = nullptr;
	std::string FileName = "";

	void Start() override;
	void Update(float _Delta) override;

};

