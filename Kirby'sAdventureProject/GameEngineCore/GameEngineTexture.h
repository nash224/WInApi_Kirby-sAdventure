#pragma once
#include <string>
#include <Windows.h>

// Ό³Έν :
class GameEngineTexture
{
public:
	// constrcuter destructer
	GameEngineTexture();
	~GameEngineTexture();

	// delete Function
	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

	void LoadResource(const std::string& _FilePath);

	HDC GetImageDC() const
	{
		return ImageDC;
	}


protected:

private:
	HBITMAP BitMap = nullptr;
	HBITMAP OldBitMap = nullptr;
	HDC ImageDC = nullptr;

	BITMAP Info = {0};

	void ScaleCheck();
};

