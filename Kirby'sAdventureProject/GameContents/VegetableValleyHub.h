#pragma once
#include "VegetableValleyPlayLevel.h"


// 설명 : VegetableValley 버스형 스테이지 파이프입니다.
class VegetableValleyHub : public VegetableValleyPlayLevel
{
public:
	// constrcuter destructer
	VegetableValleyHub();
	~VegetableValleyHub();

	// delete Function
	VegetableValleyHub(const VegetableValleyHub& _Other) = delete;
	VegetableValleyHub(VegetableValleyHub&& _Other) noexcept = delete;
	VegetableValleyHub& operator=(const VegetableValleyHub& _Other) = delete;
	VegetableValleyHub& operator=(VegetableValleyHub&& _Other) noexcept = delete;



protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// GameEngineObject override
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;


	// VegetableValleyPlayLevel override
	void SwitchRenders() override;


private:
	// this
	void ResourecsLoad();

	// 사물
	class StageElemnet
	{
	public:
		bool IsStageClear = false;
		float4 StageLocation = float4::ZERO;
		float4 BillBoardLocation = float4::ZERO;
		class DoorObject* DoorPtr = nullptr;
		class Flag* FlagPtr = nullptr;
	};


	StageElemnet Stage1;
	StageElemnet Stage2;
	StageElemnet Museum;

	class BillboardsObject* VegetableValley_Billboard = nullptr;
	const float4 StageDoorSize = float4{ 48.0f , 48.0f };



	// Stage 패턴
	bool IsRequestDoorOpen = false;


	void Kirby_StageClear();

	void VegetableValleyStage_1_Func();
	void VegetableValleyStage_2_Func();
	void VegetableValleyMuseum_Func();


	// LevelStart
	int VegetableValleyEntertheDoorNumber = -1;
	bool AreYouJustEnterScene = true;

	void LevelStartCameraPos();
	void LevelStartDoorLogic();
};

