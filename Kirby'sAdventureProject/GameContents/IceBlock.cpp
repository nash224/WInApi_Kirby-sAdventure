#include "IceBlock.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "ActorUtils.h"
#include "Kirby.h"
#include "ObejctDisapearingEffect.h"
#include "CrossDeathEffect.h"



IceBlock::IceBlock()
{
	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("Ŀ�� �������� �ʽ��ϴ�.");
		return;
	}

	std::list<IceBlock*>& IceList = KirbyPtr->GetIceList();
	IceList.push_back(this);
}

IceBlock::~IceBlock()
{
}


void IceBlock::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� ���� ������ ����..");
		return;
	}

	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("IceBlock.bmp", "Resources\\Effect\\SkillEffect");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	MainRenderer->SetTexture("IceBlock.bmp");


	Scale = Texture->GetScale();

	SetCheckPoint(Scale);


	ChangeState(IceBlockState::Idle);



	BlockBodyCollision = CreateCollision(CollisionOrder::IceBlockMoveBody);
	if (nullptr == BlockBodyCollision)
	{
		MsgBoxAssert("�浹ü�� �������� ���߽��ϴ�.");
		return;
	}

	BlockBodyCollision->SetCollisionScale(Scale);
	BlockBodyCollision->SetCollisionType(CollisionType::Rect);
	BlockBodyCollision->On();

}

void IceBlock::init(const float4& _Pos, const float4& _MasterPos)
{
	SetPos(_Pos + float4{ 0.0f , -_MasterPos.Half().Y });
}





void IceBlock::Update(float _Delta)
{
	StateUpdate(_Delta);
}


void IceBlock::StateUpdate(float _Delta)
{
	switch (State)
	{
	case IceBlockState::Idle:
		IdleUpdate(_Delta);
		break;
	case IceBlockState::Wing:
		WingUpdate(_Delta);
		break;
	default:
		break;
	}
}


void IceBlock::ChangeState(IceBlockState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case IceBlockState::Idle:
			IdleStart();
			break;
		case IceBlockState::Wing:
			WingStart();
			break;
		default:
			break;
		}

		State = _State;
	}
}



void IceBlock::IdleStart()
{

}

void IceBlock::IdleUpdate(float _Delta)
{

	// �ð������� ����
	if (GetLiveTime() > LiveTime)
	{
		GameEngineLevel* CurLevelPtr = GetLevel();
		if (nullptr == CurLevelPtr)
		{
			MsgBoxAssert("������ �ҷ����� ���߽��ϴ�.");
			return;
		}


		CrossDeathEffect* CrossDeathEffectPtr = CurLevelPtr->CreateActor<CrossDeathEffect>(UpdateOrder::Ability);
		if (nullptr == CrossDeathEffectPtr)
		{
			MsgBoxAssert("���͸� �������� ���߽��ϴ�.");
			return;
		}

		CrossDeathEffectPtr->init(GetPos(), Scale);

		Death();
		ReleaseThisList();
		EffectPointerRelease();
		return;
	}



	BlockToPlayerCollisionCheck();
}



void IceBlock::WingStart()
{
	
}

void IceBlock::WingUpdate(float _Delta)
{
	// ��ġ ����ȭ
	AddPos(EffectDir * SMALLSTARFIREEFFECTSPEED * _Delta);



	// �߾ӿ� ��Ʈ���� ��Ҵ� �� �˻�
	if (true == CheckCenterPoint())
	{
		Call_DisapearEffect(false);

		Death();
		ReleaseThisList();
		EffectPointerRelease();

		return;
	}


	// ī�޶� ������ �Ѿ�� 
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	if (GetCameraPos().X > GetPos().X && GetPos().X > GetCameraPos().X + WinScale.X)
	{
		// �װ� ����
		Death();
		ReleaseThisList();
		EffectPointerRelease();

		return;
	}





	// �浹 üũ
	AbilityToActorCollisionCheck(CollisionOrder::MonsterBody, true);

	if (false == IsAbilityCollisionCheck)
	{
		int Damage = GameEngineRandom::MainRandom.RandomInt(3, 5);
		AbilityToBossCollisionCheck(CollisionOrder::BossBody, Damage, true);
	}

}






void IceBlock::BlockToPlayerCollisionCheck()
{
	if (nullptr == BlockBodyCollision)
	{
		MsgBoxAssert("�浹ü�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	
	std::vector<GameEngineCollision*> PlayerCol;
	if (true == BlockBodyCollision->Collision(CollisionOrder::PlayerBody, PlayerCol, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < PlayerCol.size(); i++)
		{
			GameEngineCollision* Collision = PlayerCol[i];
			if (nullptr == Collision)
			{
				MsgBoxAssert("�浹ü�� �ҷ����� ���߽��ϴ�.");
				return;
			}

			GameEngineActor* PlayerPtr = Collision->GetActor();
			if (nullptr == PlayerPtr)
			{
				MsgBoxAssert("���͸� �ҷ����� ���߽��ϴ�.");
				return;
			}

			float4 KirbyPos = PlayerPtr->GetPos();

			if (GetPos().X > KirbyPos.X)
			{
				EffectDir = float4::RIGHT;
			}
			else if (GetPos().X <= KirbyPos.X)
			{
				EffectDir = float4::LEFT;
			}

			BlockBodyCollision->Off();
			ChangeState(IceBlockState::Wing);
			return;
		}
	}

}



void IceBlock::SkillDeathEffect()
{
	Call_DisapearEffect();
}

void IceBlock::DataStructRelease()
{
	ReleaseThisList();
}


void IceBlock::ReleaseThisList()
{
	Kirby* KirbyPtr = Kirby::GetMainKirby();
	if (nullptr == KirbyPtr)
	{
		MsgBoxAssert("Ŀ�� �������� �ʽ��ϴ�.");
		return;
	}

	std::list<IceBlock*>& IceList = KirbyPtr->GetIceList();
	IceList.remove(this);
	std::list<IceBlock*>& ResultIceList = KirbyPtr->GetIceList();
}




void IceBlock::LevelEnd()
{
	Death();
	ReleaseThisList();
	EffectPointerRelease();
}