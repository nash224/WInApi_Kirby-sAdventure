#pragma once
#include "GameEngineObject.h"

#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>

#include <string>

// Ό³Έν :
class GameEngineActor;
class GameEngineRenderer : public GameEngineObject
{
	friend class GameEngineActor;
	friend class GameEngineCamera;
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	void SetTexture(const std::string& _Name);
	void SetRenderScaleToTexture();



	void SetCopyPos(const float4& _Value)
	{
		CopyPos = _Value;
	}

	void SetCopyScale(const float4& _Value)
	{
		CopyScale = _Value;
	}

	void SetRenderPos(const float4& _Value)
	{
		RenderPos = _Value;
	}

	void SetRenderScale(const float4& _Value)
	{
		RenderScale = _Value;
		ScaleCheck = true;
	}

	

protected:

private:
	GameEngineWindowTexture* Texture = nullptr;
	GameEngineActor* Master = nullptr;
	bool ScaleCheck = false;
	
	float4 CopyPos;
	float4 CopyScale;

	float4 RenderPos;
	float4 RenderScale;

	void Render(class GameEngineCamera* _Camera);
};

