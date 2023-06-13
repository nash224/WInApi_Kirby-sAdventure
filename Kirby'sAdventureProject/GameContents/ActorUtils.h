#pragma once
#include "ContentsActor.h"

#define CHECKGROUNDGAP 12.0f
#define CHECKCEILINGDGAP 12.0f
#define CHECKWALLWIDTHHGAP 9.0f
#define CHECKWALLHEIGHTHGAP 12.0f
#define CHECKGAP 3.0f

#define SMALLTYPECOLLISIONSCALE float4{ 48.0f , 48.0f }

#define CHECKSTAIRHEIGHT 48.0f

#define GRAVITYMAXVECTOR 450.0f


enum class AbilityStar
{
	None,
	Spark,
	Laser,
	Beam,
	Fire,
	Freeze,
	Thorn,
	Sword,
	UFO,
	Max,
};

// 설명 :
class ActorUtils : public ContentsActor
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
	float4 ActorDirUnitVector = float4::ZERO;
	AbilityStar Ability = AbilityStar::Max;


	bool IsChangeState = true;
	float StateTime = 0.0f;

	float CurentVerticalSpeed = 0.0f;





	void CameraFocus();
	float4 GetDirUnitVector() const;


	// 충돌 감지
	float4 GroundLeftCheckPoint = float4::ZERO;
	float4 GroundRightCheckPoint = float4::ZERO;
	float4 WallBotLeftCheckPoint = float4::ZERO;
	float4 WallTopLeftCheckPoint = float4::ZERO;
	float4 WallBotRightCheckPoint = float4::ZERO;
	float4 WallTopRightCheckPoint = float4::ZERO;
	float4 CeilLeftCheckPoint = float4::ZERO;
	float4 CeilRightCheckPoint = float4::ZERO;

	virtual void SetCheckPoint(const float4& _ScaleSize);
	void GroundCheck();
	bool CeilingCheck();
	bool CheckLeftWall();
	bool CheckRightWall();
	bool CheckLeftWallBasedSpeed();
	bool CheckRightWallBasedSpeed();
	void BlockedByWall();
	void BlockedByGround();
	void BlockedByCeiling();
	bool IsSolidGround();
	bool IsPassableGround();

	int GetGroundColor(unsigned int _DefaultColor, float4 _Pos = float4::ZERO);
	bool GetGroundState() const
	{
		return isGround;
	}

	virtual void ActorCollisionDetectionPointRender();


	// 중력 함수
	bool AbleJump = true;
	float CurrentJumpDistance = 0.0f;


	void Gravity(float _Delta);
	void ReverseGravity(float _Delta);
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

	// 이동 함수
	void VerticalSpeedLimitBasedlevitation(float _Speed);
	void VerticalUpdateBasedlevitation(float _Delta);



private:
	class GameEngineWindowTexture* GroundTexture = nullptr;

	bool isGround = false;
	bool IsGravity = true;
	float GravityPower = 800.0f;
	float4 GravityVector = float4::ZERO;
	const float GravityMaxVector = 450.0f;
	float AirResistance = 1.0f;

};

