#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class VegetableValleyIntro : public GameEngineLevel
{
public:
	// constrcuter destructer
	VegetableValleyIntro();
	~VegetableValleyIntro();

	// delete Function
	VegetableValleyIntro(const VegetableValleyIntro& _Other) = delete;
	VegetableValleyIntro(VegetableValleyIntro&& _Other) noexcept = delete;
	VegetableValleyIntro& operator=(const VegetableValleyIntro& _Other) = delete;
	VegetableValleyIntro& operator=(VegetableValleyIntro&& _Other) noexcept = delete;

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

