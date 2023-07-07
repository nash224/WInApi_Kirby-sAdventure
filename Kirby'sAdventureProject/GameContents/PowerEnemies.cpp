#include "PowerEnemies.h"
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineCollision.h>



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
		for (size_t i = 0; i < KirbyBodyCollision.size(); i++)
		{
			GameEngineCollision* KirbyBody = KirbyBodyCollision[i];
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


			if (true == KirbyPtr->IsHitted)
			{
				continue;
			}

			KirbyPtr->IsHitted = true;
		}
	}
}


void PowerEnemies::PowerEnemyDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos)
{
	if (nullptr == _dc)
	{
		MsgBoxAssert("�ڵ��� �ҷ����� ���߽��ϴ�.");
		return;
	}

	{
		std::string Text = "";
		Text += "Ability Collision : ";
		if (nullptr == AbilityCollision)
		{
			MsgBoxAssert("�浹ü�� �ҷ����� ���߽��ϴ�.");
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