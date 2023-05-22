#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class EndingLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	EndingLevel();
	~EndingLevel();

	// delete Function
	EndingLevel(const EndingLevel& _Other) = delete;
	EndingLevel(EndingLevel&& _Other) noexcept = delete;
	EndingLevel& operator=(const EndingLevel& _Other) = delete;
	EndingLevel& operator=(EndingLevel&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	class Kirby* LevelPlayer = nullptr;
	class BackGround* LevelBackGround = nullptr;
	GameEngineRenderer* BackRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};