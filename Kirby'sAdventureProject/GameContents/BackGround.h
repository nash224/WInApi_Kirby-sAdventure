#pragma once
#include <GameEngineCore/GameEngineActor.h>

#include <string>

// Ό³Έν :
class BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	class GameEngineRenderer* Renderer = nullptr;

	void init(const std::string& _FileName, float4 _CopyPos, float4 _CopyScale);

protected:

private:
	std::string FileName = "";

	void Start() override;
	void Update(float _Delta) override;
	void Render() override;
	void Release() override;
};

