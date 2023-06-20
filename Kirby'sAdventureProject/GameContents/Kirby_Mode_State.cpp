#include "Kirby.h"
#include "ContentsEnum.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>


#include "BeamEffect.h"
#include "LaserEffect.h"
#include "FrameBreathEffect.h"




void Kirby::UseSpecialAbilityStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	UseAbilityStart();
	ChangeAnimationState("UseSpecialAbility");
}

void Kirby::UseSpecialAbilityUpdate(float _Delta)
{
	UseAbilityUpdate(_Delta);
}



void Kirby::ReleaseSpecialAbilityStart()
{
	StateTime = 0.0f;
	IsChangeState = false;
	ChangeAnimationState("ReleaseSpecialAbility");
}

void Kirby::ReleaseSpecialAbilityUpdate(float _Delta)
{
	IsChangeState = MainRenderer->IsAnimationEnd();

	if (true == IsChangeState && false == GetGroundState())
	{
		ChangeState(KirbyState::Fall);
		return;
	}
	if (true == IsChangeState && true == GetGroundState())
	{
		ChangeState(KirbyState::Idle);
		return;
	}

	BlockedByWall();
	BlockedByGround();

	ActorUtils::DecelerationUpdate(_Delta, DECELERATIONSPEED);
	HorizontalUpdate(_Delta);

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}
}


void Kirby::UseAbilityStart()
{
	switch (Mode)
	{
	case AbilityStar::Normal:
		InhaleAbilityStart();
		break;
	case AbilityStar::Spark:
		SparkAbilityStart();
		break;
	case AbilityStar::Laser:
		LaserAbilityStart();
		break;
	case AbilityStar::Beam:
		BeamAbilityStart();
		break;
	case AbilityStar::Fire:
		FireAbilityStart();
		break;
	case AbilityStar::Thorn:
		ThornAbilityStart();
		break;
	case AbilityStar::Sword:
		SwordAbilityStart();
		break;
	case AbilityStar::Max:
		break;
	default:
		break;
	}
}

void Kirby::UseAbilityUpdate(float _Delta)
{
	switch (Mode)
	{
	case AbilityStar::Normal:
		InhaleAbilityUpdate(_Delta);
		break;
	case AbilityStar::Spark:
		SparkAbilityUpdate(_Delta);
		break;
	case AbilityStar::Laser:
		LaserAbilityUpdate(_Delta);
		break;
	case AbilityStar::Beam:
		BeamAbilityUpdate(_Delta);
		break;
	case AbilityStar::Fire:
		FireAbilityUpdate(_Delta);
		break;
	case AbilityStar::Thorn:
		ThornAbilityUpdate(_Delta);
		break;
	case AbilityStar::Sword:
		SwordAbilityUpdate(_Delta);
		break;
	case AbilityStar::Max:
		break;
	default:
		break;
	}
}


void Kirby::TriggerOneTimeAbility()
{
	switch (Mode)
	{
	case AbilityStar::Spark:
		OneTimeSpark();
		break;
	case AbilityStar::Laser:
		OneTimeLaser();
		break;
	case AbilityStar::Beam:
		OneTimeBeam();
		break;
	case AbilityStar::Fire:
		break;
	case AbilityStar::Thorn:
		OneTimeThorn();
		break;
	case AbilityStar::Sword:
		break;
	default:
		break;
	}
}



void Kirby::OneTimeLaser()
{
	// ������ ��ȯ
	LaserEffect* LaserEffectPtr = GetLevel()->CreateActor<LaserEffect>();

	if (nullptr == LaserEffectPtr)
	{
		MsgBoxAssert("Null�� ���Ϳ� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	LaserEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());
	LaserEffectPtr->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect);
}


void Kirby::OneTimeBeam()
{
	// �� ��ȯ
	BeamEffect* BeamEffectPtr = GetLevel()->CreateActor<BeamEffect>();
	if (nullptr == BeamEffectPtr)
	{
		MsgBoxAssert("���Ͱ� Null�ϸ��� ����...");
		return;
	}

	BeamEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());
	BeamEffectPtr->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect);
}


void Kirby::OneTimeThorn()
{
	if (nullptr == ThornEffectCollision)
	{
		MsgBoxAssert("���� �浹ü�� Null �Դϴ�.");
		return;
	}

	ThornEffectCollision->On();
}



void Kirby::OneTimeSpark()
{
	if (nullptr == SparkEffectCollision)
	{
		MsgBoxAssert("���� �浹ü�� Null �Դϴ�.");
		return;
	}

	SparkEffectCollision->On();
}


void Kirby::TriggerMultiTimeAbility(float _Delta)
{
	switch (Mode)
	{
	case AbilityStar::Spark:
		break;
	case AbilityStar::Laser:
		break;
	case AbilityStar::Beam:
		break;
	case AbilityStar::Fire:
		TriggerFireAbilityAfterProcess(_Delta);
		break;
	case AbilityStar::Thorn:
		break;
	case AbilityStar::Sword:
		break;
	default:
		break;
	}
}


