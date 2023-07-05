#pragma once
#include "Item.h"


// 설명 : 커비가 즐겨마시는 고주스입니다. 체력 2칸을 채워줍니다.
class EnergeDrink : public Item
{
public:
	// constrcuter destructer
	EnergeDrink();
	~EnergeDrink();

	// delete Function
	EnergeDrink(const EnergeDrink& _Other) = delete;
	EnergeDrink(EnergeDrink&& _Other) noexcept = delete;
	EnergeDrink& operator=(const EnergeDrink& _Other) = delete;
	EnergeDrink& operator=(EnergeDrink&& _Other) noexcept = delete;


	void init(const float4& _Pos);


protected:

private:
	// GameEngineObject 상속
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	// GameEngineLevel 상속
	void LevelEnd() override;


	// this
	void IdleStart() override;
	void IdleUpdate(float _Delta) override;


	// 디버깅
	void ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);
};

