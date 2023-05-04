#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ErrorCode : C2504 : 클래스를 지정할 때 기본 클래스가 지정되지 않으면 발생함
// 부모 헤더를 추가해주지 않았음
// 설명 :
class TitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	TitleLevel();
	~TitleLevel();

	// delete Function
	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:

private:

};

