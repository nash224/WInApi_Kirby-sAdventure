#pragma once
#include <GameEngineCore/GameEngineActor.h>


// 설명 : 클리어 판자를 띄우기 위한 클래스입니다. 
// 원래는 단순히 텍스처를 띄울려고 했으나 사용되지 않아서 판자만 사용하고 있습니다.
class EndingPlank : public GameEngineActor
{
	friend class VegetableValleyHub;
public:
	// constrcuter destructer
	EndingPlank();
	~EndingPlank();

	// delete Function
	EndingPlank(const EndingPlank& _Other) = delete;
	EndingPlank(EndingPlank&& _Other) noexcept = delete;
	EndingPlank& operator=(const EndingPlank& _Other) = delete;
	EndingPlank& operator=(EndingPlank&& _Other) noexcept = delete;


	void init(const float4& _PlankPos);

protected:

private:
	// GameEngineObject 상속
	void Start() override;


	// 렌더
	GameEngineRenderer* MainRenderer = nullptr;


public:

};

