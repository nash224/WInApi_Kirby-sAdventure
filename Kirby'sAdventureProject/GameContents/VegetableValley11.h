#pragma once
#include "VegetableValleyPlayLevel.h"

// Ό³Έν :
class VegetableValley11 : public VegetableValleyPlayLevel
{
public:
	// constrcuter destructer
	VegetableValley11();
	~VegetableValley11();

	// delete Function
	VegetableValley11(const VegetableValley11& _Other) = delete;
	VegetableValley11(VegetableValley11&& _Other) noexcept = delete;
	VegetableValley11& operator=(const VegetableValley11& _Other) = delete;
	VegetableValley11& operator=(VegetableValley11&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void VegetableValley11BackGroundEffect(float _Ratio, float _Inter, bool _Loop);
};

