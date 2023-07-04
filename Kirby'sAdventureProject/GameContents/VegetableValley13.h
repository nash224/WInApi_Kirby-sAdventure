#pragma once
#include "ContentsLevelBossStage.h"

// 설명 : 보스 스테이지 이자, 마지막 스테이지 입니다. 
class VegetableValley13 : public ContentsLevelBossStage
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
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// GameEngineLevel 상속
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;


	// ContentsLevelBossStage 상속
	void SwitchRenders() override;




	// this
	// 리소스 로드
	void ResourcesLoad();

	// 레벨 이동
	void PlayerMissPrevLevel();



	// EndingCredit 패턴
	bool Ending_IsFadeOut = false;
	const float4 PlankPos = float4{ 600.0f , 621.0f };


	void EndingCredit(float _Delta);

};
