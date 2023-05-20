#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ActorUtils : public GameEngineActor
{
public:
	// constrcuter destructer
	ActorUtils();
	~ActorUtils();

	// delete Function
	ActorUtils(const ActorUtils& _Other) = delete;
	ActorUtils(ActorUtils&& _Other) noexcept = delete;
	ActorUtils& operator=(const ActorUtils& _Other) = delete;
	ActorUtils& operator=(ActorUtils&& _Other) noexcept = delete;

	void CameraFocus();
	void SetGroundTexture(const std::string& _GroundTextureName);
	int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);


	void Gravity(float _Delta);

	void GravityReset()
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
	void GroundCheck(float _XScaleSize);

	bool GetGroundState() const
	{
		return isGround;
	}

private:
	class GameEngineWindowTexture* GroundTexture = nullptr;

	bool isGround = false;
	bool IsGravity = true;
	float GravityPower = 0.8f;
	float4 GravityVector = float4::ZERO;


};

