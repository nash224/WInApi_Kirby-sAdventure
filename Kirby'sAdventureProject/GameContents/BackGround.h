#pragma once
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineActor.h>

#include <string>

// 설명 :
class BackGround : public GameEngineActor
{
	friend class VegetableValleyPlayLevel;
public:
	static int BossStage;

public:
	// constrcuter destructer
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	void init(const std::string& _FileName, const std::string& _Path);
	GameEngineWindowTexture* init(const std::string& _FileName, const std::string& _DebugFileName, const std::string& _Path);
	class GameEngineRenderer* SpriteInit(const std::string& _FileName, const std::string& _DebugFileName, const std::string& _Path, int _XCount, int _YCount);

	void ExtraMapSet(const std::string& _FileName, const std::string& _Path);


	void SwitchRender();

protected:

private:
	float4 BackGroundScale = float4::ZERO;
	bool SwitchRenderValue = true;
	std::string FileName = "";

	class GameEngineRenderer* Renderer = nullptr;
	class GameEngineRenderer* DebugRenderer = nullptr;



public:
	// 보스 관련
	bool IsBossChangeMap = false;


private:

	// Whispy 보스 관련
	const float Whispy_ChangeMap_Cycle = 0.04f;
	float Whispy_ChangeMap_Time = 0.0f;
	int Whispy_ChangeMap_Number = 0;

	void WhispyChangeMap(float _Delta);


private:
	void Start() override;
	void Update(float _Delta) override;
};

