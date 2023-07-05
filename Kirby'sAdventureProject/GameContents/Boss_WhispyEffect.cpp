#include "Boss_WhispyEffect.h"
#include "ContentsEnum.h"
#include "GlobalContents.h"


#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineRenderer.h>


#include "WhispyWood.h"


Boss_WhispyEffect::Boss_WhispyEffect()
{
}

Boss_WhispyEffect::~Boss_WhispyEffect()
{
}


void Boss_WhispyEffect::Start()
{
	// ������ ����
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("�������� ���� ������ ����..");
		return;
	}

	// �̹��� �ε�
	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("WhispyWood_ExhaleEffect_1x1_48x48.bmp", "Resources\\Effect\\SkillEffect");
	if (nullptr == Texture)
	{
		MsgBoxAssert("�ؽ�ó�� �о���� ���߽��ϴ�.");
		return;
	}

	Scale = Texture->GetScale();

	// ����
	MainRenderer->SetTexture("WhispyWood_ExhaleEffect_1x1_48x48.bmp");

	EffectDir = float4::LEFT;
}



// ���� ��ġ ����
void Boss_WhispyEffect::init(const float4& _MasterPos, const float4& _MaterScale)
{
	SetPos(_MasterPos + EffectDir * (_MaterScale.Half().X + Scale.Half().X) + float4{ 0.0f , 36.0f });

	EffectDir = float4{ -4.0f , 1.0f }.NormalizeReturn();
	XSpeed = EffectDir.X * WhispySpeed;
	YSpeed = EffectDir.Y * WhispySpeed;
	XOriginSpeed = XSpeed;
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void Boss_WhispyEffect::Update(float _Delta)
{
	float4 MoveSpeed = float4::ZERO;


	Current_XDsitance += XSpeed * _Delta;
	// ������ ���ϱ� �� �Ǵ� ������ ��� 
	if (abs(Current_XDsitance) < Whispy_ChangeDir_XDistance || true == IsSecondinflectionPoint)
	{
		MoveSpeed = EffectDir * WhispySpeed;
	}
	// ���ϰ� XSpeed�� 0�� �Ǳ������ ���
	else if (false == IsFirstinflectionPoint && abs(Current_XDsitance) > Whispy_ChangeDir_XDistance)
	{

		XSpeed += WhispySpeed * Whispy_DecelectionRatio * _Delta;
		YSpeed += WhispySpeed * WhispyYSpeedRatio * _Delta;

		MoveSpeed = float4{ XSpeed , YSpeed };

		if (XSpeed > 0.0f)
		{
			IsFirstinflectionPoint = true;
		}
	}
	// �ӵ��� ���������� ���� �ӵ��� ���ƿ��� ���� ���
	else if (true == IsFirstinflectionPoint)
	{
		XSpeed -= WhispySpeed * Whispy_DecelectionRatio * _Delta;
		YSpeed -= WhispySpeed * WhispyYSpeedRatio * _Delta;

		MoveSpeed = float4{ XSpeed , YSpeed };

		if (abs(XSpeed) > abs(XOriginSpeed))
		{
			IsSecondinflectionPoint = true;
		}
	}




	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	if (GetCameraPos().X > GetPos().X || GetPos().X > GetCameraPos().X + WinScale.X)
	{
		ReleaseThisList();
		Death();
		EffectPointerRelease();
		return;
	}


	AddPos(MoveSpeed * _Delta);
	
	
	AbilityToActorCollisionCheck(CollisionOrder::PlayerBody);
}




void Boss_WhispyEffect::DataStructRelease()
{
	ReleaseThisList();
}



void Boss_WhispyEffect::ReleaseThisList()
{
	WhispyWood* WhispyWoodPtr = WhispyWood::GetWhispyWoodPtr();
	if (nullptr == WhispyWoodPtr)
	{
		MsgBoxAssert("Ŀ�� �������� �ʽ��ϴ�.");
		return;
	}

	std::list<Boss_WhispyEffect*>& WhispyList = WhispyWoodPtr->GetWhispyList();
	WhispyList.remove(this);
}



/* �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ� */


void Boss_WhispyEffect::LevelEnd()
{
	ReleaseThisList();
	Death();
	EffectPointerRelease();
}



/*
*	1. ���� �������� 1:4 ������ �� ���ư���.
*	2. ���� ������ �����ϸ� X �ӵ��� 0���� �ǰ� �ϰ� Y�� ���� ��������.
*	3. X�ӵ��� 0�� �Ǹ� �ٽ� ���� �ӵ��� �ǵ��ư��� Y�� ���� �ӵ��� ���ư���.
*	4. �� �ٱ��� ������ Death ��Ű�� �����͸� �ʱ�ȭ�Ѵ�.
* 
*/