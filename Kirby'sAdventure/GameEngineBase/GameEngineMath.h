#pragma once

// Ό³Έν :
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




	float4& operator+=(const float4& _float)
	{
		X += _float.X;
		Y += _float.Y;
		Z += _float.Z;

		return *this;
	}


private:

};

