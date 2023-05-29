#pragma once

// Ό³Έν :
class Togezo
{
public:
	// constrcuter destructer
	Togezo();
	~Togezo();

	// delete Function
	Togezo(const Togezo& _Other) = delete;
	Togezo(Togezo&& _Other) noexcept = delete;
	Togezo& operator=(const Togezo& _Other) = delete;
	Togezo& operator=(Togezo&& _Other) noexcept = delete;

protected:

private:

};

