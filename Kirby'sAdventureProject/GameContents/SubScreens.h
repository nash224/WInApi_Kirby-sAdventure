#pragma once
#include "VegetableValleyPlayLevel.h"


// ���� : �ܼ��� ������ ���� Level�Դϴ�.
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

	// GameEngineObject ���
private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	// GameEngineLevel ���
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

};

