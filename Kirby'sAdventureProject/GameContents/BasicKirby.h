#pragma once
#include "Kirby.h"

// Ό³Έν :
class BasicKirby : public Kirby
{
public:
	// constrcuter destructer
	BasicKirby();
	~BasicKirby();

	// delete Function
	BasicKirby(const BasicKirby& _Other) = delete;
	BasicKirby(BasicKirby&& _Other) noexcept = delete;
	BasicKirby& operator=(const BasicKirby& _Other) = delete;
	BasicKirby& operator=(BasicKirby&& _Other) noexcept = delete;

protected:

private:

};

