#pragma once
#include "ContentsLevelBossStage.h"

// ���� : ���� �������� ����, ������ �������� �Դϴ�. 
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
	// GameEngineObject ���
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// GameEngineLevel ���
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;


	// ContentsLevelBossStage ���
	void SwitchRenders() override;




	// this
	// ���ҽ� �ε�
	void ResourcesLoad();

	// ���� �̵�
	void PlayerMissPrevLevel();



	// EndingCredit ����
	bool Ending_IsFadeOut = false;
	const float4 PlankPos = float4{ 600.0f , 621.0f };


	void EndingCredit(float _Delta);

};
