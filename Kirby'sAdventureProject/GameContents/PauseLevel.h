#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class PauseLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PauseLevel();
	~PauseLevel();

	// delete Function
	PauseLevel(const PauseLevel& _Other) = delete;
	PauseLevel(PauseLevel&& _Other) noexcept = delete;
	PauseLevel& operator=(const PauseLevel& _Other) = delete;
	PauseLevel& operator=(PauseLevel&& _Other) noexcept = delete;

protected:

private:
	class Player* LevelPlayer = nullptr;
	class BackGround* LevelBackGround = nullptr;

	void Start() override;
	void Update(float _Delta) override;

};

