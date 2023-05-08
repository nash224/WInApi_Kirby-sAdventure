#pragma once

// ���� :
class GameEngineMath
{

};

class float4
{
public:
	static const float4 Zero;
	// �Ǽ��� �ε��Ҽ��� ����� ����ϰ� �־� ǥ����Ŀ� �̼��� ������ ���� �� ��������
	// ��ȣ�����ڸ� ����ϸ� ���ϴ� ����� ������ ���� �� �ִ�.
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;
	float W = 1.0f;

	// �� ��ġ
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

