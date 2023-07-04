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




// ���� : ��Ʈ�ο� ���� �ƾ��Դϴ�. 
//		  �� ���Ϳ��� �������� �̾� ���Ͱ� 3���� �� ó�� �ٸ���ϴ�.
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

	// GameEngineObject ���
private:
	void Start() override;
	void Update(float _Delta) override;


	// Start
	class SceneData
	{
	public:
		GameEngineRenderer* ActorRenderer = nullptr;
		float Scene_XSpeed = 0.0f;
		float Scene_YSpeed = 0.0f;
	};

	SceneData KirbyActor;
	SceneData KnightActor;
	SceneData SwordActor;

	const float4 UnitScale = float4{ 48.0f , 48.0f };


	void ActorRenderSet();



	// Update
	// FSM
	std::string CurState = "";
	ValleyCutSceneState State = ValleyCutSceneState::Max;

	void StateUpdate(float _Delta);
	void ChangeState(ValleyCutSceneState _State);
	void ChangeAnimationState(const std::string& _StateName);


	void StandByStart();
	void StandByUpdate(float _Delta);

	void ConfrontStart();
	void ConfrontUpdate(float _Delta);



	// Press ���� ����
	int Kirby_FrontNumber = 0;
	int Knight_FrontNumber = 0;
	const float OneStepDecelerationSpeed = 27.0f;
	const float TwoStepDecelerationSpeed = 36.0f;
	const float Press_StateDuration = 0.2f;

	void PressStart();
	void PressUpdate(float _Delta);


	// ShedSword ���� ����
	bool IsKirbysSword_FlyAway = false;
	const float EmbarrassmentTime = 0.08f;

	bool IsSwordStuckedPlank = false;

	void ShedSwordStart();
	void ShedSwordUpdate(float _Delta);

	void SwordUpdate(float _Delta);


	// Inhale ���� ����
	int WabbleCount = 0;
	const int MaxWabbleCount = 12;
	float WabbleTime = 0.0f;
	const float WabbleCycle = 0.06f;
	const float TypeOne_WabbleDistance = 10.0f;
	const float TypeTwo_WabbleDistance = -5.0f;
	const float TypeThree_WabbleDistance = 5.0f;

	float Actor_MutualDistance = 0.0f;
	const float BeInhaledTime = 0.2f;

	void KirbyInhaleStart();
	void KirbyInhaleUpdate(float _Delta);




	void EattedKnightStart();
	void EattedKnightUpdate(float _Delta);



	// GetAbility ����
	bool IsGetAbilityAnimationEnd = false;
	bool IsFadeOutStart = false;
	int FadeAlphaValue = 70;


	void GetAbilityStart();
	void GetAbilityUpdate(float _Delta);



	// �̵�
	float4 Renderer_GravityVector = float4::ZERO;

	void Renderer_Gravity(SceneData& _DataStruct, float _Delta, float _GravityPower);
	void Renderer_VerticalUpdate(SceneData& _DataStruct, float _Delta);
	
	void Renderer_HorizontalMoveUpdate(SceneData& _DataStruct, float _Delta);
	void Renderer_DecelerationUpdate(SceneData& _DataStruct, float _Delta, float _Speed);

};

