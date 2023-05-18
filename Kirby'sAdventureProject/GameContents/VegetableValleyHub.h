#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class VegetableValleyHub : public GameEngineLevel
{
public:
	// constrcuter destructer
	VegetableValleyHub();
	~VegetableValleyHub();

	// delete Function
	VegetableValleyHub(const VegetableValleyHub& _Other) = delete;
	VegetableValleyHub(VegetableValleyHub&& _Other) noexcept = delete;
	VegetableValleyHub& operator=(const VegetableValleyHub& _Other) = delete;
	VegetableValleyHub& operator=(VegetableValleyHub&& _Other) noexcept = delete;

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

	void PushLevelPlayer(Player* _LevelPlayer);
};

