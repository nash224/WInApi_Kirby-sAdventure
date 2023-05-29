#pragma once

// Ό³Έν :
class MrFrosty
{
public:
	// constrcuter destructer
	MrFrosty();
	~MrFrosty();

	// delete Function
	MrFrosty(const MrFrosty& _Other) = delete;
	MrFrosty(MrFrosty&& _Other) noexcept = delete;
	MrFrosty& operator=(const MrFrosty& _Other) = delete;
	MrFrosty& operator=(MrFrosty&& _Other) noexcept = delete;

protected:

private:

};

