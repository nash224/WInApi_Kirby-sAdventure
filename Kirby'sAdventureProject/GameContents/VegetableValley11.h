#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include "Enemy.h"

// Ό³Έν :
class VegetableValley11 : public GameEngineLevel
{
private:
	static float UpdateTime;
	float FPSText = 0.0f;

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
	std::map<std::string, Enemy*> LevelEnemy;

	class Kirby* LevelPlayer = nullptr;
	class BackGround* LevelBackGround = nullptr;
	class GameEffect* LevelEffect = nullptr;

	float4 BackGroundScale = float4::ZERO;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;



	void VegetableValley11BackGroundEffect(float _Ratio, float _Inter, bool _Loop);
	void CreateAndSetupBackgroundEffectRenderer(
		const std::string& _AnimationName,
		const std::string& _FileName,
		int _StartFrame, int _EndFrame,
		float4 _Pos, float _Ratio,
		float _Inter = 0.1f, bool _Loop = true);
};

