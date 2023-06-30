#include "VegetableValleyCutScene.h"
#include "ContentsEnum.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCore.h>


#include "GlobalContents.h"
#include "FadeObject.h"


VegetableValleyCutScene::VegetableValleyCutScene() 
{
}

VegetableValleyCutScene::~VegetableValleyCutScene() 
{
}


// 4 Front 2 Back 2 Front
// 0/1 2 Back


void VegetableValleyCutScene::Start()
{
	KirbyActor.ActorRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == KirbyActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	KnightActor.ActorRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == KnightActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	SwordActor.ActorRenderer = CreateRenderer(RenderOrder::Play);
	if (nullptr == SwordActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 생성하지 못했습니다.");
		return;
	}

	
	// 파일로드
	GlobalContents::SpriteFileLoad("Scene_Kirby_Actor.bmp", "Resources\\Scene", 12, 4);
	GlobalContents::SpriteFileLoad("Scene_Knight_Actor.bmp", "Resources\\Scene", 4, 2);
	GlobalContents::SpriteFileLoad("Scene_Sword_Actor.bmp", "Resources\\Scene", 5, 1);

	// 애니메이션 설정
	KirbyActor.ActorRenderer->CreateAnimation("Confront", "Scene_Kirby_Actor.bmp", 0, 0, 0.6f, false);
	KirbyActor.ActorRenderer->CreateAnimation("Press", "Scene_Kirby_Actor.bmp", 1, 0, Press_StateDuration * 0.5f, false);
	KirbyActor.ActorRenderer->CreateAnimation("ShedSword", "Scene_Kirby_Actor.bmp", 2, 3, EmbarrassmentTime, false);
	KirbyActor.ActorRenderer->CreateAnimation("KirbyInhale", "Scene_Kirby_Actor.bmp", 4, 4, 0.1f, false);
	KirbyActor.ActorRenderer->CreateAnimation("EattedKnight", "Scene_Kirby_Actor.bmp", 5, 6, 0.24f, false);
	KirbyActor.ActorRenderer->CreateAnimation("GetAbility", "Scene_Kirby_Actor.bmp", 7, 36, 0.04f, false);
	KirbyActor.ActorRenderer->ChangeAnimation("Confront");


	KnightActor.ActorRenderer->CreateAnimation("Confront", "Scene_Knight_Actor.bmp", 1, 1, 0.6f, false);
	KnightActor.ActorRenderer->CreateAnimation("Press", "Scene_Knight_Actor.bmp", 0, 1, Press_StateDuration * 0.5f, false);
	KnightActor.ActorRenderer->CreateAnimation("ShedSword", "Scene_Knight_Actor.bmp", 2, 7, 0.1f, false);
	KnightActor.ActorRenderer->FindAnimation("ShedSword")->Inters = { 0.1f , 0.04f , 0.04f , 0.04f , 0.04f , 0.04f };
	KnightActor.ActorRenderer->CreateAnimation("BeInhaled", "Scene_Knight_Actor.bmp", 0, 0, 0.1f, false);
	KnightActor.ActorRenderer->ChangeAnimation("Confront");


	SwordActor.ActorRenderer->CreateAnimation("BounceOff", "Scene_Sword_Actor.bmp", 0, 3, 0.08f, true);
	SwordActor.ActorRenderer->CreateAnimation("StuckBanner", "Scene_Sword_Actor.bmp", 4, 4, 0.1f, false);
	SwordActor.ActorRenderer->ChangeAnimation("BounceOff");


	SetPos(float4::ZERO);



	// 초기 상태
	ChangeState(ValleyCutSceneState::StandBy);


}




void VegetableValleyCutScene::Update(float _Delta)
{
	StateUpdate(_Delta);


	if (true == IsKirbysSword_FlyAway && false == IsSwordStuckedPlank)
	{
		SwordUpdate(_Delta);
	}
}


void VegetableValleyCutScene::StateUpdate(float _Delta)
{
	switch (State)
	{
	case ValleyCutSceneState::StandBy:					return StandByUpdate(_Delta);
	case ValleyCutSceneState::Confront:					return ConfrontUpdate(_Delta);
	case ValleyCutSceneState::Press:					return PressUpdate(_Delta);
	case ValleyCutSceneState::ShedSword:				return ShedSwordUpdate(_Delta);
	case ValleyCutSceneState::KirbyInhale:				return KirbyInhaleUpdate(_Delta);
	case ValleyCutSceneState::EattedKnight:				return EattedKnightUpdate(_Delta);
	case ValleyCutSceneState::GetAbility:				return GetAbilityUpdate(_Delta);
	default:
		break;
	}
}

