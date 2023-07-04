#pragma once
#include <GameEngineCore/GameEngineLevel.h>


// ���� : �����ϴ� ��������� ������� �ʽ��ϴ�.
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

	// GameEngineObject ���
private:
	void Start() override;
	void Update(float _Delta) override;




	// this
private:
	class Player* LevelPlayer = nullptr;
	class BackGround* LevelBackGround = nullptr;


};

