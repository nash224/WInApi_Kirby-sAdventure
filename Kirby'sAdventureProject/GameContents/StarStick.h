#pragma once
#include "Item.h"

#include <GameEngineCore/GameEngineRenderer.h>


enum class StarStickState
{
	BounceOff,
	Floating,
	Max,
};

// ���� :
class StarStick : public Item
{
public:
	// constrcuter destructer
	StarStick();
	~StarStick();

	// delete Function
	StarStick(const StarStick& _Other) = delete;
	StarStick(StarStick&& _Other) noexcept = delete;
	StarStick& operator=(const StarStick& _Other) = delete;
	StarStick& operator=(StarStick&& _Other) noexcept = delete;

	void init(const float4& _StartPos, const float4& _TargetPos);

protected:


private:
	// GameEngineObject ���
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;



	// this
	GameEngineRenderer* HaloEffectRenderer = nullptr;


	// FSM 
	StarStickState State = StarStickState::Max;

	void StateUpdate(float _Delta);
	void ChangeState(StarStickState _State);


	// ��������
	void BounceOffStart();
	void BounceOffUpdate(float _Delta);


	// BounceOff Pettern
	float4 TargetPos = float4::ZERO;
	float4 TargetMovePos = float4::ZERO;
	float4 Target_UnitVector = float4::ZERO;
	float4 Target_TotalDecelection_UnitVector = float4::ZERO;
	float Target_Distance = 0.0f;


	// Floating Pettern
	void FloatingStart();
	void FloatingUpdate(float _Delta);

	bool IsChangeReverseDir = false;
	float ChangePosTime = 0.0f;
	float Center_Origin_YPos = 0.0f;
	const float ChangePosCycle = 0.1f;
	const float LimitHeight_ToCenter = 30.0f;
	const float OneTime_Move_HeightDistance = 3.0f;



	// �浹 
	void ItemReachedState() override;


	// �����
	void ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);
};

