#pragma once
#include "VegetableValleyPlayLevel.h"

// Ό³Έν :
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

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	const float4 KirbyRespawnLocation = float4{ 648.0f , 456.0f };

};

