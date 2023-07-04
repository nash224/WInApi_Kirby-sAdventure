#pragma once
#include "VegetableValleyPlayLevel.h"

#include <GameEnginePlatform/GameEngineSound.h>

// ErrorCode : C2504 : 클래스를 지정할 때 기본 클래스가 지정되지 않으면 발생함
// 부모 헤더를 추가해주지 않았음
// 설명 :
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

	// GameEngineObject 상속
private:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _Delta) override;

	// GameEngineLevel 상속
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;


	//this
private:
	void ResourcesLoad();

};

