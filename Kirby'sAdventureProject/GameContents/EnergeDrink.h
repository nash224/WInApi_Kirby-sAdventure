#pragma once
#include "Item.h"


// ���� : Ŀ�� ��ܸ��ô� ���ֽ��Դϴ�. ü�� 2ĭ�� ä���ݴϴ�.
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
	// GameEngineObject ���
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;

	// GameEngineLevel ���
	void LevelEnd() override;


	// this
	void IdleStart() override;
	void IdleUpdate(float _Delta) override;


	// �����
	void ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);
};

