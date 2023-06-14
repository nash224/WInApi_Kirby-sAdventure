#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class PlayUIManager : public GameEngineActor
{
public:
	static PlayUIManager* UI;

public:
	// constrcuter destructer
	PlayUIManager();
	~PlayUIManager();

	// delete Function
	PlayUIManager(const PlayUIManager& _Other) = delete;
	PlayUIManager(PlayUIManager&& _Other) noexcept = delete;
	PlayUIManager& operator=(const PlayUIManager& _Other) = delete;
	PlayUIManager& operator=(PlayUIManager&& _Other) noexcept = delete;

	void init(const std::string& _FileName, const std::string& _Path);

	float4 UIScale = float4::ZERO;

protected:
	GameEngineRenderer* MainUIRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

private:

};

