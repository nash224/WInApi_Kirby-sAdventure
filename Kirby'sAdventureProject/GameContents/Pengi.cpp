#include "Pengi.h"
#include "ContentsEnum.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>


#include "GlobalContents.h"
#include "VegetableValleyPlayLevel.h"
#include "Kirby.h"


Pengi::Pengi()
{
}

Pengi::~Pengi()
{
}


void Pengi::Start()
{
	MainRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� �������� ���߽��ϴ�.");
		return;
	}

	GlobalContents::TextureFileLoad("Right_Pengi.bmp", "Resources\\Unit\\Grunt");

	MainRenderer->SetTexture("Right_Pengi.bmp");


	Scale = float4{ 24.0f, 39.0f };
	SetCheckPoint(Scale);

	Dir = ActorDir::Right;


	SetName("Pengi");

	CurState = "Idle";

	BodyCollision = CreateCollision(CollisionOrder::ForDisplay);
	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("�ٵ� �ݸ����� Null�ϸ��� ����..");
		return;
	}
	BodyCollision->SetCollisionPos(float4{ 0.0f, -Scale.hY() });
	BodyCollision->SetCollisionScale(Scale);
	BodyCollision->SetCollisionType(CollisionType::Rect);
	BodyCollision->On();
}

void Pengi::init(const std::string& _FileName, PengiState _State, const float4& _Pos)
{
	Attribute = AttributeType::None;
	Ability = AbilityStar::Ice;

	SetGroundTexture(_FileName);
	SetPos(_Pos);
	ChangeState(_State);
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */

void Pengi::Update(float _Delta)
{
	GroundCheck();

	StateUpdate(_Delta);
}

void Pengi::StateUpdate(float _Delta)
{
	switch (State)
	{
	case PengiState::Idle:					return IdleUpdate(_Delta);
	case PengiState::BeInhaled:				return BeInhaledUpdate(_Delta);
	default:
		break;
	}
}

void Pengi::ChangeState(PengiState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case PengiState::Idle:					IdleStart();					break;
		case PengiState::BeInhaled:				BeInhaledStart();				break;
		default:
			break;
		}
	}

	State = _State;
}

/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void Pengi::IdleStart()
{
	GravityReset();
}

void Pengi::IdleUpdate(float _Delta)
{
	Gravity(_Delta);
	GravityLimit(_Delta);

	BlockedByGround();

	if (false == GetGroundState())
	{
		VerticalUpdate(_Delta);
	}

	EnemyCollisionCheck();
}


// ���ÿ� ���̿��� �浹 ó���� �������� ���¹ۿ� �����ϴ�.
void Pengi::EnemyCollisionCheck()
{
	if (true == IsInhaledStateOn)
	{
		ChangeState(PengiState::BeInhaled);
		return;
	}
}


/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void Pengi::Render(float _Delta)
{
	if (false == VegetableValleyPlayLevel::Level_DebugRenderValue)
	{
		return;
	}


	HDC dc = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	int TextRenderNum = 0;


	float4 ActorScenePos = ActorCameraPos();

	int TextXPos = ActorScenePos.iX() - Scale.Half().iX();
	int TextYPos = ActorScenePos.iY() - (Scale * 2.0f).iY();


	EnemyDebugRender(dc, TextRenderNum, TextXPos, TextYPos);
}