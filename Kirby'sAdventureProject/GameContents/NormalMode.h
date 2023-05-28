#pragma once
#include "Kirby.h"

// Ό³Έν :
class NormalMode : public Kirby
{
public:
	// constrcuter destructer
	NormalMode();
	~NormalMode();

	// delete Function
	NormalMode(const NormalMode& _Other) = delete;
	NormalMode(NormalMode&& _Other) noexcept = delete;
	NormalMode& operator=(const NormalMode& _Other) = delete;
	NormalMode& operator=(NormalMode&& _Other) noexcept = delete;

protected:

private:

};

