#include "ActorUtils.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>

ActorUtils::ActorUtils() 
{
}

ActorUtils::~ActorUtils() 
{
}


void ActorUtils::CameraFocus()
{
	float4 WinScale = GameEngineWindow::MainWindow.GetScale();
	GetLevel()->GetMainCamera()->SetPos(GetPos() - WinScale.Half());




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

	GravityVector += float4::DOWN * GravityPower * _Delta;

	if (GravityVector.Y >= GravityMaxVector * _Delta)
	{
		GravityVector = float4::DOWN * GravityMaxVector * _Delta;
	}

	AddPos(GravityVector);
}

void ActorUtils::SetGroundTexture(const std::string& _GroundTextureName)
{
	GroundTexture = ResourcesManager::GetInst().FindTexture(_GroundTextureName);

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
	unsigned int LeftBottomColor = GetGroundColor(RGB(255, 255, 255), float4{ -_XScaleSize + 12.0f , 0.0f });
	unsigned int RightBottomColor = GetGroundColor(RGB(255, 255, 255), float4{ _XScaleSize + -12.0f , 0.0f });
	if (RGB(255, 255, 255) == LeftBottomColor &&
		RGB(255, 255, 255) == RightBottomColor)
	{
		isGround = false;
		return;
	}

	isGround = true;
}

bool ActorUtils::CheckLeftWall(const float4& _ScaleSize)
{
	if (Dir == ActorDir::Left)
	{
		float4 CheckPosBottom = float4::ZERO;
		float4 CheckPosTop = float4::ZERO;
		CheckPosBottom = { -_ScaleSize.X + 9.0f , -12.0f };
		CheckPosTop = { -_ScaleSize.X + 9.0f , 12.0f - _ScaleSize.Y };

		unsigned int ColorBottom = GetGroundColor(RGB(255, 255, 255), CheckPosBottom);
		unsigned int ColorTop = GetGroundColor(RGB(255, 255, 255), CheckPosTop);
		if (ColorBottom == RGB(0, 255, 255) || ColorTop == RGB(0, 255, 255))
		{
			return true;
		}
	}

	return false;
}

bool ActorUtils::CheckRightWall(const float4& _ScaleSize)
{
	if (Dir == ActorDir::Right)
	{
		float4 CheckPosBottom = float4::ZERO;
		float4 CheckPosTop = float4::ZERO;
		CheckPosBottom = { _ScaleSize.X - 9.0f , -12.0f };
		CheckPosTop = { _ScaleSize.X - 9.0f , 12.0f - _ScaleSize.Y };

		unsigned int ColorBottom = GetGroundColor(RGB(255, 255, 255), CheckPosBottom);
		unsigned int ColorTop = GetGroundColor(RGB(255, 255, 255), CheckPosTop);
		if (ColorBottom == RGB(0, 255, 255) || ColorTop == RGB(0, 255, 255))
		{
			return true;
		}
	}
	return false;
}