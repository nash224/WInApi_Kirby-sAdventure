#pragma once
#include <GameEngineCore/GameEngineActor.h>


enum class ActorDir
{
	Right,
	Left,
	Max,
};


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
	GameEngineCollision* BodyCollision = nullptr;

	ActorDir Dir = ActorDir::Max;

	const float GravityMaxVector = 450.0f;


	void GroundCheck(float _XScaleSize);
	bool CheckLeftWall(const float4& _ScaleSize);
	bool CheckRightWall(const float4& _ScaleSize);

	void SetGravityVector(const float4& _GravityVector)
	{
		GravityVector = _GravityVector;
	}

	void AddGravityVector(const float _GravityPower, float _Delta)
	{
		GravityVector += float4::UP * _GravityPower * _Delta;
	}

	bool GetGroundState() const
	{
		return isGround;
	}

	float4 GetGravityVector() const
	{
		return GravityVector;
	}

private:
	class GameEngineWindowTexture* GroundTexture = nullptr;

	bool isGround = false;
	bool IsGravity = true;
	float GravityPower = 1.5f;
	float4 GravityVector = float4::ZERO;

};

