#pragma once
#include <GameEngineCore/GameEngineActor.h>


// ���� : Ŭ���� ���ڸ� ���� ���� Ŭ�����Դϴ�. 
// ������ �ܼ��� �ؽ�ó�� ������ ������ ������ �ʾƼ� ���ڸ� ����ϰ� �ֽ��ϴ�.
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
	// GameEngineObject ���
	void Start() override;


	// ����
	GameEngineRenderer* MainRenderer = nullptr;


public:

};

