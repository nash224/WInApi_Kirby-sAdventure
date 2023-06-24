#pragma once
#include "Enemy.h"

// 설명 :
class Boss : public Enemy
{
	friend class BossUI;
public:
	static Boss* MainBossPtr;
	
	int m_BossHp = 28;
	bool BossChangeMapPattern = false;



	static Boss* GetMainBossPtr()
	{
		return MainBossPtr;
	}


public:
	// constrcuter destructer
	Boss();
	~Boss();

	// delete Function
	Boss(const Boss& _Other) = delete;
	Boss(Boss&& _Other) noexcept = delete;
	Boss& operator=(const Boss& _Other) = delete;
	Boss& operator=(Boss&& _Other) noexcept = delete;

protected:
	std::string CurLevel_BitMap_FileName = "";

	// BossUI 관련
	class BossUI* BossUIPtr = nullptr;


	// BossBackGround 관련
	class BackGround* BossBackGroundPtr = nullptr;

	bool IsBossFindKirby = false;

private:

};

