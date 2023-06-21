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

	//void DoorRender();


	const float4 OneStageLocation = float4{ 288.0f , 863.0f };
	const float4 OneStageBillBoardLocation = float4{ 228.0f , 813.0f };


	

	void Start() override;
	void Update(float _Delta) override;
};

