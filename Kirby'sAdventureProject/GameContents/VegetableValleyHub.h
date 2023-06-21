#pragma once
#include "VegetableValleyPlayLevel.h"

// Ό³Έν :
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

	//void DoorRender();


	const float4 StageOneLocation = float4{ 288.0f , 865.0f };
	const float4 StageTwoLocation = float4{ 720.0f , 961.0f };
	const float4 StageOneBillBoardLocation = float4{ 288.0f , 813.0f };
	const float4 StageBossBillBoardLocation = float4{ 720.0f , 909.0f };

	



private:
	void Start() override;
	void Update(float _Delta) override;


};

