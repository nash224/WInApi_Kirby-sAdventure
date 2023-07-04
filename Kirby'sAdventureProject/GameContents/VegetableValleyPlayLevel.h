#pragma once
#include <GameEngineCore/GameEngineLevel.h>

#include <GameEnginePlatform/GameEngineSound.h>


#include <vector>


// 사운드 볼륨 최대
#define MAX_VOLUME_AMOUNT 1.0f


// 설명 : Contents Level 의 부모입니다. 자식 레벨에게 필요한 기능을 제공해줍니다.
class BackGround;
class Enemy;
class VegetableValleyPlayLevel : public GameEngineLevel
{
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


	void SetLevelBackgroundScale(const float4& _Scale)
	{
		BackGroundScale = _Scale;
	}

	float4 GetLevelBackgroundScale() const
	{
		return BackGroundScale;
	}


	std::string GetLevelBitMapFileName() const
	{
		return BitMapFileName;
	}


	class UIManager* GetUIManager()
	{
		return LevelUIManager;
	}


	BackGround* GetLevelBackGroundPtr()
	{
		return LevelBackGround;
	}





protected:
	// BackGround
	BackGround* LevelBackGround = nullptr;
	std::string BitMapFileName = "";
	float4 BackGroundScale = float4::ZERO;



	// Map Effect
	class GameEffect* LevelEffect = nullptr;

	void CreateAndSetupBackgroundEffectRenderer(
		const std::string& _AnimationName,
		const std::string& _FileName,
		int _StartFrame, int _EndFrame,
		float4 _Pos, float _Ratio,
		float _Inter = 0.1f, bool _Loop = true);


	// UI
	class UIManager* LevelUIManager = nullptr;


public:
	// Level Change
	static bool PrevLevelTriggerOn;
	static bool NextLevelTriggerOn;
	static bool IsStageEnd;
	static bool IsPlayerEnter;
	static bool IsPlayerMiss;
	static bool IsChangeLevel;
	static bool IsFadeDone;

	static bool ChangeClearDoor;

protected:
	bool IsPrevLeveling = false;
	bool IsNextLeveling = false;





public:
	// Unit
	// Player
	float4 Kirby_RespawnPos = float4::ZERO;

protected:
	class Kirby* LevelPlayer = nullptr;



	// Enemy
	std::vector<Enemy*> LevelEnemy;

	virtual void EnemySummon() {}


	// Enemy::Respawn
	void SetPlayerPosAndCameraPos(const float4& _PlayerPos, const float4& _CameraPos);
	void CheckRespawnEnemy();



	// BGM
public:
	static GameEngineSoundPlayer BGM_Player;
	static float SoundVol;
	static bool IsBGM_On;
	static std::string BGMFileName;
	std::string LevelBgmFileName = "";

private:
	float SoundVolPressKeyTime = 0.0f;
	const float SoundVol_OneTime_AmountOfChange = 0.05f;
	const float SoundVol_KeyDownCycle = 0.2f;

	void RePlayBGM();





protected:
	// Camera
	float4 CameraFrontCheckPos = float4::ZERO;
	float4 CameraBackCheckPos = float4::ZERO;


	void CameraFocus(float _Delta);


public:
	// 카메라 지진
	static int Camera_ShakeCount;

	static void RequestShakeCountToLevel(size_t _Value = 1)
	{
		for (size_t i = 0; i < _Value; i++)
		{
			++Camera_ShakeCount;
		}
	}

	static void RequestShakeMagnitudeToLevel(float _Value = 3.0f)
	{
		Camera_ShakeMagnitude = _Value;
	}

private:
	static float Camera_ShakeMagnitude;
	int Camera_ShakeNumber = 0;

	const float Camera_ShakeCycle = 0.04f;
	float Camera_ShakeTime = 0.0f;



public:
	// 디버그
	void LevelDebugShortcut(float _Delta);


	static bool Level_MenuOpenValue;
	static bool Level_SwitchBitMapRenderValue;
	static bool Level_DebugRenderValue;

protected:
	void DebugRender(float _Delta);
	void OpenMenuRender(HDC _HDC, int& _RenderNumber);
	void DevModeRender(HDC _HDC, int& _RenderNumber, float _Delta);
	void ColAndBitMapRender(HDC _HDC, int& _RenderNumber);

	virtual void SwitchRenders() {}


	static int Level_DebugRenderXPos;
	const int DebugRenderText_YInter = 18;

	float FPSText = 0.0f;
	static float UpdateTime;


	std::string NextLevelName = "";
	float4 KirbyShortCutPos = float4::ZERO;


};

