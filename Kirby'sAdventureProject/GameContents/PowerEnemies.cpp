#include "PowerEnemies.h"
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineCollision.h>


#include <vector>



PowerEnemies::PowerEnemies() 
{
}

PowerEnemies::~PowerEnemies() 
{
}


// ���� ���� �������� ��, �� �������͸� ��ȯ
float4 PowerEnemies::GetAbilityDir()
{
	float4 AbilityDir = float4::ZERO;

	if (ActorDir::Left == Dir)
	{
		AbilityDir = float4{ -1.0f, 0.0f };
	}
	else if (ActorDir::Right == Dir)
	{
		AbilityDir = float4{ 1.0f, 0.0f };
	}
	
	return AbilityDir;
}



void PowerEnemies::EnemyAbilityAttack()
{
	std::vector<GameEngineCollision*> KirbyBodyCollision;
	if (true == AbilityCollision->Collision(CollisionOrder::PlayerBody, KirbyBodyCollision, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineCollision* KirbyBody = KirbyBodyCollision[0];
		if (nullptr == KirbyBody)
		{
			MsgBoxAssert("Ŀ��� Null �Դϴ�.");
			return;
		}

		ActorUtils* KirbyPtr = dynamic_cast<ActorUtils*>(KirbyBody->GetActor());
		if (nullptr == KirbyPtr)
		{
			MsgBoxAssert("�ٿ� ĳ������ �����߽��ϴ�.");
			return;
		}

		KirbyPtr->IsHitted = true;
	}
}