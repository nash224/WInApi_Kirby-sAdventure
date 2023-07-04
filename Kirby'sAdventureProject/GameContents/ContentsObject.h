#pragma once
#include <GameEngineCore/GameEngineActor.h>


// ���� : Ŭ���� ���ڸ� ���� ���� Ŭ�����Դϴ�. 
// ������ �ܼ��� �ؽ�ó�� ������ ������ ������ �ʾƼ� ���ڸ� ����ϰ� �ֽ��ϴ�.
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
	// GameEngineObject ���
	void Start() override;


	// ����
	GameEngineRenderer* MainRenderer = nullptr;


public:

};

