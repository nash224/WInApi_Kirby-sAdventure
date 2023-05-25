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

	// �߷� ������
	GravityVector += float4::DOWN * GravityPower * _Delta;

	// �ִ� ���� ����
	if (GravityVector.Y <= - GravityMaxVector * _Delta)
	{
		GravityVector = float4::UP * GravityMaxVector * _Delta;
	}

	// �ִ� �߷� ����
	if (GravityVector.Y >= GravityMaxVector * _Delta)
	{
		GravityVector = float4::DOWN * GravityMaxVector * _Delta;
	}

	AddPos(GravityVector);
}

// �ȼ��� ����
void ActorUtils::SetGroundTexture(const std::string& _GroundTextureName)
{
	GroundTexture = ResourcesManager::GetInst().FindTexture(_GroundTextureName);

	if (nullptr == GroundTexture)
	{
		MsgBoxAssert(" �ȼ��浹 ���� ã�� �� �����ϴ�. "+ _GroundTextureName);
		return;
	}
}

// �ٴ� ���� �ҷ���
int ActorUtils::GetGroundColor(unsigned int _DefaultColor, float4 _Pos/* = float4::ZERO*/)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("�ȼ� �浹 �ؽ�ó�� �������� �ʽ��ϴ�.");
		return 0;
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}

// Ư�� ��ü�� �߳��� �ٴ� ����
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

