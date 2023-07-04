#include "ActorUtils.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/ResourcesManager.h>
#include <GameEngineCore/GameEngineCollision.h>



ActorUtils::ActorUtils() 
{
}

ActorUtils::~ActorUtils() 
{
}



float4 ActorUtils::GetDirUnitVector() const
{
	float4 ActorDirUnitVector = float4::ZERO;
	if (ActorDir::Left == Dir)
	{
		ActorDirUnitVector = float4::LEFT;
	}
	else if (ActorDir::Right == Dir)
	{
		ActorDirUnitVector = float4::RIGHT;
	}

	return ActorDirUnitVector;
}





void ActorUtils::Gravity(float _Delta)
{
	// 중력 보간법
	GravityVector += float4::DOWN * GravityPower * _Delta;
}

void ActorUtils::ReverseGravity(float _Delta)
{
	// 중력 보간법
	GravityVector += float4::UP * GravityPower * _Delta;
}

void ActorUtils::GravityLimit(float _Delta)
{
	// 최대 중력 제한
	if (GravityVector.Y >= GravityMaxVector * AirResistance)
	{
		GravityVector = float4::DOWN * GravityMaxVector * AirResistance;
	}
}

void ActorUtils::VerticalUpdate(float _Delta)
{
	if (false == IsGravity)
	{
		return;
	}

	AddPos(GravityVector * _Delta);
}


void ActorUtils::VerticalDecelerationUpdate(float _Speed, float _Delta)
{
	if (CurentVerticalSpeed < 0.0f)
	{
		CurentVerticalSpeed -= _Speed * _Delta;

		if (CurentVerticalSpeed > 0.0f)
		{
			CurentVerticalSpeed = 0.0f;
		}
	}
	else if (CurentVerticalSpeed > 0.0f)
	{
		CurentVerticalSpeed += _Speed * _Delta;

		if (CurentVerticalSpeed < 0.0f)
		{
			CurentVerticalSpeed = 0.0f;
		}
	}
}

void ActorUtils::VerticalSpeedLimitBasedlevitation(float _Speed)
{
	if ((CurentVerticalSpeed > _Speed || CurentVerticalSpeed < -_Speed))
	{
		if (CurentVerticalSpeed <= -_Speed)
		{
			CurentVerticalSpeed = -_Speed;
		}

		if (CurentVerticalSpeed >= _Speed)
		{
			CurentVerticalSpeed = _Speed;
		}
	}
}

