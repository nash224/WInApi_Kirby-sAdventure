#pragma once
#include "GameEngineDebug.h"

// 설명 :
class GameEngineMath
{

};

class float4
{
public:
	static const float4 ZERO;
	static const float4 LEFT;
	static const float4 RIGHT;
	static const float4 UP;
	static const float4 DOWN;
	// 실수는 부동소수점 방식을 사용하고 있어 표현방식에 미세한 오차가 있을 수 있음으로
	// 등호연산자를 사용하면 원하는 결과가 나오지 않을 수 있다.
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;
	float W = 1.0f;

	inline int iX() const
	{
		return static_cast<int>(X);
	}

	inline int iY() const
	{
		return static_cast<int>(Y);
	}

	float hX() const
	{
		return X * 0.5f;
	}

	float hY() const
	{
		return Y * 0.5f;
	}

	inline int ihX() const
	{
		return static_cast<int>(X * 0.5f);
	}


	inline int ihY() const
	{
		return static_cast<int>(Y * 0.5f);
	}

	float4 GetHalf() const
	{
		return { hX(), hY(), Z, W };
	}

	bool operator==(const float4& _Value) const
	{
		return X == _Value.X &&
			Y == _Value.Y&&
			Z == _Value.Z;
	}

	float4 operator+(const float4& _Other) const
	{
		float4 ReturnValue;
		ReturnValue.X = X + _Other.X;
		ReturnValue.Y = Y + _Other.Y;
		ReturnValue.Z = Z + _Other.Z;

		return ReturnValue;
	}

	float4& operator+=(const float4& _float)
	{
		X += _float.X;
		Y += _float.Y;
		Z += _float.Z;

		return *this;
	}

	float4 operator-(const float4& _Other) const
	{
		float4 ReturnValue;
		ReturnValue.X = X - _Other.X;
		ReturnValue.Y = Y - _Other.Y;
		ReturnValue.Z = Z - _Other.Z;

		return ReturnValue;
	}

	float4& operator-=(const float4& _float)
	{
		X -= _float.X;
		Y -= _float.Y;
		Z -= _float.Z;

		return *this;
	}


	float4 operator*(const float4& _Other) const
	{
		float4 ReturnValue;
		ReturnValue.X = X * _Other.X;
		ReturnValue.Y = Y * _Other.Y;
		ReturnValue.Z = Z * _Other.Z;

		return ReturnValue;
	}

	float4 operator*(const float _Value) const
	{
		float4 ReturnValue;
		ReturnValue.X = X * _Value;
		ReturnValue.Y = Y * _Value;
		ReturnValue.Z = Z * _Value;

		return ReturnValue;
	}

	float4& operator*=(const float4& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;

		return *this;
	}

	float4& operator*=(const float _Value)
	{
		X *= _Value;
		Y *= _Value;
		Z *= _Value;

		return *this;
	}

	inline void Normalize()
	{
		float Len = Size();

		if (0.0f == Len)
		{
			return;
		}

		X /= Len;
		Y /= Len;
		Z /= Len;
	}

	inline float4 NormalizeReturn()
	{
		float4 Result = *this;
		Result.Normalize();
		return Result;
	}

	inline float Size()
	{
		float Value = X * X + Y * Y;
		return sqrtf(Value);
		
	}

private:

};