#include "ContentsActor.h"


#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCamera.h>



ContentsActor::ContentsActor() 
{
}

ContentsActor::~ContentsActor() 
{
}



// 카메라 기준의 액터 위치
float4 ContentsActor::ActorCameraPos()
{
	static float4 ReturnValue;

	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("카메라를 불러오지 못했습니다.");
		return ReturnValue;
	}

	GameEngineCamera* MainCameraPtr = CurLevelPtr->GetMainCamera();
	if (nullptr == MainCameraPtr)
	{
		MsgBoxAssert("카메라를 불러오지 못했습니다.");
		return ReturnValue;
	}


	return GetPos() - MainCameraPtr->GetPos();
}




// 지정 위치에 비트맵 색 반환
int ContentsActor::GetGroundColor(unsigned int _DefaultColor, float4 _Pos/* = float4::ZERO*/)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("픽셀 충돌 텍스처가 존재하지 않습니다.");
		return 0;
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}




// X축 감속
void ContentsActor::DecelerationUpdate(float _Delta, float _Speed)
{
	if (CurrentSpeed < 0.0f)
	{
		CurrentSpeed += _Speed * _Delta;

		if (CurrentSpeed > 0.0f)
		{
			CurrentSpeed = 0.0f;
		}
	}
	else if (CurrentSpeed > 0.0f)
	{
		CurrentSpeed -= _Speed * _Delta;

		if (CurrentSpeed < 0.0f)
		{
			CurrentSpeed = 0.0f;
		}
	}
}

// X축 속도 제한
void ContentsActor::HorizontalSpeedLimit(float _Speed)
{
	if ((CurrentSpeed > _Speed || CurrentSpeed < -_Speed))
	{
		if (CurrentSpeed <= -_Speed)
		{
			CurrentSpeed = -_Speed;
		}

		if (CurrentSpeed >= _Speed)
		{
			CurrentSpeed = _Speed;
		}
	}
}

// X축 속도 업데이트
void ContentsActor::HorizontalUpdate(float _Delta)
{
	AddPos(float4{ CurrentSpeed * _Delta , 0.0f });
}
