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
	// 레이저 소환
	LaserEffect* LaserEffectPtr = GetLevel()->CreateActor<LaserEffect>();

	if (nullptr == LaserEffectPtr)
	{
		MsgBoxAssert("Null인 액터에 참조하려고 했습니다.");
		return;
	}

	LaserEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());
	LaserEffectPtr->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect);
}


void Kirby::OneTimeBeam()
{
	// 빔 소환
	BeamEffect* BeamEffectPtr = GetLevel()->CreateActor<BeamEffect>();
	if (nullptr == BeamEffectPtr)
	{
		MsgBoxAssert("액터가 Null일리가 없어...");
		return;
	}

	BeamEffectPtr->init(GetPos(), GetKirbyScale(), GetDirUnitVector());
	BeamEffectPtr->SetActorCollision(CollisionOrder::PlayerAbility, CollisionType::Rect);
}


void Kirby::OneTimeThorn()
{
	if (nullptr == ThornEffectCollision)
	{
		MsgBoxAssert("가시 충돌체가 Null 입니다.");
		return;
	}

	ThornEffectCollision->On();
}



void Kirby::OneTimeSpark()
{
	if (nullptr == SparkEffectCollision)
	{
		MsgBoxAssert("전기 충돌체가 Null 입니다.");
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
			MsgBoxAssert("액터가 Null입니다.");
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


	// 기본커비 특수 스킬 충돌검사
	std::vector<GameEngineCollision*> InhaleCol;
	if (true == InhaleEffectCollision->Collision(CollisionOrder::MonsterBody, InhaleCol, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < InhaleCol.size(); i++)
		{
			GameEngineCollision* Collision = InhaleCol[i];
			if (nullptr == Collision)
			{
				MsgBoxAssert("충돌한 객체가 Null 입니다.");
				return;
			}

			ActorUtils* EnemyPtr = dynamic_cast<ActorUtils*>(Collision->GetActor());
			if (nullptr == EnemyPtr)
			{
				MsgBoxAssert("다운 캐스팅이 잘못되었습니다.");
				return;
			}


			// 이미 충돌한 객체는 다시 못들어옴
			if (true == EnemyPtr->IsInhaledStateOn)
			{
				continue;
			}


			// 충돌되면 충돌했다는 변수를 변경하고, 몬스터의 능력 정보를 가져옴
			EnemyPtr->IsInhaledStateOn = true;
			AbilityStar EnemyAbility = EnemyPtr->Ability;


			// 빨아들인 몬스터 수에 따라 별의 크기가 결정됨
			if (AbilityStar::Max != EnemyAbility)
			{
				++Star.SwallowedEnemyNumber;
				SwallingEnemy = EnemyPtr;
			}

			// 특수 몹을 2명 이상 먹었으면 랜덤 능력
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


	// 아무도 안먹었을 때 'Z' 키를 때면 능력 해제
	if (true == IsChangeState && true == GameEngineInput::IsFree('Z') && 0 == Star.SwallowedEnemyNumber)
	{
		Star.SwallowedPowerEnemyNumber;

		InhaleEffectCollision->Off();
		ChangeState(KirbyState::ReleaseSpecialAbility);
		return;
	}



	// 데미지 상태 패턴
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





// 몸통 충돌검사 또는 외부에서 맞았을 경우 Damaged 상태
void Kirby::CheckKirbyCollision()
{
	
	GameEngineCollision* KirbyBodyCollision = GetKirbyCollison();
	if (nullptr == KirbyBodyCollision)
	{
		MsgBoxAssert("커비 몸통 충돌체가 Null 입니다.");
		return;
	}

	// 면역상태가 아닐때 충돌
	std::vector<GameEngineCollision*> MonsterBodyCol;
	if (true == KirbyBodyCollision->Collision(CollisionOrder::MonsterBody, MonsterBodyCol, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < MonsterBodyCol.size(); i++)
		{
			GameEngineCollision* MonsterBodyPtr = MonsterBodyCol[i];
			if (nullptr == MonsterBodyPtr)
			{
				MsgBoxAssert("참조한 Monster 가 Null 입니다.");
				return;
			}

			ActorUtils* Monster = dynamic_cast<ActorUtils*>(MonsterBodyPtr->GetActor());
			if (nullptr == Monster)
			{
				MsgBoxAssert("다운 캐스팅 오류입니다.");
				return;
			}

			// 맞았고
			Monster->IsHitted = true;


			// 커비가 면역상태가 아니면 데미지
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
					MsgBoxAssert("커비의 KeepDamaged 변수가 이상합니다.");
					return;
				}
			}
		}
	}



	// 면역상태일 때, 몬스터 충돌 
	std::vector<GameEngineCollision*> MonsterBodyColToImmune;
	if (true == ImmuneCollision->Collision(CollisionOrder::MonsterBody, MonsterBodyColToImmune, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < MonsterBodyColToImmune.size(); i++)
		{
			GameEngineCollision* MonsterBodyPtr = MonsterBodyColToImmune[i];
			if (nullptr == MonsterBodyPtr)
			{
				MsgBoxAssert("참조한 Monster 가 Null 입니다.");
				return;
			}

			ActorUtils* Monster = dynamic_cast<ActorUtils*>(MonsterBodyPtr->GetActor());
			if (nullptr == Monster)
			{
				MsgBoxAssert("다운 캐스팅 오류입니다.");
				return;
			}

			Monster->IsHitted = true;
		}
	}



	// 커비가 맞았을때 데미지 상태
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
			MsgBoxAssert("커비의 KeepDamaged 변수가 이상합니다.");
			return;
		}
	}

}


// 커비에 능력 충돌체가 있는 경우
void Kirby::CheckKirbyAbilityCollision(GameEngineCollision* _CheckCol)
{
	if (nullptr == _CheckCol)
	{
		MsgBoxAssert("충돌 인자가 Null 입니다.");
		return;
	}


	// 능력 충돌 검사
	std::vector<GameEngineCollision*> AbilityCol;
	if (true == _CheckCol->Collision(CollisionOrder::MonsterBody, AbilityCol, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < AbilityCol.size(); i++)
		{
			GameEngineCollision* MonsterBodyPtr = AbilityCol[i];
			if (nullptr == MonsterBodyPtr)
			{
				MsgBoxAssert("참조한 Monster 가 Null 입니다.");
				return;
			}

			ActorUtils* Monster = dynamic_cast<ActorUtils*>(MonsterBodyPtr->GetActor());
			if (nullptr == Monster)
			{
				MsgBoxAssert("다운 캐스팅 오류입니다.");
				return;
			}

			// 몬스터 상태 변경 트리거 On
			Monster->IsHitted = true;
		}
	}
}