void VegetableValleyCutScene::ChangeState(ValleyCutSceneState _State)
{
	if (_State != State)
	{
		switch (_State)
		{
		case ValleyCutSceneState::StandBy:						StandByStart();					break;
		case ValleyCutSceneState::Confront:						ConfrontStart();				break;
		case ValleyCutSceneState::Press:						PressStart();					break;
		case ValleyCutSceneState::ShedSword:					ShedSwordStart();				break;
		case ValleyCutSceneState::KirbyInhale:					KirbyInhaleStart();				break;
		case ValleyCutSceneState::EattedKnight:					EattedKnightStart();			break;
		case ValleyCutSceneState::GetAbility:					GetAbilityStart();				break;
		default:
			break;
		}
	}

	State = _State;
}


// 상태 패턴
void VegetableValleyCutScene::ChangeAnimationState(const std::string& _StateName)
{
	CurState = _StateName;
	KirbyActor.ActorRenderer->ChangeAnimation(_StateName);
}




void VegetableValleyCutScene::StandByStart()
{
	if (nullptr == KirbyActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}
	if (nullptr == KnightActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}
	if (nullptr == SwordActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	StateTime = 0.0f;
	KirbyActor.ActorRenderer->Off();
	KnightActor.ActorRenderer->Off();
	SwordActor.ActorRenderer->Off();


	Kirby_FrontNumber = 0;
	Knight_FrontNumber = 0;
}

void VegetableValleyCutScene::StandByUpdate(float _Delta) 
{
	StateTime += _Delta;

	if (StateTime > 1.0f)
	{
		if (nullptr == KirbyActor.ActorRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}
		if (nullptr == KnightActor.ActorRenderer)
		{
			MsgBoxAssert("렌더러를 불러오지 못했습니다.");
			return;
		}


		KirbyActor.ActorRenderer->SetRenderPos(float4{ 480.0f , 384.0f });
		KnightActor.ActorRenderer->SetRenderPos(float4{ 360.0f , 384.0f });

		KirbyActor.ActorRenderer->On();
		KnightActor.ActorRenderer->On();

		ChangeState(ValleyCutSceneState::Confront);
		return;
	}

}



void VegetableValleyCutScene::ConfrontStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	if (nullptr == KirbyActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}
	if (nullptr == KnightActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	if (false == IsKirbysSword_FlyAway)
	{
		ChangeAnimationState("Confront");
	}
	KnightActor.ActorRenderer->ChangeAnimation("Confront");
}

void VegetableValleyCutScene::ConfrontUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > 0.6f)
	{
		if (6 == Kirby_FrontNumber && false == IsKirbysSword_FlyAway)
		{
			ChangeState(ValleyCutSceneState::ShedSword);
			return;
		}

		if (5 == Knight_FrontNumber)
		{
			ChangeState(ValleyCutSceneState::KirbyInhale);
			return;
		}

		ChangeState(ValleyCutSceneState::Press);
		return;
	}
}



void VegetableValleyCutScene::PressStart()
{
	StateTime = 0.0f;
	IsChangeState = false;

	if (nullptr == KnightActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	if (Kirby_FrontNumber <= 3)
	{
		++Kirby_FrontNumber;
		KirbyActor.Scene_XSpeed = -OneStepDecelerationSpeed / Press_StateDuration;
		KnightActor.Scene_XSpeed = -OneStepDecelerationSpeed / Press_StateDuration;
	}
	else if (Knight_FrontNumber <= 1)
	{
		++Knight_FrontNumber;
		KirbyActor.Scene_XSpeed = OneStepDecelerationSpeed / Press_StateDuration;
		KnightActor.Scene_XSpeed = OneStepDecelerationSpeed / Press_StateDuration;
	}
	else if (Knight_FrontNumber == 2 && Kirby_FrontNumber <= 5)
	{
		++Kirby_FrontNumber;
		KirbyActor.Scene_XSpeed = -OneStepDecelerationSpeed / Press_StateDuration;
		KnightActor.Scene_XSpeed = -OneStepDecelerationSpeed / Press_StateDuration;
	}
	else if (Knight_FrontNumber == 2 && Kirby_FrontNumber == 6)
	{
		++Knight_FrontNumber;
		KirbyActor.Scene_XSpeed = TwoStepDecelerationSpeed / Press_StateDuration;
		KnightActor.Scene_XSpeed = 0.0f;
	}
	else if (Knight_FrontNumber >= 3 && Kirby_FrontNumber == 6)
	{
		++Knight_FrontNumber;
		KirbyActor.Scene_XSpeed = TwoStepDecelerationSpeed / Press_StateDuration;
		KnightActor.Scene_XSpeed = TwoStepDecelerationSpeed / Press_StateDuration;
	}

	KnightActor.ActorRenderer->ChangeAnimation("Press");

	if (false == IsKirbysSword_FlyAway)
	{
		ChangeAnimationState("Press");
	}
}

void VegetableValleyCutScene::PressUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > Press_StateDuration)
	{
		StateTime = 0.0f;

		ChangeState(ValleyCutSceneState::Confront);
		return;
	}


	Renderer_DecelerationUpdate(KirbyActor, _Delta, OneStepDecelerationSpeed / Press_StateDuration);
	Renderer_HorizontalMoveUpdate(KirbyActor, _Delta);

	Renderer_DecelerationUpdate(KnightActor, _Delta, OneStepDecelerationSpeed / Press_StateDuration);
	Renderer_HorizontalMoveUpdate(KnightActor, _Delta);
}




