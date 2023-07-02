#include "IceBlock.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEngineBase/GameEngineRandom.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "ActorUtils.h"
#include "ObejctDisapearingEffect.h"



IceBlock::IceBlock()
{
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

	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("IceBlock.bmp", "Resources\\Effect\\KirbyBaseEffect");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �ҷ����� ���߽��ϴ�.");
		return;
	}

	MainRenderer->SetTexture("IceBlock.bmp");


	Scale = Texture->GetScale();

	SetCheckPoint(Scale);






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
	BlockToPlayerCollisionCheck();
}



void IceBlock::WingStart()
{
	
}

void IceBlock::WingUpdate(float _Delta)
{
	// �浹 üũ
	AbilityToActorCollisionCheck(CollisionOrder::MonsterBody, true);

	if (false == IsAbilityCollisionCheck)
	{
		int Damage = GameEngineRandom::MainRandom.RandomInt(3, 5);
		AbilityToBossCollisionCheck(CollisionOrder::BossBody, Damage, true);
	}


	// ��ġ ����ȭ
	AddPos(EffectDir * SMALLSTARFIREEFFECTSPEED * _Delta);


	// �߾ӿ� ��Ʈ���� ��Ҵ� �� �˻�
	if (true == CheckCenterPoint())
	{
		Call_DisapearEffect(false);

		Death();
		EffectPointerRelease();

		return;
	}


	// ī�޶� ������ �Ѿ�� 
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	if (GetCameraPos().X > GetPos().X && GetPos().X > GetCameraPos().X + WinScale.X)
	{
		// �װ� ����
		Death();
		EffectPointerRelease();

		return;
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




void IceBlock::LevelEnd()
{
	Death();
	EffectPointerRelease();
}