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



// ī�޶� ������ ���� ��ġ
float4 ContentsActor::ActorCameraPos()
{
	static float4 ReturnValue;

	GameEngineLevel* CurLevelPtr = GetLevel();
	if (nullptr == CurLevelPtr)
	{
		MsgBoxAssert("ī�޶� �ҷ����� ���߽��ϴ�.");
		return ReturnValue;
	}

	GameEngineCamera* MainCameraPtr = CurLevelPtr->GetMainCamera();
	if (nullptr == MainCameraPtr)
	{
		MsgBoxAssert("ī�޶� �ҷ����� ���߽��ϴ�.");
		return ReturnValue;
	}


	return GetPos() - MainCameraPtr->GetPos();
}




// ���� ��ġ�� ��Ʈ�� �� ��ȯ
int ContentsActor::GetGroundColor(unsigned int _DefaultColor, float4 _Pos/* = float4::ZERO*/)
{
	if (nullptr == GroundTexture)
	{
		MsgBoxAssert("�ȼ� �浹 �ؽ�ó�� �������� �ʽ��ϴ�.");
		return 0;
	}

	return GroundTexture->GetColor(_DefaultColor, GetPos() + _Pos);
}




// X�� ����
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

// X�� �ӵ� ����
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

// X�� �ӵ� ������Ʈ
void ContentsActor::HorizontalUpdate(float _Delta)
{
	AddPos(float4{ CurrentSpeed * _Delta , 0.0f });
}
