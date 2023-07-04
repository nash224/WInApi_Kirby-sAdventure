#pragma once
#include <GameEngineCore/GameEngineActor.h>


// 설명 : 클리어 판자를 띄우기 위한 클래스입니다. 
// 원래는 단순히 텍스처를 띄울려고 했으나 사용되지 않아서 판자만 사용하고 있습니다.
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
	// GameEngineObject 상속
	void Start() override;


	// 렌더
	GameEngineRenderer* MainRenderer = nullptr;


public:

};

