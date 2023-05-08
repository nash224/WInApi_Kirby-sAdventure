#pragma once

// 설명 :
class GameEngineMath
{

};

class float4
{
public:
	static const float4 Zero;
	// 실수는 부동소수점 방식을 사용하고 있어 표현방식에 미세한 오차가 있을 수 있음으로
	// 등호연산자를 사용하면 원하는 결과가 나오지 않을 수 있다.
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;
	float W = 1.0f;

	// 내 위치
	inline int iX() const
	{
		return static_cast<int>(X);
	}


	inline int iY() const
	{
		return static_cast<int>(Y);
	}

	inline int ihX() const
	{
		return static_cast<int>(X * 0.5f);
	}


	inline int ihY() const
	{
		return static_cast<int>(Y * 0.5f);
	}



	float4& operator+=(const float4& _float)
	{
		X += _float.X;
		Y += _float.Y;
		Z += _float.Z;

		return *this;
	}


private:

};

