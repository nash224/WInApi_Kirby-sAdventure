#pragma once

// 설명 :
class GameEngineMath
{

};

class float4
{
public:
	float X;
	float Y;
	float Z;
	float W;

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

