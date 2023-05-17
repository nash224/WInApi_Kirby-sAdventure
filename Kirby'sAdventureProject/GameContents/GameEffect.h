#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class BackgroundEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	BackgroundEffect();
	~BackgroundEffect();

	// delete Function
	BackgroundEffect(const BackgroundEffect& _Other) = delete;
	BackgroundEffect(BackgroundEffect&& _Other) noexcept = delete;
	BackgroundEffect& operator=(const BackgroundEffect& _Other) = delete;
	BackgroundEffect& operator=(BackgroundEffect&& _Other) noexcept = delete;

protected:

private:
	std::string FileName = "";

	void Start() override;
	void Update(float _Delta) override;

};

