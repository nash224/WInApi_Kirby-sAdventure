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


// 방향 값을 기준으로 좌, 우 단위벡터를 반환
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
			MsgBoxAssert("커비는 Null 입니다.");
			return;
		}

		ActorUtils* KirbyPtr = dynamic_cast<ActorUtils*>(KirbyBody->GetActor());
		if (nullptr == KirbyPtr)
		{
			MsgBoxAssert("다운 캐스팅이 실패했습니다.");
			return;
		}

		KirbyPtr->IsHitted = true;
	}
}


void PowerEnemies::PowerEnemyDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos)
{
	{
		std::string Text = "";
		Text += "Ability Collision : ";
		if (nullptr == AbilityCollision)
		{
			MsgBoxAssert("충돌체를 불러오지 못했습니다.");
			return;
		}

		if (true == AbilityCollision->IsUpdate())
		{
			Text += "On";
		}
		else if (false == AbilityCollision->IsUpdate())
		{
			Text += "Off";
		}
		TextOutA(_dc, _TextXPos, 2 + _TextYPos - _RenderNumber * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++_RenderNumber;
	}
}