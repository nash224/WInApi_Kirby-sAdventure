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

private:
	// GameEngineObject ���
	void Start() override;
	void Update(float _Delta) override;


	// GameEngineLevel ���
	void LevelStart(GameEngineLevel* _PrevLevel) override;


	// this
	class VegetableValleyCutScene* LevelScene = nullptr;

};

