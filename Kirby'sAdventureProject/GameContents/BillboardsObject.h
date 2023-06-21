#pragma once

// Ό³Έν :
class BillboardsObject
{
public:
	// constrcuter destructer
	BillboardsObject();
	~BillboardsObject();

	// delete Function
	BillboardsObject(const BillboardsObject& _Other) = delete;
	BillboardsObject(BillboardsObject&& _Other) noexcept = delete;
	BillboardsObject& operator=(const BillboardsObject& _Other) = delete;
	BillboardsObject& operator=(BillboardsObject&& _Other) noexcept = delete;

protected:

private:

};

