#pragma once
#include "Item.h"


// 설명 :
class WanderingStar : public Item
{
public:
	// constrcuter destructer
	WanderingStar();
	~WanderingStar();

	// delete Function
	WanderingStar(const WanderingStar& _Other) = delete;
	WanderingStar(WanderingStar&& _Other) noexcept = delete;
	WanderingStar& operator=(const WanderingStar& _Other) = delete;
	WanderingStar& operator=(WanderingStar&& _Other) noexcept = delete;


	template<typename EnumType>
	void init(const float4& _MasterPos, const float4& _MasterScale, EnumType _Order)
	{
		init(_MasterPos, _MasterScale, static_cast<int>(_Order));
	}

	void init(const float4& _MasterPos, const float4& _MasterScale, int _Order);


protected:

	void IdleStart() override;
	void BounceOffStart() override;
	void BeInhaledStart() override;


	void IdleUpdate(float _Delta) override;
	void BounceOffUpdate(float _Delta) override;
	void BeInhaledUpdate(float _Delta) override;

	
	void CheckStarCollision();


private:
	// 상태관련 변수
	const float m_XSpeed = 160.0f;

	float StarLive_Time = 0.0f;
	const float StarLive_InitialTime = 7.0f;
	const float Star_ReduceTime_per_Bounce = 1.0f;



	const float v_Bounce_Power = 600.0f;





	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void LevelEnd() override;



	// 디버깅
	void ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);
};

