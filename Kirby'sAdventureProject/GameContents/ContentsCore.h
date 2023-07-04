#pragma once
#include <GameEngineCore/GameEngineObject.h>
#include <GameEngineCore/GameEngineCore.h>


// 설명 : GameEngineCore의 순수가상테이블로 Level을 생성하거나 바꿉니다.
class ContentsCore : public CoreProcess
{
public:
	// constrcuter destructer
	ContentsCore();
	~ContentsCore();

	// delete Function
	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void Update(float _Delta) override;
	void Render(float _Delta) override;
	void Release() override;
};