void Kirby::TriggerFireAbilityAfterProcess(float _Delta)
{
	FrameTime += _Delta;


	if (FrameTime > KIRBYFRAMEEFFECTCREATECYCLE)
	{
		FrameTime = 0.0f;

		FrameBreathEffect* FrameBreathEffectPtr = GetLevel()->CreateActor<FrameBreathEffect>(UpdateOrder::Ability);

		if (nullptr == FrameBreathEffectPtr)
		{
			MsgBoxAssert("���Ͱ� Null�Դϴ�.");
			return;
		}

		FrameBreathEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());
		FrameBreathEffectPtr->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect);
	}


}




void Kirby::InhaleAbilityStart()
{
	Duration = 0.0f;
	swallowedObject = false;
	IsSwallowedtriggerOn = false;
	Star.SwallowedEnemyNumber = 0;
	Star.SwallowedPowerEnemyNumber = 0;

	float4 KirbyDirUnitVector = GetDirUnitVector();
	if (KirbyDirUnitVector.X < 0.0f)
	{
		KirbyDirUnitVector =
			float4{ -(INHALEEFFECTCOLLISIONSCALE + SMALLTYPECOLLISIONSCALE).Half().X, -INHALEEFFECTCOLLISIONSCALE.Half().Y };
	}
	else if (KirbyDirUnitVector.X > 0.0f)
	{
		KirbyDirUnitVector =
			float4{ (INHALEEFFECTCOLLISIONSCALE + LOWERTYPECOLLISIONSCALE).Half().X, -INHALEEFFECTCOLLISIONSCALE.Half().Y };
	}
	InhaleEffectCollision->SetCollisionPos(KirbyDirUnitVector);
	InhaleEffectCollision->On();
}



void Kirby::InhaleAbilityUpdate(float _Delta)
{
	StateTime += _Delta;

	IsChangeState = MainRenderer->IsAnimationEnd();


	// �⺻Ŀ�� Ư�� ��ų �浹�˻�
	std::vector<GameEngineCollision*> InhaleCol;
	if (true == InhaleEffectCollision->Collision(CollisionOrder::MonsterBody, InhaleCol, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < InhaleCol.size(); i++)
		{
			GameEngineCollision* Collision = InhaleCol[i];
			if (nullptr == Collision)
			{
				MsgBoxAssert("�浹�� ��ü�� Null �Դϴ�.");
				return;
			}

			ActorUtils* EnemyPtr = dynamic_cast<ActorUtils*>(Collision->GetActor());
			if (nullptr == EnemyPtr)
			{
				MsgBoxAssert("�ٿ� ĳ������ �߸��Ǿ����ϴ�.");
				return;
			}


			// �̹� �浹�� ��ü�� �ٽ� ������
			if (true == EnemyPtr->IsInhaledStateOn)
			{
				continue;
			}


			// �浹�Ǹ� �浹�ߴٴ� ������ �����ϰ�, ������ �ɷ� ������ ������
			EnemyPtr->IsInhaledStateOn = true;
			AbilityStar EnemyAbility = EnemyPtr->Ability;


			// ���Ƶ��� ���� ���� ���� ���� ũ�Ⱑ ������
			if (AbilityStar::Max != EnemyAbility)
			{
				++Star.SwallowedEnemyNumber;
				SwallingEnemy = EnemyPtr;
			}

			// Ư�� ���� 2�� �̻� �Ծ����� ���� �ɷ�
			if (AbilityStar::Normal != EnemyAbility && AbilityStar::Max != EnemyAbility)
			{
				CurrentAbilityStar = EnemyAbility;
				++Star.SwallowedPowerEnemyNumber;
			}
		}
	}
	


	// 
	if ((Star.SwallowedEnemyNumber > 0 && false == SwallingEnemy->IsUpdate()) || StateTime > 3.0f)
	{
		InhaleEffectCollision->Off();
		ChangeState(KirbyState::Contain_Idle);
		return;
	}


	// �ƹ��� �ȸԾ��� �� 'Z' Ű�� ���� �ɷ� ����
	if (true == IsChangeState && true == GameEngineInput::IsFree('Z') && 0 == Star.SwallowedEnemyNumber)
	{
		Star.SwallowedPowerEnemyNumber;

		InhaleEffectCollision->Off();
		ChangeState(KirbyState::ReleaseSpecialAbility);
		return;
	}



	// ������ ���� ����
	CheckKirbyCollision();




	BlockedByWall(); 
	BlockedByGround();

	if (false == GetGroundState())
	{
		Gravity(_Delta);
		GravityLimit(_Delta);
		VerticalUpdate(_Delta);
	}

	ContentsActor::DecelerationUpdate(_Delta, DECELERATIONSPEED);
	HorizontalUpdate(_Delta);
}






