#pragma once
#include "ActorUtils.h"


// Ŀ�� �� ����
#define KIRBYCENTERYPOINT 15.0f


enum class ItemState
{
	Idle,
	BounceOff,
	BeInhaled,
	Max,
};



// ���� : �������� �θ�Ŭ������ ���� Ŭ�������� �ʿ��� ����� �������ݴϴ�.
class Item : public ActorUtils
{
public:
	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;



	// �ܺο��� �ؽ�ó ���� �����ϴ� �Լ�
	void SetGroundTexture(const std::string& _GroundTextureName);




protected:
	float4 Scale = float4::ZERO;




	// FSM ����
	std::string CurState = "";
	ItemState State = ItemState::Max;

	void StateUpdate(float _Delta);
	void ChangeState(ItemState _State);
	void ChangeAnimationState(const std::string& _StateName);



	float4 GetKirbyOpponentDistance();
	float4 ActorDirUnitVector = float4::ZERO;



	virtual void IdleStart() {}
	virtual void IdleUpdate(float _Delta) {}

	virtual void BounceOffStart() {}
	virtual void BounceOffUpdate(float _Delta) {}


	virtual void BeInhaledStart() {}
	virtual void BeInhaledUpdate(float _Delta) {}

	const float InhaledTime = 0.3f;
	float4 InhaleTargetPos = float4::ZERO;
	float InhaleTargetPosYDistance = 0.0f;
	float InhaleTargetPosXDistance = 0.0f;


	// �浹 ����
	int ItemNumber = -1;

	bool IsReached = false;

	void ItemCollisionCheck();
	virtual void ItemReachedState() {}


public:
	// ������ ����
	void ItemPointerRelease();
	void ObjectPointerRelease();

};

