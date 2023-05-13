#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class VegetableValley2 : public GameEngineLevel
{
public:
	// constrcuter destructer
	VegetableValley2();
	~VegetableValley2();

	// delete Function
	VegetableValley2(const VegetableValley2& _Other) = delete;
	VegetableValley2(VegetableValley2&& _Other) noexcept = delete;
	VegetableValley2& operator=(const VegetableValley2& _Other) = delete;
	VegetableValley2& operator=(VegetableValley2&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;

};

