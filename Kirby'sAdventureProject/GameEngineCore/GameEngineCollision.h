#pragma once
#include "GameEngineObject.h"
#include <GameEngineBase/GameEngineMath.h>
#include <string>
#include <map>
#include <vector>


enum class CollisionType
{
	Point,
	Rect,
	Circle,
	Max,
};


// 설명 : 충돌에 관한 클래스입니다. 각 충돌에 대한 정보를 변경할 수 있습니다.
class GameEngineActor;
class GameEngineCollision : public GameEngineObject
{
	friend class GameEngineActor;


private:
	static bool PointToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool PointToRect(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool PointToCirCle(GameEngineCollision* _Left, GameEngineCollision* _Right);

	static bool RectToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool RectToCirCle(GameEngineCollision* _Left, GameEngineCollision* _Right);

	static bool CirCleToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool CirCleToRect(GameEngineCollision* _Left, GameEngineCollision* _Right);
	static bool CirCleToCirCle(GameEngineCollision* _Left, GameEngineCollision* _Right);

public:
	// constrcuter destructer
	GameEngineCollision();
	~GameEngineCollision();

	// delete Function
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;

	void SetOrder(int _Order) override;



	void SetCollisionScale(const float4& _Value)
	{
		CollisionScale = _Value;
	}

	void SetCollisionPos(const float4& _Value)
	{
		CollisionPos = _Value;
	}


	GameEngineActor* GetActor()
	{
		return Master;
	}


	template<typename EnumType>
	bool Collision(EnumType _Order, std::vector<GameEngineCollision*>& _Result
		, CollisionType _ThisType = CollisionType::Circle
		, CollisionType _OtherType = CollisionType::Circle)
	{
		return Collision(static_cast<int>(_Order), _Result, _ThisType, _OtherType);
	}

	bool Collision(int _Order, std::vector<GameEngineCollision*>& _Result
		, CollisionType _ThisType = CollisionType::Circle
		, CollisionType _OtherType = CollisionType::Circle);



	bool CollisionCheck(GameEngineCollision* _Other,
		CollisionType _ThisType = CollisionType::Circle,
		CollisionType _OtherType = CollisionType::Circle);

protected:

private:
	GameEngineActor* Master = nullptr;
	float4 CollisionPos = float4::ZERO;
	float4 CollisionScale = float4::ZERO;

};

