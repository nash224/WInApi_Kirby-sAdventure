#pragma once
#include "ActorUtils.h"



enum class ValleyCutSceneState
{
	StandBy,
	Confront,
	Press,
	ShedSword,
	KirbyInhale,
	EattedKnight,
	GetAbility,
	Max,
};


class SceneData
{
public:
	GameEngineRenderer* ActorRenderer = nullptr;
	float Scene_XSpeed = 0.0f;
	float Scene_YSpeed = 0.0f;
};


// 설명 :
class VegetableValleyCutScene : public ActorUtils
{
public:
	bool SceneEnd = false;

public:
	// constrcuter destructer
	VegetableValleyCutScene();
	~VegetableValleyCutScene();

	// delete Function
	VegetableValleyCutScene(const VegetableValleyCutScene& _Other) = delete;
	VegetableValleyCutScene(VegetableValleyCutScene&& _Other) noexcept = delete;
	VegetableValleyCutScene& operator=(const VegetableValleyCutScene& _Other) = delete;
	VegetableValleyCutScene& operator=(VegetableValleyCutScene&& _Other) noexcept = delete;

protected:

private:
	SceneData KirbyActor;
	SceneData KnightActor;
	SceneData SwordActor;

	const float4 UnitScale = float4{ 48.0f , 48.0f };

	std::string CurState = "";
	ValleyCutSceneState State = ValleyCutSceneState::Max;

	void StateUpdate(float _Delta);
	void ChangeState(ValleyCutSceneState _State);
	void ChangeAnimationState(const std::string& _StateName);




	void StandByStart();
	void ConfrontStart();
	void PressStart();
	void ShedSwordStart();
	void KirbyInhaleStart();
	void EattedKnightStart();
	void GetAbilityStart();


	void StandByUpdate(float _Delta);
	void ConfrontUpdate(float _Delta);
	void PressUpdate(float _Delta);
	void ShedSwordUpdate(float _Delta);
	void KirbyInhaleUpdate(float _Delta);
	void EattedKnightUpdate(float _Delta);
	void GetAbilityUpdate(float _Delta);



	// 이동
	float4 Renderer_GravityVector = float4::ZERO;

	void Renderer_Gravity(SceneData& _DataStruct, float _Delta, float _GravityPower);
	void Renderer_VerticalUpdate(SceneData& _DataStruct, float _Delta);
	

	void Renderer_HorizontalMoveUpdate(SceneData& _DataStruct, float _Delta);
	void Renderer_DecelerationUpdate(SceneData& _DataStruct, float _Delta, float _Speed);


	// Press 상태
	int Kirby_FrontNumber = 0;
	int Knight_FrontNumber = 0;
	const float OneStepDecelerationSpeed = 27.0f;
	const float TwoStepDecelerationSpeed = 36.0f;
	const float Press_StateDuration = 0.2f;

	// ShedSword 상태 관련
	bool IsKirbysSword_FlyAway = false;
	const float EmbarrassmentTime = 0.08f;

	bool IsSwordStuckedPlank = false;

	void SwordUpdate(float _Delta);


	// Inhale 상태 관련
	int WabbleCount = 0;
	const int MaxWabbleCount = 12;
	float WabbleTime = 0.0f;
	const float WabbleCycle = 0.06f;
	const float TypeOne_WabbleDistance = 10.0f;
	const float TypeTwo_WabbleDistance = -5.0f;
	const float TypeThree_WabbleDistance = 5.0f;

	float Actor_MutualDistance = 0.0f;
	const float BeInhaledTime = 0.2f;


	// GetAbility 관련
	bool IsGetAbilityAnimationEnd = false;
	bool IsFadeOutStart = false;
	int FadeAlphaValue = 70;



private:
	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd() override;
};

