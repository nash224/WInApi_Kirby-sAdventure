#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ContentUtils : public GameEngineActor
{
public:
	// constrcuter destructer
	ContentUtils();
	~ContentUtils();

	// delete Function
	ContentUtils(const ContentUtils& _Other) = delete;
	ContentUtils(ContentUtils&& _Other) noexcept = delete;
	ContentUtils& operator=(const ContentUtils& _Other) = delete;
	ContentUtils& operator=(ContentUtils&& _Other) noexcept = delete;

	void CameraFocus();
	void SetGroundTexture(const std::string& _GroundTextureName);


	void Gravity();

	void GraviyReset()
	{
		GravityVector = float4::ZERO;
	}

	void GravityOn()
	{
		IsGravity = true;
	}

	void GravityOff()
	{
		IsGravity = false;
	}


protected:

private:
	class GameEngineWindowTexture* GroundTexture = nullptr;

	bool IsGravity = true;
	float GravityPower = 1.f;
	float4 GravityVector = float4::ZERO;


};

