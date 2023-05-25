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

float4 ActorUtils::ActorCameraPos()
{
	return GetPos() - GetLevel()->GetMainCamera()->GetPos();
}

void ActorUtils::Gravity(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	// 중력 보간법
	GravityVector += float4::DOWN * GravityPower * _Delta;

	// 최대 점프 제한
	if (GravityVector.Y <= - GravityMaxVector * _Delta)
	{
		GravityVector = float4::UP * GravityMaxVector * _Delta;
	}

	// 최대 중력 제한
	if (GravityVector.Y >= GravityMaxVector * _Delta)
	{
		GravityVector = float4::DOWN * GravityMaxVector * _Delta;
	}

	AddPos(GravityVector);
}

// 픽셀맵 세팅
void ActorUtils::SetGroundTexture(const std::string& _GroundTextureName)
{
	GroundTexture = ResourcesManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTexture)
	{
		MsgBoxAssert(" 픽셀충돌 맵을 찾을 수 없습니다. "+ _GroundTextureName);
		return;
	}
}

// 바닥 색을 불러옴
int ActorUtils::GetGroundColor(unsigned int _DefaultColor, float4 _Pos/* = float4::ZERO*/)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("픽셀 충돌 텍스처가 존재하지 않습니다.");
		return 0;
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}

// 특정 객체의 발끝에 바닥 여부
void ActorUtils::GroundCheck()
{
	unsigned int LeftBottomColor = GetGroundColor(RGB(255, 255, 255), GroundLeftCheckPoint);
	unsigned int RightBottomColor = GetGroundColor(RGB(255, 255, 255), GroundRightCheckPoint);
	if ((RGB(0, 255, 255) == LeftBottomColor || (RGB(0, 0, 255) == LeftBottomColor) ||
		RGB(0, 255, 255) == RightBottomColor) || (RGB(0, 0, 255) == RightBottomColor))
	{
		isGround = true;
		return;
	}

	isGround = false;
}

bool ActorUtils::CeilingCheck()
{
	unsigned int LeftTopColor = GetGroundColor(RGB(255, 255, 255), CeilLeftCheckPoint);
	unsigned int RightTopColor = GetGroundColor(RGB(255, 255, 255), CeilRightCheckPoint);
	if ((RGB(0, 255, 255) == LeftTopColor || (RGB(0, 255, 255) == RightTopColor)))
	{
		return true;
	}

	return false;
}


bool ActorUtils::CheckLeftWall()
{
	if (Dir == ActorDir::Left)
	{
		unsigned int ColorBottom = GetGroundColor(RGB(255, 255, 255), WallBotLeftCheckPoint);
		unsigned int ColorTop = GetGroundColor(RGB(255, 255, 255), WallTopLeftCheckPoint);
		if (ColorBottom == RGB(0, 255, 255) || ColorTop == RGB(0, 255, 255))
		{
			return true;
		}
	}

	return false;
}

bool ActorUtils::CheckRightWall()
{
	if (Dir == ActorDir::Right)
	{
		unsigned int ColorBottom = GetGroundColor(RGB(255, 255, 255), WallBotRightCheckPoint);
		unsigned int ColorTop = GetGroundColor(RGB(255, 255, 255), WallTopRightCheckPoint);
		if (ColorBottom == RGB(0, 255, 255) || ColorTop == RGB(0, 255, 255))
		{
			return true;
		}
	}
	return false;
}

bool ActorUtils::CheckLeftWallSpeedBased()
{
	if (CurrentSpeed < 0.0f)
	{
		unsigned int ColorBottom = GetGroundColor(RGB(255, 255, 255), WallBotLeftCheckPoint);
		unsigned int ColorTop = GetGroundColor(RGB(255, 255, 255), WallTopLeftCheckPoint);
		if (ColorBottom == RGB(0, 255, 255) || ColorTop == RGB(0, 255, 255))
		{
			return true;
		}
	}

	return false;
}

bool ActorUtils::CheckRightWallSpeedBased()
{
	if (CurrentSpeed > 0.0f)
	{
		unsigned int ColorBottom = GetGroundColor(RGB(255, 255, 255), WallBotRightCheckPoint);
		unsigned int ColorTop = GetGroundColor(RGB(255, 255, 255), WallTopRightCheckPoint);
		if (ColorBottom == RGB(0, 255, 255) || ColorTop == RGB(0, 255, 255))
		{
			return true;
		}
	}

	return false;
}

void ActorUtils::SetCheckPoint(const float4& _ScaleSize)
{
	GroundLeftCheckPoint =   { -_ScaleSize.X + CHECKGROUNDGAP , 0.0f };
	GroundRightCheckPoint =  { _ScaleSize.X + -CHECKGROUNDGAP , 0.0f };
	WallBotLeftCheckPoint =  { -_ScaleSize.X + CHECKWALLWIDTHHGAP , -CHECKWALLHEIGHTHGAP };
	WallTopLeftCheckPoint =  { -_ScaleSize.X + CHECKWALLWIDTHHGAP , -_ScaleSize.Y + CHECKWALLHEIGHTHGAP };
	WallBotRightCheckPoint = { _ScaleSize.X + -CHECKWALLWIDTHHGAP , -CHECKWALLHEIGHTHGAP };
	WallTopRightCheckPoint = { _ScaleSize.X + -CHECKWALLWIDTHHGAP , -_ScaleSize.Y + CHECKWALLHEIGHTHGAP };
	CeilLeftCheckPoint =     { -_ScaleSize.X + CHECKGROUNDGAP , -_ScaleSize.Y };
	CeilRightCheckPoint =    { _ScaleSize.X + -CHECKGROUNDGAP , -_ScaleSize.Y };
}

