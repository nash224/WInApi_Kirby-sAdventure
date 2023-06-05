#pragma once
#include "VegetableValleyPlayLevel.h"

// ���� :
class VegetableValley12 : public VegetableValleyPlayLevel
{
public:
	// constrcuter destructer
	VegetableValley12();
	~VegetableValley12();

	// delete Function
	VegetableValley12(const VegetableValley12& _Other) = delete;
	VegetableValley12(VegetableValley12&& _Other) noexcept = delete;
	VegetableValley12& operator=(const VegetableValley12& _Other) = delete;
	VegetableValley12& operator=(VegetableValley12&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:

	void Start() override;
	void Update(float _Delta) override;

};

