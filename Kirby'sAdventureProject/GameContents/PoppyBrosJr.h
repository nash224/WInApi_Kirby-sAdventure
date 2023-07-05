#pragma once
#include "NormalEnemies.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>




// ���� : ����� �ſ� �����ϴ� �������Դϴ�. 
class PoppyBrosJr : public NormalEnemies
{
public:
	// constrcuter destructer
	PoppyBrosJr();
	~PoppyBrosJr();

	// delete Function
	PoppyBrosJr(const PoppyBrosJr& _Other) = delete;
	PoppyBrosJr(PoppyBrosJr&& _Other) noexcept = delete;
	PoppyBrosJr& operator=(const PoppyBrosJr& _Other) = delete;
	PoppyBrosJr& operator=(PoppyBrosJr&& _Other) noexcept = delete;


protected:

private:

	// GameEngineObject ���
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;


	// this
	const float StateChangeTime = 0.1f;


	void AppleRunStart() override;
	void AppleRunUpdate(float _Delta) override;

	void EscapeStart() override;
	void EscapeUpdate(float _Delta) override;

	void IdleStart() override;
	void IdleUpdate(float _Delta) override;

	void JumpStart() override;
	void JumpUpdate(float _Delta) override;

	const float JumpDistance = 5.0f;
	const float Jump_XSpeed = 100.0f;
	const float JumpDuration= 0.05f;


	void FallStart() override;
	void FallUpdate(float _Delta) override;






	// �����
	void ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);
};

