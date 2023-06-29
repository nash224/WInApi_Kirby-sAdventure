#pragma once
#include "VegetableValleyPlayLevel.h"

// ���� :
class VegetableValleyIntro : public VegetableValleyPlayLevel
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
	class BackGround* LevelBackGround = nullptr;
	class VegetableValleyCutScene* LevelScene = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};

