#pragma once
#include <GameEngineCore/GameEngineActor.h>

#define CHECKGROUNDGAP 12.0f
#define CHECKCEILINGDGAP 12.0f
#define CHECKWALLWIDTHHGAP 9.0f
#define CHECKWALLHEIGHTHGAP 12.0f
#define CHECKGAP 3.0f

enum class ActorDir
{
	Right,
	Left,
	Max,
};


// 설명 :
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

	float4 ActorCameraPos();
	void SetGroundTexture(const std::string& _GroundTextureName);


	void GravityOn()
	{
		IsGravity = true;
	}

	void GravityOff()
	{
		IsGravity = false;
	}

	void SetDir(ActorDir _Dir)
	{
		Dir = _Dir;
	}


protected:
	GameEngineRenderer* MainRenderer = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
	ActorDir Dir = ActorDir::Max;
	float CurrentSpeed = 0.0f;


	void CameraFocus();



	float4 GroundLeftCheckPoint = float4::ZERO;
	float4 GroundRightCheckPoint = float4::ZERO;
	float4 WallBotLeftCheckPoint = float4::ZERO;
	float4 WallTopLeftCheckPoint = float4::ZERO;
	float4 WallBotRightCheckPoint = float4::ZERO;
	float4 WallTopRightCheckPoint = float4::ZERO;
	float4 CeilLeftCheckPoint = float4::ZERO;
	float4 CeilRightCheckPoint = float4::ZERO;

	// 판정 함수
	void GroundCheck();
	bool CeilingCheck();
	bool CheckLeftWall();
	bool CheckRightWall();
	bool CheckLeftWallBasedSpeed();
	bool CheckRightWallBasedSpeed();
	void BlockedByWall();
	void BlockedByGround();
	void BlockedByCeiling();
	void SetCheckPoint(const float4& _ScaleSize);
	bool IsSolidGround();
	bool IsPassableGround();

	int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);
	bool GetGroundState() const
	{
		return isGround;
	}


	const float GravityMaxVector = 450.0f;

	// 중력 함수
	void Gravity(float _Delta);
	void GravityLimit(float _Delta);
	void VerticalUpdate(float _Delta);
	void GravityReset()
	{
		GravityVector = float4::ZERO;
	}

	float4 GetGravityVector() const
	{
		return GravityVector;
	}

	void SetGravityVector(const float4& _GravityVector)
	{
		GravityVector = _GravityVector;
	}

	void AddGravityVector(const float _GravityPower, float _Delta)
	{
		GravityVector += float4::UP * _GravityPower * _Delta;
	}

	void SetAirResistance(float _AirResistance)
	{
		AirResistance = _AirResistance;
	}


private:
	class GameEngineWindowTexture* GroundTexture = nullptr;

	bool isGround = false;
	bool IsGravity = true;
	float GravityPower = 800.0f;
	float AirResistance = 1.0f;
	float4 GravityVector = float4::ZERO;

};