void Kirby::DropAbility()
{
	Mode = AbilityStar::Normal;
	ChangeAnimationState(CurState);
}





// ���� �浹�˻� �Ǵ� �ܺο��� �¾��� ��� Damaged ����
void Kirby::CheckKirbyCollision()
{
	
	GameEngineCollision* KirbyBodyCollision = GetKirbyCollison();
	if (nullptr == KirbyBodyCollision)
	{
		MsgBoxAssert("Ŀ�� ���� �浹ü�� Null �Դϴ�.");
		return;
	}

	// �鿪���°� �ƴҶ� �浹
	std::vector<GameEngineCollision*> MonsterBodyCol;
	if (true == KirbyBodyCollision->Collision(CollisionOrder::MonsterBody, MonsterBodyCol, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < MonsterBodyCol.size(); i++)
		{
			GameEngineCollision* MonsterBodyPtr = MonsterBodyCol[i];
			if (nullptr == MonsterBodyPtr)
			{
				MsgBoxAssert("������ Monster �� Null �Դϴ�.");
				return;
			}

			ActorUtils* Monster = dynamic_cast<ActorUtils*>(MonsterBodyPtr->GetActor());
			if (nullptr == Monster)
			{
				MsgBoxAssert("�ٿ� ĳ���� �����Դϴ�.");
				return;
			}

			// �¾Ұ�
			Monster->IsHitted = true;


			// Ŀ�� �鿪���°� �ƴϸ� ������
			if (false == ImmuneState)
			{
				if (KirbyState::Fly != KeepDamagedState && KirbyState::Contain_Idle != KeepDamagedState)
				{
					ChangeState(KirbyState::Damaged);
					return;
				}
				else if (KirbyState::Fly == KeepDamagedState || KirbyState::Contain_Idle == KeepDamagedState)
				{
					ChangeState(KirbyState::Contain_Damaged);
					return;
				}
				else
				{
					MsgBoxAssert("Ŀ���� KeepDamaged ������ �̻��մϴ�.");
					return;
				}
			}
		}
	}



	// �鿪������ ��, ���� �浹 
	std::vector<GameEngineCollision*> MonsterBodyColToImmune;
	if (true == ImmuneCollision->Collision(CollisionOrder::MonsterBody, MonsterBodyColToImmune, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < MonsterBodyColToImmune.size(); i++)
		{
			GameEngineCollision* MonsterBodyPtr = MonsterBodyColToImmune[i];
			if (nullptr == MonsterBodyPtr)
			{
				MsgBoxAssert("������ Monster �� Null �Դϴ�.");
				return;
			}

			ActorUtils* Monster = dynamic_cast<ActorUtils*>(MonsterBodyPtr->GetActor());
			if (nullptr == Monster)
			{
				MsgBoxAssert("�ٿ� ĳ���� �����Դϴ�.");
				return;
			}

			Monster->IsHitted = true;
		}
	}



	// Ŀ�� �¾����� ������ ����
	if (true == IsHitted && false == ImmuneState)
	{
		if (KirbyState::Fly != KeepDamagedState && KirbyState::Contain_Idle != KeepDamagedState)
		{
			ChangeState(KirbyState::Damaged);
			return;
		}
		else if (KirbyState::Fly == KeepDamagedState || KirbyState::Contain_Idle == KeepDamagedState)
		{
			ChangeState(KirbyState::Contain_Damaged);
			return;
		}
		else
		{
			MsgBoxAssert("Ŀ���� KeepDamaged ������ �̻��մϴ�.");
			return;
		}
	}

}


// Ŀ�� �ɷ� �浹ü�� �ִ� ���
void Kirby::CheckKirbyAbilityCollision(GameEngineCollision* _CheckCol)
{
	if (nullptr == _CheckCol)
	{
		MsgBoxAssert("�浹 ���ڰ� Null �Դϴ�.");
		return;
	}


	// �ɷ� �浹 �˻�
	std::vector<GameEngineCollision*> AbilityCol;
	if (true == _CheckCol->Collision(CollisionOrder::MonsterBody, AbilityCol, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < AbilityCol.size(); i++)
		{
			GameEngineCollision* MonsterBodyPtr = AbilityCol[i];
			if (nullptr == MonsterBodyPtr)
			{
				MsgBoxAssert("������ Monster �� Null �Դϴ�.");
				return;
			}

			ActorUtils* Monster = dynamic_cast<ActorUtils*>(MonsterBodyPtr->GetActor());
			if (nullptr == Monster)
			{
				MsgBoxAssert("�ٿ� ĳ���� �����Դϴ�.");
				return;
			}

			// ���� ���� ���� Ʈ���� On
			Monster->IsHitted = true;
		}
	}
}