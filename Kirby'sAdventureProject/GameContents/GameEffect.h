#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : 배경의 숲풀이나 구름, 물의 흐름을 주기 위한 함수입니다.
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


	void SwitchEffect();

	void LoadBackGroundEffect(const std::string& _FileName, const std::string& _Path, int _XCount, int _YCount);

protected:

private:
	// GameEngineObject override;
	void Update(float _Delta) override;


};

