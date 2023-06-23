#pragma once
#include <GameEnginePlatform/GameEngineWindowTexture.h>
#include <GameEngineCore/GameEngineActor.h>

#include <string>

// 설명 :
class BackGround : public GameEngineActor
{
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
	bool SwitchRenderValue = true;
	std::string FileName = "";

	class GameEngineRenderer* Renderer = nullptr;
	class GameEngineRenderer* DebugRenderer = nullptr;



	// 보스 관련
	bool IsBossChangeMap = false;

	void WhispyChangeMap(float _Delta);
	const float Whispy_ChangeMap_Cycle = 0.06f;
	float Whispy_ChangeMap_Time = 0.0f;
	int Whispy_ChangeMap_Number = 0;



private:
	void Start() override;
	void Update(float _Delta) override;
};