void VegetableValleyCutScene::ShedSwordStart()
{
	StateTime = 0.0f;
	IsKirbysSword_FlyAway = false;


	if (nullptr == KnightActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	KnightActor.ActorRenderer->ChangeAnimation("ShedSword");
}


void VegetableValleyCutScene::ShedSwordUpdate(float _Delta)
{
	if (nullptr == KirbyActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	if (nullptr == KnightActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}



	if (false == IsKirbysSword_FlyAway && 2 == KnightActor.ActorRenderer->FindAnimation("ShedSword")->CurFrame)
	{

		if (false == IsKirbysSword_FlyAway)
		{
			if (nullptr == SwordActor.ActorRenderer)
			{
				MsgBoxAssert("렌더러를 불러오지 못했습니다.");
				return;
			}


			KirbyActor.ActorRenderer->ChangeAnimation("ShedSword");
			SwordActor.ActorRenderer->On();
			SwordActor.ActorRenderer->SetRenderPos(KirbyActor.ActorRenderer->GetRenderPos() + float4::LEFT * 48.0f);
			SwordActor.Scene_YSpeed = -600.0f;
			SwordActor.Scene_XSpeed = 160.0f;

			IsKirbysSword_FlyAway = true;
		}

	}

	if (true == IsKirbysSword_FlyAway)
	{
		StateTime += _Delta;

		if (StateTime > EmbarrassmentTime)
		{
			ChangeState(ValleyCutSceneState::Press);
			return;
		}
	}
}


void VegetableValleyCutScene::SwordUpdate(float _Delta)
{
	if (nullptr == SwordActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}
	

	Renderer_Gravity(SwordActor, _Delta, 800.0f);
	Renderer_VerticalUpdate(SwordActor, _Delta);

	Renderer_HorizontalMoveUpdate(SwordActor, _Delta);

	float4 Sword_RenderPos = SwordActor.ActorRenderer->GetRenderPos();

	if (Sword_RenderPos.Y > 575.0f && false == IsSwordStuckedPlank)
	{
		SwordActor.ActorRenderer->SetRenderPos(float4{ Sword_RenderPos.X , 576.0f });
		SwordActor.ActorRenderer->ChangeAnimation("StuckBanner");

		IsSwordStuckedPlank = true;
	}
}





void VegetableValleyCutScene::KirbyInhaleStart()
{
	if (nullptr == KirbyActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
	}

	if (nullptr == KnightActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
	}

	WabbleCount = 0;
	WabbleTime = 0.0f;

	float Kirby_X_RenderPos = KirbyActor.ActorRenderer->GetRenderPos().X;
	float Knight_X_RenderPos = KnightActor.ActorRenderer->GetRenderPos().X;
	
	Actor_MutualDistance = Kirby_X_RenderPos - Knight_X_RenderPos;

	KnightActor.ActorRenderer->ChangeAnimation("BeInhaled");
	ChangeAnimationState("KirbyInhale");
}

void VegetableValleyCutScene::KirbyInhaleUpdate(float _Delta)
{
	if (nullptr == KirbyActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
	}

	if (nullptr == KnightActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
	}


	WabbleTime += _Delta;

	if (WabbleCount != MaxWabbleCount && WabbleTime > WabbleCycle)
	{
		WabbleTime = 0.0f;

		
		float WabbleDistance = 0.0f;
		int WabbleType = WabbleCount % 6;

		switch (WabbleType)
		{
		case 0:
			WabbleDistance = TypeOne_WabbleDistance;
			break;
		case 1:
			WabbleDistance = -TypeOne_WabbleDistance;
			break;
		case 2:
			WabbleDistance = TypeTwo_WabbleDistance;
			break;
		case 3:
			WabbleDistance = -TypeTwo_WabbleDistance;
			break;
		case 4:
			WabbleDistance = TypeThree_WabbleDistance;
			break;
		case 5:
			WabbleDistance = -TypeThree_WabbleDistance;
			break;
		default:
			break;
		}

		KnightActor.ActorRenderer->AddRenderPos(float4{ WabbleDistance , 0.0f });

		++WabbleCount;
	}

	if (WabbleCount != MaxWabbleCount)
	{
		return;
	}


	
	KnightActor.Scene_XSpeed += Actor_MutualDistance / BeInhaledTime * _Delta;;

	Renderer_HorizontalMoveUpdate(KnightActor, _Delta);


	float Kirby_X_RenderPos = KirbyActor.ActorRenderer->GetRenderPos().X;
	float Knight_X_RenderPos = KnightActor.ActorRenderer->GetRenderPos().X;

	if (UnitScale.Half().X > abs(Knight_X_RenderPos - Kirby_X_RenderPos))
	{
		KnightActor.ActorRenderer->Off();

		ChangeState(ValleyCutSceneState::EattedKnight);
		return;
	}
}



void VegetableValleyCutScene::EattedKnightStart()
{
	StateTime = 0.0f;

	ChangeAnimationState("EattedKnight");
}

void VegetableValleyCutScene::EattedKnightUpdate(float _Delta)
{
	StateTime += _Delta;

	if (StateTime > 0.6f)
	{
		ChangeState(ValleyCutSceneState::GetAbility);
		return;
	}
}




void VegetableValleyCutScene::GetAbilityStart()
{
	StateTime = 0.0f;
	IsGetAbilityAnimationEnd = false;
	IsFadeOutStart = false;

	GameEngineLevel* CurLevelPtr = GetLevel();

	FadeObject* LevelFade = CurLevelPtr->CreateActor<FadeObject>(UpdateOrder::UI);
	if (nullptr == LevelFade)
	{
		MsgBoxAssert("생성한 액터가 Null 입니다.");
		return;
	}

	LevelFade->RequestFadeScreen(FadeAlphaValue);

	ChangeAnimationState("GetAbility");
}

void VegetableValleyCutScene::GetAbilityUpdate(float _Delta)
{
	if (nullptr == KirbyActor.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}



	if (28 == KirbyActor.ActorRenderer->FindAnimation("GetAbility")->CurFrame && false == FadeObject::IsFadeScreenRelease)
	{
		FadeObject::IsFadeScreenRelease = true;
	}


	if (false == IsGetAbilityAnimationEnd && true == KirbyActor.ActorRenderer->IsAnimationEnd())
	{
		IsGetAbilityAnimationEnd = true;
	}

	if (true == IsGetAbilityAnimationEnd)
	{
		StateTime += _Delta;

		if (StateTime > 0.6f && false == IsFadeOutStart)
		{
			GameEngineLevel* CurLevelPtr = GetLevel();
			if (nullptr == CurLevelPtr)
			{
				MsgBoxAssert("레벨을 불러오지 못했습니다.");
				return;
			}

			GlobalContents::WhiteFadeOut(CurLevelPtr);

			IsFadeOutStart = true;
		}

		if (StateTime > 1.5f)
		{
			GameEngineCore::ChangeLevel("VegetableValleyHub");
			return;
		}
	}
}


void VegetableValleyCutScene::LevelEnd() 
{

}






void VegetableValleyCutScene::Renderer_DecelerationUpdate(SceneData& _DataStruct, float _Delta, float _Speed)
{
	if (_DataStruct.Scene_XSpeed < 0.0f)
	{
		_DataStruct.Scene_XSpeed += _Speed * _Delta;

		if (_DataStruct.Scene_XSpeed > 0.0f)
		{
			_DataStruct.Scene_XSpeed = 0.0f;
		}
	}
	else if (_DataStruct.Scene_XSpeed > 0.0f)
	{
		_DataStruct.Scene_XSpeed -= _Speed * _Delta;

		if (_DataStruct.Scene_XSpeed < 0.0f)
		{
			_DataStruct.Scene_XSpeed = 0.0f;
		}
	}
}




void VegetableValleyCutScene::Renderer_HorizontalMoveUpdate(SceneData& _DataStruct, float _Delta)
{
	if (nullptr == _DataStruct.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	_DataStruct.ActorRenderer->AddRenderPos(float4{ _DataStruct.Scene_XSpeed * _Delta , 0.0f });
}



void VegetableValleyCutScene::Renderer_Gravity(SceneData& _DataStruct, float _Delta , float _GravityPower)
{
	_DataStruct.Scene_YSpeed += _GravityPower * _Delta;
}

void VegetableValleyCutScene::Renderer_VerticalUpdate(SceneData& _DataStruct, float _Delta)
{
	if (nullptr == _DataStruct.ActorRenderer)
	{
		MsgBoxAssert("렌더러를 불러오지 못했습니다.");
		return;
	}

	_DataStruct.ActorRenderer->AddRenderPos(float4{ 0.0f , _DataStruct.Scene_YSpeed * _Delta });

}