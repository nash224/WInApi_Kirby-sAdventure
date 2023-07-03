#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 : Stage 클리어한 증표입니다. 커비의 프라이드가 높아집니다.
class ContentsObject : public GameEngineActor
{
	friend class VegetableValleyHub;
public:
	// constrcuter destructer
	ContentsObject();
	~ContentsObject();

	// delete Function
	ContentsObject(const ContentsObject& _Other) = delete;
	ContentsObject(ContentsObject&& _Other) noexcept = delete;
	ContentsObject& operator=(const ContentsObject& _Other) = delete;
	ContentsObject& operator=(ContentsObject&& _Other) noexcept = delete;


	void init(const float4& _PlankPos);

protected:

private:
	void Start() override;
	void Update(float _Delta) override;

	GameEngineRenderer* MainRenderer = nullptr;


public:

};

