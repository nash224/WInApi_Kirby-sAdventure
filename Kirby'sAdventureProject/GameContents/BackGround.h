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

	void init(const std::string& _FileName, const std::string& _Path);
	void init(const std::string& _FileName, const std::string& _DebugFileName, const std::string& _Path);
	class GameEngineRenderer* SpriteInit(const std::string& _FileName, const std::string& _DebugFileName, const std::string& _Path, int _XCount, int _YCount);

	void SwitchRender();

protected:

private:
	bool SwitchRenderValue = true;
	std::string FileName = "";

	class GameEngineRenderer* Renderer = nullptr;
	class GameEngineRenderer* DebugRenderer = nullptr;

	void Start() override;
	void Update(float _Delta) override;
};

