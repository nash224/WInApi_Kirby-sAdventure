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
	// 렌더러 생성
	MainRenderer = CreateRenderer(RenderOrder::AbillityEffect);
	if (nullptr == MainRenderer)
	{
		MsgBoxAssert("랜더러가 널일 이유가 없어..");
		return;
	}

	// 이미지 로드
	GameEngineWindowTexture* Texture = GlobalContents::TextureFileLoad("WhispyWood_ExhaleEffect_1x1_48x48.bmp", "Resources\\Effect\\SkillEffect");
	if (nullptr == Texture)
	{
		MsgBoxAssert("텍스처를 읽어오지 못했습니다.");
		return;
	}

	Scale = Texture->GetScale();

	// 세팅
	MainRenderer->SetTexture("WhispyWood_ExhaleEffect_1x1_48x48.bmp");

	EffectDir = float4::LEFT;
}



// 생성 위치 설정
void Boss_WhispyEffect::init(const float4& _MasterPos, const float4& _MaterScale)
{
	SetPos(_MasterPos + EffectDir * (_MaterScale.Half().X + Scale.Half().X) + float4{ 0.0f , 36.0f });

	EffectDir = float4{ -4.0f , 1.0f }.NormalizeReturn();
	XSpeed = EffectDir.X * WhispySpeed;
	YSpeed = EffectDir.Y * WhispySpeed;
	XOriginSpeed = XSpeed;
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void Boss_WhispyEffect::Update(float _Delta)
{
	float4 MoveSpeed = float4::ZERO;


	Current_XDsitance += XSpeed * _Delta;
	// 방향이 변하기 전 또는 마지막 운동힘 
	if (abs(Current_XDsitance) < Whispy_ChangeDir_XDistance || true == IsSecondinflectionPoint)
	{
		MoveSpeed = EffectDir * WhispySpeed;
	}
	// 변하고 XSpeed가 0이 되기까지의 운동힘
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
	// 속도의 변곡점부터 원래 속도로 돌아오기 전의 운동힘
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
		MsgBoxAssert("커비가 존재하지 않습니다.");
		return;
	}

	std::list<Boss_WhispyEffect*>& WhispyList = WhispyWoodPtr->GetWhispyList();
	WhispyList.remove(this);
}



/* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */


void Boss_WhispyEffect::LevelEnd()
{
	ReleaseThisList();
	Death();
	EffectPointerRelease();
}



/*
*	1. 지정 범위까지 1:4 각도로 로 날아간다.
*	2. 일정 범위로 도달하면 X 속도가 0으로 되게 하고 Y도 점점 빨라진다.
*	3. X속도가 0이 되면 다시 원래 속도로 되돌아가고 Y도 원래 속도로 돌아간다.
*	4. 맵 바깥을 나가면 Death 시키고 포인터를 초기화한다.
* 
*/