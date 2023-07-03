#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BillboardsObject : public GameEngineActor
{
	friend class VegetableValleyHub;
public:
	// constrcuter destructer
	BillboardsObject();
	~BillboardsObject();

	// delete Function
	BillboardsObject(const BillboardsObject& _Other) = delete;
	BillboardsObject(BillboardsObject&& _Other) noexcept = delete;
	BillboardsObject& operator=(const BillboardsObject& _Other) = delete;
	BillboardsObject& operator=(BillboardsObject&& _Other) noexcept = delete;


	void StageOneBillBoardinit(const float4& _StageOneBillBoardPos);
	void StageBossBillBoardinit(const float4& _StageBossBillBoardPos);

protected:
	GameEngineRenderer* StageOne_BillBoard = nullptr;
	GameEngineRenderer* StageBoss_BillBoard = nullptr;

private:

	void Start() override;
	void Update(float _Delta) override;



public:
	void SwitchEffect();

};

