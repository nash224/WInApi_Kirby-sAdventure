#pragma once
#include "VegetableValleyPlayLevel.h"





// ���� :
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
	class Kirby* LevelPlayer = nullptr;
	class BackGround* LevelBackGround = nullptr;

	class BillboardsObject* VegetableValley_Billboard = nullptr;




	// Stage ����
	const float4 StageDoorSize = float4{ 48.0f , 48.0f };


	bool IsRequestDoorOpen = false;
	bool AreYouJustEnterScene = true;
	int VegetableValleyEntertheDoorNumber = -1;


	void VegetableValleyStage_1_Func();
	void VegetableValleyStage_2_Func();

	void Kirby_StageClear();


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




private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;


};

