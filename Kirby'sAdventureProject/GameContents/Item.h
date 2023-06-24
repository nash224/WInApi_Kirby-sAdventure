#pragma once
#include "ActorUtils.h"

// ���� :
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

protected:
	float4 Scale = float4::ZERO;



	// �浹 ����
	int ItemNumber = -1;

	bool IsReached = false;

	void ItemCollisionCheck();
	virtual void ItemReachedState() {}
	void ItemPointerRelease();

private:

};

