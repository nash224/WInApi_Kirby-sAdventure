#pragma once
#include "VegetableValleyPlayLevel.h"


// 설명 : 단순히 설명을 띄우는 Level입니다.
class SubScreens : public VegetableValleyPlayLevel
{
public:
	// constrcuter destructer
	SubScreens();
	~SubScreens();

	// delete Function
	SubScreens(const SubScreens& _Other) = delete;
	SubScreens(SubScreens&& _Other) noexcept = delete;
	SubScreens& operator=(const SubScreens& _Other) = delete;
	SubScreens& operator=(SubScreens&& _Other) noexcept = delete;

protected:

	// GameEngineObject 상속
private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	// GameEngineLevel 상속
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

};