void ActorUtils::VerticalUpdateBasedlevitation(float _Delta)
{
	AddPos(float4{ 0.0f , CurentVerticalSpeed * _Delta });
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
int ActorUtils::GetGroundColor(unsigned int _DefaultColor /*= RGB(255, 255, 0)*/, float4 _Pos/* = float4::ZERO*/)
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

bool ActorUtils::CheckLeftWallBasedSpeed(unsigned int _DefaultColor)
{
	if (CurrentSpeed < 0.0f)
	{
		unsigned int ColorBottom = GetGroundColor(_DefaultColor, WallBotLeftCheckPoint);
		unsigned int ColorTop = GetGroundColor(_DefaultColor, WallTopLeftCheckPoint);
		if (ColorBottom == RGB(0, 255, 255) || ColorTop == RGB(0, 255, 255))
		{
			return true;
		}
	}

	return false;
}

bool ActorUtils::CheckRightWallBasedSpeed(unsigned int _DefaultColor)
{
	if (CurrentSpeed > 0.0f)
	{
		unsigned int ColorBottom = GetGroundColor(_DefaultColor, WallBotRightCheckPoint);
		unsigned int ColorTop = GetGroundColor(_DefaultColor, WallTopRightCheckPoint);
		if (ColorBottom == RGB(0, 255, 255) || ColorTop == RGB(0, 255, 255))
		{
			return true;
		}
	}

	return false;
}




bool ActorUtils::CheckMapLeftWallBasedSpeed(unsigned int _DefaultColor)
{
	if (CurrentSpeed < 0.0f)
	{
		unsigned int ColorBottom = GetGroundColor(_DefaultColor, WallBotLeftCheckPoint);
		unsigned int ColorTop = GetGroundColor(_DefaultColor, WallTopLeftCheckPoint);
		if (ColorBottom == RGB(255, 255, 0) || ColorTop == RGB(255, 255, 0))
		{
			return true;
		}
	}

	return false;
}

bool ActorUtils::CheckMapRightWallBasedSpeed(unsigned int _DefaultColor)
{
	if (CurrentSpeed > 0.0f)
	{
		unsigned int ColorBottom = GetGroundColor(_DefaultColor, WallBotRightCheckPoint);
		unsigned int ColorTop = GetGroundColor(_DefaultColor, WallTopRightCheckPoint);
		if (ColorBottom == RGB(255, 255, 0) || ColorTop == RGB(255, 255, 0))
		{
			return true;
		}
	}

	return false;
}






bool ActorUtils::CheckCeilingBasedSpeed(unsigned int _DefaultColor)
{
	if (GravityVector.Y < 0.0f)
	{
		unsigned int ColorLeft = GetGroundColor(_DefaultColor, CeilLeftCheckPoint);
		unsigned int ColorRight = GetGroundColor(_DefaultColor, CeilRightCheckPoint);
		if (ColorLeft == RGB(0, 255, 255) || ColorRight == RGB(0, 255, 255))
		{
			return true;
		}
	}

	return false;
}



bool ActorUtils::CheckMapCeilingBasedSpeed(unsigned int _DefaultColor)
{
	if (GravityVector.Y < 0.0f)
	{
		unsigned int ColorLeft = GetGroundColor(_DefaultColor, CeilLeftCheckPoint);
		unsigned int ColorRight = GetGroundColor(_DefaultColor, CeilRightCheckPoint);
		if (ColorLeft == RGB(255, 255, 0) || ColorRight == RGB(255, 255, 0))
		{
			return true;
		}
	}

	return false;
}



void ActorUtils::BlockedByWall()
{
	if (true == CheckLeftWallBasedSpeed() && CurrentSpeed < 0.0f)
	{
		CurrentSpeed = 0.0f;
	}
	if (true == CheckRightWallBasedSpeed() && CurrentSpeed > 0.0f)
	{
		CurrentSpeed = 0.0f;
	}

	{
		unsigned int BottomWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallBotLeftCheckPoint + float4{ CHECKGAP , 0.0f });
		unsigned int TopWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallTopLeftCheckPoint + float4{ CHECKGAP , 0.0f });

		if ((BottomWallCheckColor == RGB(0, 255, 255)) || (TopWallCheckColor == RGB(0, 255, 255)))
		{
			while ((BottomWallCheckColor == RGB(0, 255, 255)) || (TopWallCheckColor == RGB(0, 255, 255)))
			{
				BottomWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallBotLeftCheckPoint + float4{ CHECKGAP , 0.0f });
				TopWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallTopLeftCheckPoint + float4{ CHECKGAP , 0.0f });
				AddPos(float4::RIGHT * 3);
			}
		}
	}

	{
		unsigned int BottomWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallBotRightCheckPoint + float4{ -CHECKGAP , 0.0f });
		unsigned int TopWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallTopRightCheckPoint + float4{ -CHECKGAP , 0.0f });

		if ((BottomWallCheckColor == RGB(0, 255, 255)) || (TopWallCheckColor == RGB(0, 255, 255)))
		{
			while ((BottomWallCheckColor == RGB(0, 255, 255)) || (TopWallCheckColor == RGB(0, 255, 255)))
			{
				BottomWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallBotRightCheckPoint + float4{ -CHECKGAP , 0.0f });
				TopWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallTopRightCheckPoint + float4{ -CHECKGAP , 0.0f });
				AddPos(float4::LEFT * 3);
			}
		}
	}
}

void ActorUtils::BlockedByGround()
{
	unsigned int LeftGroundCheckColor = GetGroundColor(RGB(255, 255, 255), GroundLeftCheckPoint + float4{ CHECKGAP , -CHECKGAP });
	unsigned int RightGroundCheckColor = GetGroundColor(RGB(255, 255, 255), GroundRightCheckPoint + float4{ -CHECKGAP , -CHECKGAP });

	if ((LeftGroundCheckColor == RGB(0, 255, 255)) || (RightGroundCheckColor == RGB(0, 255, 255)))
	{
		while ((LeftGroundCheckColor == RGB(0, 255, 255)) || (RightGroundCheckColor == RGB(0, 255, 255)))
		{
			LeftGroundCheckColor = GetGroundColor(RGB(255, 255, 255), GroundLeftCheckPoint + float4{ CHECKGAP , -CHECKGAP });
			RightGroundCheckColor = GetGroundColor(RGB(255, 255, 255), GroundRightCheckPoint + float4{ -CHECKGAP , -CHECKGAP });
			AddPos(float4::UP * 3);
		}
	}
}

void ActorUtils::BlockedByCeiling()
{
	unsigned int LeftCeilingCheckColor = GetGroundColor(RGB(255, 255, 255), CeilLeftCheckPoint + float4{ CHECKGAP , CHECKGAP });
	unsigned int RightCeilingCheckColor = GetGroundColor(RGB(255, 255, 255), CeilRightCheckPoint + float4{ -CHECKGAP , CHECKGAP });

	if ((LeftCeilingCheckColor == RGB(0, 255, 255)) || (RightCeilingCheckColor == RGB(0, 255, 255)))
	{
		while ((LeftCeilingCheckColor == RGB(0, 255, 255)) || (RightCeilingCheckColor == RGB(0, 255, 255)))
		{
			LeftCeilingCheckColor = GetGroundColor(RGB(255, 255, 255), CeilLeftCheckPoint + float4{ CHECKGAP , CHECKGAP });
			RightCeilingCheckColor = GetGroundColor(RGB(255, 255, 255), CeilRightCheckPoint + float4{ -CHECKGAP , CHECKGAP });
			AddPos(float4::DOWN * 3);
		}
	}
}


