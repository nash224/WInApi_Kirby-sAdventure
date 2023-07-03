#pragma once
#include "NormalEnemies.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>



#define POPPYBROSJRSPEED 100.0f
#define POPPYBROSJRCHANGETIME 0.1f

#define POPPYBROSJRJUMPTIME 0.05f
#define POPPYBROSJRJUMPDISTANCE 5.0f

// Ό³Έν :
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

	void AppleRunStart() override;
	void EscapeStart() override;
	void IdleStart() override;
	void JumpStart() override;
	void FallStart() override;


	void AppleRunUpdate(float _Delta) override;
	void EscapeUpdate(float _Delta) override;
	void IdleUpdate(float _Delta) override;
	void JumpUpdate(float _Delta) override;
	void FallUpdate(float _Delta) override;

private:


	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;




	// µπΉφ±λ
	void ThisDebugRender(HDC _dc, int& _RenderNumber, const int _TextXPos, const int _TextYPos);
};

