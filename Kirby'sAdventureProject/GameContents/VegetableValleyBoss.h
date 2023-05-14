#pragma once

// Ό³Έν :
class VegetableValleyBoss
{
public:
	// constrcuter destructer
	VegetableValleyBoss();
	~VegetableValleyBoss();

	// delete Function
	VegetableValleyBoss(const VegetableValleyBoss& _Other) = delete;
	VegetableValleyBoss(VegetableValleyBoss&& _Other) noexcept = delete;
	VegetableValleyBoss& operator=(const VegetableValleyBoss& _Other) = delete;
	VegetableValleyBoss& operator=(VegetableValleyBoss&& _Other) noexcept = delete;

protected:

private:

};