void ActorUtils::BlockedByAll()
{
	if (true == CheckMapLeftWallBasedSpeed(RGB(255, 255, 0)))
	{
		CurrentSpeed = 0.0f;
	}
	if (true == CheckMapRightWallBasedSpeed(RGB(255, 255, 0)))
	{
		CurrentSpeed = 0.0f;
	}

	{
		unsigned int BottomWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallBotLeftCheckPoint + float4{ CHECKGAP , 0.0f });
		unsigned int TopWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallTopLeftCheckPoint + float4{ CHECKGAP , 0.0f });

		if ((BottomWallCheckColor == RGB(255, 255, 0)) || (TopWallCheckColor == RGB(255, 255, 0)))
		{
			while ((BottomWallCheckColor == RGB(255, 255, 0)) || (TopWallCheckColor == RGB(255, 255, 0)))
			{
				BottomWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallBotLeftCheckPoint + float4{ CHECKGAP , 0.0f });
				TopWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallTopLeftCheckPoint + float4{ CHECKGAP , 0.0f });
				AddPos(float4::RIGHT * 3);
			}
		}
	}

	{
		unsigned int BottomWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallBotRightCheckPoint + float4{ -CHECKGAP , 0.0f });
		unsigned int TopWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallTopRightCheckPoint + float4{ -CHECKGAP , 0.0f });

		if ((BottomWallCheckColor == RGB(255, 255, 0)) || (TopWallCheckColor == RGB(255, 255, 0)))
		{
			while ((BottomWallCheckColor == RGB(255, 255, 0)) || (TopWallCheckColor == RGB(255, 255, 0)))
			{
				BottomWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallBotRightCheckPoint + float4{ -CHECKGAP , 0.0f });
				TopWallCheckColor = GetGroundColor(RGB(255, 255, 255), WallTopRightCheckPoint + float4{ -CHECKGAP , 0.0f });
				AddPos(float4::LEFT * 3);
			}
		}
	}


	if (true == CheckMapCeilingBasedSpeed(RGB(255, 255, 0)))
	{
		GravityReset();
	}

	unsigned int LeftCeilingCheckColor = GetGroundColor(RGB(255, 255, 255), CeilLeftCheckPoint + float4{ CHECKGAP , CHECKGAP });
	unsigned int RightCeilingCheckColor = GetGroundColor(RGB(255, 255, 255), CeilRightCheckPoint + float4{ -CHECKGAP , CHECKGAP });

	if ((LeftCeilingCheckColor == RGB(255, 255, 0)))
	{
		while ((LeftCeilingCheckColor == RGB(255, 255, 0)))
		{
			AddPos(float4::DOWN * 3);
			LeftCeilingCheckColor = GetGroundColor(RGB(255, 255, 255), CeilLeftCheckPoint + float4{ CHECKGAP , CHECKGAP });
			RightCeilingCheckColor = GetGroundColor(RGB(255, 255, 255), CeilRightCheckPoint + float4{ -CHECKGAP , CHECKGAP });
		}
	}

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

bool ActorUtils::IsSolidGround()
{
	unsigned int LeftBottomColor = GetGroundColor(RGB(255, 255, 255), GroundLeftCheckPoint);
	unsigned int RightBottomColor = GetGroundColor(RGB(255, 255, 255), GroundRightCheckPoint);
	if ((RGB(0, 255, 255) == LeftBottomColor || RGB(0, 255, 255) == RightBottomColor))
	{
		return true;
	}

	return false;
}

bool ActorUtils::IsPassableGround()
{
	unsigned int LeftBottomColor = GetGroundColor(RGB(255, 255, 255), GroundLeftCheckPoint);
	unsigned int RightBottomColor = GetGroundColor(RGB(255, 255, 255), GroundRightCheckPoint);
	if ((RGB(0, 0, 255) == LeftBottomColor || RGB(0, 0, 255) == RightBottomColor))
	{
		return true;
	}

	return false;
}

void ActorUtils::ActorCollisionDetectionPointRender()
{
	HDC BackDC = GameEngineWindow::MainWindow.GetBackBuffer()->GetImageDC();

	CollisionData Data;

	// 원점
	Data.Pos = ActorCameraPos();
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 바닥 왼쪽
	Data.Pos = ActorCameraPos() + GroundLeftCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 바닥 오른쪽
	Data.Pos = ActorCameraPos() + GroundRightCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 벽 하단왼쪽
	Data.Pos = ActorCameraPos() + WallBotLeftCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 벽 상단왼쪽
	Data.Pos = ActorCameraPos() + WallTopLeftCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 벽 하단오른쪽
	Data.Pos = ActorCameraPos() + WallBotRightCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 벽 상단오른쪽
	Data.Pos = ActorCameraPos() + WallTopRightCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 천장 왼쪽
	Data.Pos = ActorCameraPos() + CeilLeftCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
	// 천장 오른쪽
	Data.Pos = ActorCameraPos() + CeilRightCheckPoint;
	Data.Scale = { 5 , 5 };
	Rectangle(BackDC, Data.iLeft(), Data.iTop(), Data.iRight(), Data.iBot());
}

