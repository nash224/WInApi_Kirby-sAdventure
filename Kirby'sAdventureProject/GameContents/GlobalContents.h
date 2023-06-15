#pragma once
#include <string>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineSprite.h>

// Ό³Έν :
class GlobalContents
{
public:
	// constrcuter destructer
	GlobalContents();
	~GlobalContents();

	// delete Function
	GlobalContents(const GlobalContents& _Other) = delete;
	GlobalContents(GlobalContents&& _Other) noexcept = delete;
	GlobalContents& operator=(const GlobalContents& _Other) = delete;
	GlobalContents& operator=(GlobalContents&& _Other) noexcept = delete;

	static GameEngineWindowTexture* TextureFileLoad(const std::string& _FileName, const std::string& _Path);
	static void SpriteFileLoad(const std::string& _FileName, const std::string& _Path, int _XCount, int _YCount);

protected:

private:

};