#include "GameEngineCollision.h"

#include "GameEngineActor.h"
#include "GameEngineLevel.h"

#include <list>


bool GameEngineCollision::PointToPoint(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
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



GameEngineCollision::GameEngineCollision() 
{
}

GameEngineCollision::~GameEngineCollision() 
{
}


bool GameEngineCollision::Collision(int _Order, std::vector<GameEngineCollision*>& _Result
	, CollisionType _ThisType/* = CollisionType::Circle*/
	, CollisionType _OtherType/* = CollisionType::Circle*/)
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
			MsgBoxAssert("�浹ü�� �������� �ʽ��ϴ�.");
			return false;
		}

		if (false == Collision->IsUpdate())
		{
			continue;
		}

		
		// ���� ����� �浹�� Ȯ����
		if (true == CollisionCheck(Collision, _ThisType, _OtherType))
		{
			_Result.push_back(Collision);
			Check = true;
		}
	}

	return Check;
}


bool GameEngineCollision::CollisionCheck(GameEngineCollision* _Other,
	CollisionType _ThisType/* = CollisionType::Circle*/,
	CollisionType _OtherType/* = CollisionType::Circle*/)
{
	// ��������
	return true;
}


void GameEngineCollision::SetOrder(int _Order)
{
	std::list<GameEngineCollision*>& PrevCollision = Master->GetLevel()->AllCollision[GetOrder()];
	PrevCollision.remove(this);

	GameEngineObject::SetOrder(_Order);

	std::list<GameEngineCollision*>& NextCollision = Master->GetLevel()->AllCollision[GetOrder()];
	PrevCollision.push_back(this);
}
