#pragma once
#include <GameEngineCore/GameEngineLevel.h>


// 설명 : 정지하는 기능이지만 사용하지 않습니다.
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

	// GameEngineObject 상속
private:
	void Start() override;
	void Update(float _Delta) override;




	// this
private:
	class Player* LevelPlayer = nullptr;
	class BackGround* LevelBackGround = nullptr;


};

