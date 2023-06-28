#pragma once
#include "ActorUtils.h"



// 흡입 상태에 관한 상수
#define INHALETIME 0.3f
#define INHALEXPOWER 200.0f


// 커비 입 높이
#define KIRBYCENTERYPOINT 15.0f


enum class ItemState
{
	Idle,
	BounceOff,
	BeInhaled,
	Max,
};



// 설명 :
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



	// 외부에서 텍스처 맵을 지정하는 함수
	void SetGroundTexture(const std::string& _GroundTextureName);




protected:
	float4 Scale = float4::ZERO;




	// 상태 함수
	std::string CurState = "";
	ItemState State = ItemState::Max;

	void StateUpdate(float _Delta);
	void ChangeState(ItemState _State);
	void ChangeAnimationState(const std::string& _StateName);



	float4 ActorDirUnitVector = float4::ZERO;
	float4 GetKirbyOpponentDistance();




	virtual void IdleStart() {}
	virtual void BounceOffStart() {}

	virtual void IdleUpdate(float _Delta) {}
	virtual void BounceOffUpdate(float _Delta) {}


	virtual void BeInhaledStart() {}
	virtual void BeInhaledUpdate(float _Delta) {}


	float4 InhaleTargetPos = float4::ZERO;
	float InhaleTargetPosYDistance = 0.0f;
	float InhaleTargetPosXDistance = 0.0f;


	// 충돌 관련
	int ItemNumber = -1;

	bool IsReached = false;

	void ItemCollisionCheck();
	virtual void ItemReachedState() {}


public:
	// 포인터 해제
	void ItemPointerRelease();
	void ObjectPointerRelease();

};

