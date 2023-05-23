#include "GameEngineCollision.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <list>

bool (*GameEngineCollision::CollisionFunction[static_cast<int>(CollisionType::Max)][static_cast<int>(CollisionType::Max)])(GameEngineCollision* _Left, GameEngineCollision* _Right) = { nullptr };

bool GameEngineCollision::PointToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	MsgBoxAssert("�浹üũ �Լ��� ������ �ʾҽ��ϴ�.");
	return false;
}
bool GameEngineCollision::PointToRect(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}
bool GameEngineCollision::PointToCirCle(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}
bool GameEngineCollision::RectToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}
bool GameEngineCollision::RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}
bool GameEngineCollision::RectToCirCle(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}
bool GameEngineCollision::CirCleToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}
bool GameEngineCollision::CirCleToRect(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}
bool GameEngineCollision::CirCleToCirCle(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	return false;
}

class CollisionInitClass
{
public:
	CollisionInitClass()
	{
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::Point)][static_cast<size_t>(CollisionType::Point)] = &GameEngineCollision::PointToPoint;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::Point)][static_cast<size_t>(CollisionType::Rect)] = &GameEngineCollision::PointToRect;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::Point)][static_cast<size_t>(CollisionType::CirCle)] = &GameEngineCollision::PointToCirCle;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::Rect)][static_cast<size_t>(CollisionType::Point)] = &GameEngineCollision::RectToPoint;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::Rect)][static_cast<size_t>(CollisionType::Rect)] = &GameEngineCollision::RectToRect;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::Rect)][static_cast<size_t>(CollisionType::CirCle)] = &GameEngineCollision::RectToCirCle;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::CirCle)][static_cast<size_t>(CollisionType::Point)] = &GameEngineCollision::CirCleToPoint;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::CirCle)][static_cast<size_t>(CollisionType::Rect)] = &GameEngineCollision::CirCleToRect;
		GameEngineCollision::CollisionFunction[static_cast<size_t>(CollisionType::CirCle)][static_cast<size_t>(CollisionType::CirCle)] = &GameEngineCollision::CirCleToCirCle;
	}
};

CollisionInitClass ColInitInst = CollisionInitClass();

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
	//Points.push_back({1, 0});
	//Points.push_back({ 1, 0 });
}



bool GameEngineCollision::Collision(int _Order,
	std::vector<GameEngineCollision*>& _Result,
	CollisionType _ThisType,
	CollisionType _OtherType)
{
	if (false == IsUpdate())
	{
		return false;
	}

	std::list<GameEngineCollision*>& OtherCollision = Master->GetLevel()->AllCollision[_Order];

	if (0 == OtherCollision.size())
	{
		return false;
	}

	bool Check = false;

	for (GameEngineCollision* Collision : OtherCollision)
	{
		if (nullptr == Collision)
		{
			MsgBoxAssert("�������� �ʴ� �ݸ����� �ֽ��ϴ�.");
			return false;
		}

		if (false == Collision->IsUpdate())
		{
			continue;
		}

		// ����ü ��������� �ݸ����� ������ ���°�?
		// ���� �����Ǵ°�?
		// ��� �������°� ?
		// Level 

		// ���� ���� �浹�� �غ��� ��.
		if (true == CollisonCheck(Collision, _ThisType, _OtherType))
		{
			_Result.push_back(Collision);
			Check = true;
		}
	}

	return Check;
}


void GameEngineCollision::SetOrder(int _Order)
{
	std::list<GameEngineCollision*>& PrevCollisions = Master->GetLevel()->AllCollision[GetOrder()];
	PrevCollisions.remove(this);

	GameEngineObject::SetOrder(_Order);

	std::list<GameEngineCollision*>& NextCollisions = Master->GetLevel()->AllCollision[GetOrder()];
	NextCollisions.push_back(this);

}

bool GameEngineCollision::CollisonCheck(GameEngineCollision* _Other
	, CollisionType _ThisType
	, CollisionType _OtherType)
{
	if (nullptr == CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)])
	{
		MsgBoxAssert("�浹üũ�Լ��� ������ �ʾҽ��ϴ�.");
		return false;
	}

	return CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)](this, _Other);
}