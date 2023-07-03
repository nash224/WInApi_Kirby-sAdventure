#pragma once
#include "VegetableValleyPlayLevel.h"

// 설명 :
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
	// EndingCredit 관련
	bool Ending_IsFadeOut = false;

	void EndingCredit(float _Delta);

	const float4 PlankPos = float4{ 600.0f , 621.0f };


	void Start() override;



	void Update(float _Delta) override;

	void PlayerMissPrevLevel();


	void Render(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;


	void SwitchRenders() override;
};
