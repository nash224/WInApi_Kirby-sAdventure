#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class VegetableValley12 : public GameEngineLevel
{
public:
	// constrcuter destructer
	VegetableValley12();
	~VegetableValley12();

	// delete Function
	VegetableValley12(const VegetableValley12& _Other) = delete;
	VegetableValley12(VegetableValley12&& _Other) noexcept = delete;
	VegetableValley12& operator=(const VegetableValley12& _Other) = delete;
	VegetableValley12& operator=(VegetableValley12&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	class Kirby* LevelPlayer = nullptr;
	class BackGround* LevelBackGround = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;

};

