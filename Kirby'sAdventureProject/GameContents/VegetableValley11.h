#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class VegetableValley11 : public GameEngineLevel
{
public:
	// constrcuter destructer
	VegetableValley11();
	~VegetableValley11();

	// delete Function
	VegetableValley11(const VegetableValley11& _Other) = delete;
	VegetableValley11(VegetableValley11&& _Other) noexcept = delete;
	VegetableValley11& operator=(const VegetableValley11& _Other) = delete;
	VegetableValley11& operator=(VegetableValley11&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	class Player* LevelPlayer = nullptr;
	class BackGround* LevelBackGround = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};

