#pragma once
#include "VegetableValleyPlayLevel.h"





// 설명 :
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
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	class Kirby* LevelPlayer = nullptr;
	class BackGround* LevelBackGround = nullptr;

	class DoorObject* VegetableValley_Stage1_PlayDoor = nullptr;
	class DoorObject* VegetableValley_Stage1_BossDoor = nullptr;
	class DoorObject* VegetableValley_Museum_Door = nullptr;

	class BillboardsObject* VegetableValley_Billboard = nullptr;





	const float4 StageOneLocation = float4{ 288.0f , 865.0f };
	const float4 StageTwoLocation = float4{ 720.0f , 961.0f };
	const float4 StageOneBillBoardLocation = float4{ 288.0f , 813.0f };
	const float4 StageBossBillBoardLocation = float4{ 720.0f , 909.0f };

	

	// Stage 관련

	bool IsRequestDoorOpen = false;

	bool IsStage1Clear = false;
	bool IsStage2Clear = false;


	void VegetableValleyStage_1_Func();
	void VegetableValleyStage_2_Func();

	void Kirby_StageClear();





private:
	void Start() override;
	void Update(float _Delta) override;


};

