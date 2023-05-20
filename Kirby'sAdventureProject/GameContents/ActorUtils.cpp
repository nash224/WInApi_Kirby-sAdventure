#include "ActorUtils.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourceManager.h>

ActorUtils::ActorUtils() 
{
}

ActorUtils::~ActorUtils() 
{
}


void ActorUtils::CameraFocus()
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	GetLevel()->GetMainCamera()->SetPos(GetPos() - WinScale.GetHalf());




	//if (true == GameEngineInput::IsPress('A') || GameEngineInput::IsPress('D'))
//{
//	if (LevelPlayer->GetPos().iX() > GameEngineWindow::MainWindow.GetScale().GetHalf().iX() &&
//		LevelPlayer->GetPos().iX() <
//		LevelBackGround->GetScale().iX() - GameEngineWindow::MainWindow.GetScale().GetHalf().iX())
//	{
//		GetMainCamera()->AddPos(float4::XValue(LevelPlayer->GetMovePos()));
//	}
//}
//if (true == GameEngineInput::IsPress('W') || GameEngineInput::IsPress('S'))
//{
//	if (LevelPlayer->GetPos().iY() > GameEngineWindow::MainWindow.GetScale().GetHalf().iY() &&
//		LevelPlayer->GetPos().iY() <
//		LevelBackGround->GetScale().iY() - GameEngineWindow::MainWindow.GetScale().GetHalf().iY())
//	{
//		GetMainCamera()->AddPos(float4::YValue(LevelPlayer->GetMovePos()));
//	}
//}


}

void ActorUtils::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	GravityVector = float4::DOWN * GravityPower;

	AddPos(GravityVector);
}

void ActorUtils::SetGroundTexture(const std::string& _GroundTextureName)
{
	GroundTexture = ResourceManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTexture)
	{
		MsgBoxAssert(" 픽셀충돌 맵을 찾을 수 없습니다. "+ _GroundTextureName);
		return;
	}
}

int ActorUtils::GetGroundColor(unsigned int _DefaultColor, float4 _Pos/* = float4::ZERO*/)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("픽셀 충돌 텍스처가 존재하지 않습니다.");
		return 0;
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}

void ActorUtils::GroundCheck(float _XScaleSize)
{
	unsigned int LeftBottomColor = GetGroundColor(RGB(255, 255, 255), float4{ -_XScaleSize + 3.0f , 0.0f });
	unsigned int RightBottomColor = GetGroundColor(RGB(255, 255, 255), float4{ _XScaleSize + -3.0f , 0.0f });
	if (RGB(255, 255, 255) == LeftBottomColor &&
		RGB(255, 255, 255) == RightBottomColor)
	{
		isGround = false;
	}
	else
	{
		isGround = true;
	}
}