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
	class Kirby* LevelPlayer = nullptr;
	class BackGround* LevelBackGround = nullptr;
	class GameEffect* LevelEffect = nullptr;


	void Start() override;
	void Update(float _Delta) override;



	void VegetableValley11BackGroundEffect(float _Ratio, float _Inter, bool _Loop);
	void CreateAndSetupBackgroundEffectRenderer(
		const std::string& _AnimationName,
		const std::string& _FileName,
		int _StartFrame, int _EndFrame,
		float4 _Pos, float _Ratio,
		float _Inter = 0.1f, bool _Loop = true);
};

