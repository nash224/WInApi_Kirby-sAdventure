#pragma once
#include <GameEnginePlatform/GameEngineSound.h>
#include <GameEngineCore/GameEngineLevel.h>

// ErrorCode : C2504 : Ŭ������ ������ �� �⺻ Ŭ������ �������� ������ �߻���
// �θ� ����� �߰������� �ʾ���
// ���� :
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer 
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:

private:
	class BackGround* LevelBackGround = nullptr;

	GameEngineSoundPlayer BGMPlayer;
	bool IsBGMOn = false;

	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

};

