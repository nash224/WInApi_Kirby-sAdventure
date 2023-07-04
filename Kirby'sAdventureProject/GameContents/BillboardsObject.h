#pragma once
#include <GameEngineCore/GameEngineActor.h>


// 설명 : 전광판입니다. 
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

	// 외부) init
	void StageOneBillBoardinit(const float4& _StageOneBillBoardPos);
	void StageBossBillBoardinit(const float4& _StageBossBillBoardPos);

protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;


	// 렌더
	GameEngineRenderer* StageOne_BillBoard = nullptr;
	GameEngineRenderer* StageBoss_BillBoard = nullptr;

public:
	// 디버깅용 스위치 렌더
	void SwitchEffect();

};

