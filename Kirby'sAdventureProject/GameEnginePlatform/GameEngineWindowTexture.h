#pragma once
#include <GameEngineBase/GameEngineMath.h>

#include <string>
#include <Windows.h>

// Ό³Έν :
class GameEngineWindowTexture
{
public:
	// constrcuter destructer
	GameEngineWindowTexture();
	~GameEngineWindowTexture();

	// delete Function
	GameEngineWindowTexture(const GameEngineWindowTexture& _Other) = delete;
	GameEngineWindowTexture(GameEngineWindowTexture&& _Other) noexcept = delete;
	GameEngineWindowTexture& operator=(const GameEngineWindowTexture& _Other) = delete;
	GameEngineWindowTexture& operator=(GameEngineWindowTexture&& _Other) noexcept = delete;

	void ResLoad(const std::string& _FilePath);
	void ResCreate(HDC _ImageDC)
	{
		ImageDC = _ImageDC;
		ScaleCheck();
	}

	void ResCreate(const float4& _Scale);

	HDC GetImageDC() const
	{
		return ImageDC;
	}

	float4 GetScale() const
	{
		return { static_cast<float>(Info.bmWidth), static_cast<float>(Info.bmHeight) };
	}

	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos);
	void BitCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale);

	void TransCopy(GameEngineWindowTexture* _CopyTexture, const float4& _Pos, const float4& _Scale, 
		const float4& _OtherPos, const float4& _OtherScale, int _TransColor = RGB(255,0,255));


protected:

private:
	HBITMAP BitMap = nullptr;
	HBITMAP OldBitMap = nullptr;
	HDC ImageDC = nullptr;
	BITMAP Info = {0};

	

	void ScaleCheck();
};

