#pragma once
#include "VegetableValleyPlayLevel.h"


// Ό³Έν :
class ContentsLevelBossStage : public VegetableValleyPlayLevel
{
public:
	// constrcuter destructer
	ContentsLevelBossStage();
	~ContentsLevelBossStage();

	// delete Function
	ContentsLevelBossStage(const ContentsLevelBossStage& _Other) = delete;
	ContentsLevelBossStage(ContentsLevelBossStage&& _Other) noexcept = delete;
	ContentsLevelBossStage& operator=(const ContentsLevelBossStage& _Other) = delete;
	ContentsLevelBossStage& operator=(ContentsLevelBossStage&& _Other) noexcept = delete;


	class Boss* GetLevelBossPtr()
	{
		return LevelBoss;
	}



protected:
	class Boss* LevelBoss = nullptr;

private:

};

