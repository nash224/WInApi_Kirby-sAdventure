#pragma once
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineActor.h>

#include <string>

// 설명 : 레벨의 배경을 당담합니다. 이외에도 다양한 기능을 제공합니다.
class BackGround : public GameEngineActor
{
	friend class VegetableValleyPlayLevel;
public:
	// constrcuter destructer
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;


	// 외부
	void init(const std::string& _FileName, const std::string& _Path);
	GameEngineWindowTexture* init(const std::string& _FileName, const std::string& _DebugFileName, const std::string& _Path);
	class GameEngineRenderer* SpriteInit(const std::string& _FileName, const std::string& _DebugFileName, const std::string& _Path, int _XCount, int _YCount);


	float4 GetBackGroundScale() const
	{
		return BackGroundScale;
	}


protected:

private:
	// GameEngineObject override
	void Start() override;
	void Update(float _Delta) override;



	// this
	float4 BackGroundScale = float4::ZERO;
	std::string FileName = "";



public:
	// 공통 보스 
	static int BossStage;
	bool IsBossChangeMap = false;
	void ExtraMapSet(const std::string& _FileName, const std::string& _Path);


private:

	// Whispy 보스
	const float Whispy_ChangeMap_Cycle = 0.04f;
	float Whispy_ChangeMap_Time = 0.0f;
	int Whispy_ChangeMap_Number = 0;

	void WhispyChangeMap(float _Delta);



	// 디버그 렌더
	bool SwitchRenderValue = true;
	class GameEngineRenderer* Renderer = nullptr;
	class GameEngineRenderer* DebugRenderer = nullptr;

public:
	void SwitchRender();
};

