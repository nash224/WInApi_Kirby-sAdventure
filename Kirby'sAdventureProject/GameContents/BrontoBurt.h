#pragma once

// Ό³Έν :
class BrontoBurt
{
public:
	// constrcuter destructer
	BrontoBurt();
	~BrontoBurt();

	// delete Function
	BrontoBurt(const BrontoBurt& _Other) = delete;
	BrontoBurt(BrontoBurt&& _Other) noexcept = delete;
	BrontoBurt& operator=(const BrontoBurt& _Other) = delete;
	BrontoBurt& operator=(BrontoBurt&& _Other) noexcept = delete;

protected:

private:

};

