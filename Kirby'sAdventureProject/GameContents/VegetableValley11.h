#pragma once
#include "VegetableValleyPlayLevel.h"

// 설명 : 스테이지 1-1 레벨입니다.
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


private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	// GameEngineLevel 상속
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;


	// VegetableValleyPlayLevel 상속
	void EnemySummon() override;
	void SwitchRenders() override;



private:
	// this
	void ResourcesLoad();
	void VegetableValley11BackGroundEffect(float _Ratio, float _Inter, bool _Loop);



	void PlayerEnterNextLevel();
	void PlayerMissPrevLevel();

};

