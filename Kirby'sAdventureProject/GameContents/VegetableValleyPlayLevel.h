#pragma once
#include <GameEngineCore/GameEngineLevel.h>

#include "Enemy.h"

// 페이드 아웃 지속시간
#define FADEOUT_ENDTIME 0.2f
// 커비 Enter 시간
#define KIRBY_ENTERSTATETIME 0.2f


// 설명 :
class VegetableValleyPlayLevel : public GameEngineLevel
{

public:
	static bool NextLevelTriggerOn;
	static bool IsStageEnd;

	static bool IsPlayerEnter;
	static float FadeTime;
	static float KirbyStateTime;


protected:
	static int VegetableValleyEntertheDoorNumber;

	static float UpdateTime;
	float FPSText = 0.0f;

public:
	// constrcuter destructer
	VegetableValleyPlayLevel();
	~VegetableValleyPlayLevel();

	// delete Function
	VegetableValleyPlayLevel(const VegetableValleyPlayLevel& _Other) = delete;
	VegetableValleyPlayLevel(VegetableValleyPlayLevel&& _Other) noexcept = delete;
	VegetableValleyPlayLevel& operator=(const VegetableValleyPlayLevel& _Other) = delete;
	VegetableValleyPlayLevel& operator=(VegetableValleyPlayLevel&& _Other) noexcept = delete;

	size_t GetLevelEnemyCount() const
	{
		return LevelEnemy.size();
	}

	float4 GetLevelBackgroundScale() const
	{
		return BackGroundScale;
	}

	std::string GetLevelBitMapFileName() const
	{
		return BitMapFileName;
	}


protected:
	class UIManager* LevelUIManager = nullptr;
	class BackGround* LevelBackGround = nullptr;
	class GameEffect* LevelEffect = nullptr;
	class Kirby* LevelPlayer = nullptr;

	

	std::map<std::string, Enemy*> LevelEnemy;
	std::string BitMapFileName = "";

	float4 BackGroundScale = float4::ZERO;



	void SetLevelBackgroundScale(const float4& _Scale)
	{
		BackGroundScale = _Scale;
	}



	virtual void EnemySummon() {}
	void CheckRespawnEnemy();

	void CreateAndSetupBackgroundEffectRenderer(
		const std::string& _AnimationName,
		const std::string& _FileName,
		int _StartFrame, int _EndFrame,
		float4 _Pos, float _Ratio,
		float _Inter = 0.1f, bool _Loop = true);

private:

};

