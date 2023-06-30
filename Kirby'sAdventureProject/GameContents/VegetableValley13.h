#pragma once
#include "VegetableValleyPlayLevel.h"

// Ό³Έν :
class VegetableValley13 : public VegetableValleyPlayLevel
{
public:
	static bool IsEndingCreditOn;

public:
	// constrcuter destructer
	VegetableValley13();
	~VegetableValley13();

	// delete Function
	VegetableValley13(const VegetableValley13& _Other) = delete;
	VegetableValley13(VegetableValley13&& _Other) noexcept = delete;
	VegetableValley13& operator=(const VegetableValley13& _Other) = delete;
	VegetableValley13& operator=(VegetableValley13&& _Other) noexcept = delete;

protected:

private:
	void EndingCredit();


	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
};
