#pragma once
#include "VegetableValleyPlayLevel.h"

#include <GameEnginePlatform/GameEngineSound.h>

// ErrorCode : C2504 : Ŭ������ ������ �� �⺻ Ŭ������ �������� ������ �߻���
// �θ� ����� �߰������� �ʾ���
// ���� :
class TitleLevel : public VegetableValleyPlayLevel
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

	// GameEngineObject ���
private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _Delta) override;

	// GameEngineLevel ���
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;


	//this
private:
	void ResourcesLoad();

};

