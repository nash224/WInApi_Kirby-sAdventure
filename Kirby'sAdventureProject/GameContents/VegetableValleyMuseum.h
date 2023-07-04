#pragma once
#include "VegetableValleyPlayLevel.h"

// 설명 :
class VegetableValleyMuseum : public VegetableValleyPlayLevel
{
public:
	// constrcuter destructer
	VegetableValleyMuseum();
	~VegetableValleyMuseum();

	// delete Function
	VegetableValleyMuseum(const VegetableValleyMuseum& _Other) = delete;
	VegetableValleyMuseum(VegetableValleyMuseum&& _Other) noexcept = delete;
	VegetableValleyMuseum& operator=(const VegetableValleyMuseum& _Other) = delete;
	VegetableValleyMuseum& operator=(VegetableValleyMuseum&& _Other) noexcept = delete;

protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// GameEngineLevel 상속
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;



	// this
	void ResourcesLoad();
	void PlayerEnterNextLevel();





private:
	const float4 KirbyRespawnLocation = float4{ 648.0f , 456.0f };

	void SwitchRenders() override;

};

