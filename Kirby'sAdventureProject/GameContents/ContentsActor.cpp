#include "ContentsActor.h"

ContentsActor::ContentsActor() 
{
}

ContentsActor::~ContentsActor() 
{
}


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

void ContentsActor::HorizontalUpdate(float _Delta)
{
	AddPos(float4{ CurrentSpeed * _Delta , 0.0f });
}
