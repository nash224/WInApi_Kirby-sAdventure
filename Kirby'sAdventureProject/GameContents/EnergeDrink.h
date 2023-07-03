#pragma once
#include "Item.h"


// Ό³Έν :
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
	void IdleStart() override;
	void IdleUpdate(float _Delta) override;


private:

	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void LevelEnd() override;



	// µπΉφ±λ
	void ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);
};

