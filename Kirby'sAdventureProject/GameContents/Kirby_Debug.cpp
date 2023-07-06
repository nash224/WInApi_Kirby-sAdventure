#include "Kirby.h"


#include <GameEnginePlatform/GameEngineInput.h>

#include "VegetableValleyPlayLevel.h"



// 커비 디버그 숏컷
void Kirby::KirbysDebugShortcut(float _Delta)
{
	if (false == VegetableValleyPlayLevel::Level_DebugRenderValue)
	{
		return;
	}


	// 치트 무적키
	if (true == GameEngineInput::IsDown('1'))
	{
		Cheat_Invincibility = !Cheat_Invincibility;
		if (true == Cheat_Invincibility)
		{
			Cheat_NoneBodyCollision = false;
		}
	}

	if (true == GameEngineInput::IsDown('2'))
	{
		SwitchNoneBodyCollision();
	}

	if (true == GameEngineInput::IsDown('4'))
	{
		if (6 != m_KirbyHp)
		{
			++m_KirbyHp;
		}
	}

	if (true == GameEngineInput::IsDown('5'))
	{
		if (KirbyState::Fly != KeepDamagedState && KirbyState::Contain_Idle != KeepDamagedState)
		{
			ChangeState(KirbyState::Damaged);
			return;
		}
		else if (KirbyState::Fly == KeepDamagedState || KirbyState::Contain_Idle == KeepDamagedState)
		{
			ChangeState(KirbyState::Contain_Damaged);
			return;
		}
	}


	// 지정 상태 확인키 (임시 활성화)
	//if (true == GameEngineInput::IsDown('J'))
	//{
	//	ChangeState(KirbyState::StageClear);
	//	return;
	//}


	if (AbilityStar::Max != Mode && AbilityStar::Normal != Mode)
	{
		return;
	}

	// 얼음
	if (true == GameEngineInput::IsDown('I'))
	{
		Star.SwallowedEnemyNumber = 1;
		Star.SwallowedPowerEnemyNumber = 1;
		CurrentAbilityStar = AbilityStar::Ice;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	// 검
	if (true == GameEngineInput::IsDown('O'))
	{
		Star.SwallowedEnemyNumber = 1;
		Star.SwallowedPowerEnemyNumber = 1;
		CurrentAbilityStar = AbilityStar::Sword;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	// 가시
	if (true == GameEngineInput::IsDown('P'))
	{
		Star.SwallowedEnemyNumber = 1;
		Star.SwallowedPowerEnemyNumber = 1;
		CurrentAbilityStar = AbilityStar::Thorn;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	// 빔
	if (true == GameEngineInput::IsDown('U'))
	{
		Star.SwallowedEnemyNumber = 1;
		Star.SwallowedPowerEnemyNumber = 1;
		CurrentAbilityStar = AbilityStar::Beam;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	// 화염
	if (true == GameEngineInput::IsDown('Y'))
	{
		Star.SwallowedEnemyNumber = 1;
		Star.SwallowedPowerEnemyNumber = 1;
		CurrentAbilityStar = AbilityStar::Fire;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	// 스파크
	if (true == GameEngineInput::IsDown('K'))
	{
		Star.SwallowedEnemyNumber = 1;
		Star.SwallowedPowerEnemyNumber = 1;
		CurrentAbilityStar = AbilityStar::Spark;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	// 레이저
	if (true == GameEngineInput::IsDown('L'))
	{
		Star.SwallowedEnemyNumber = 1;
		Star.SwallowedPowerEnemyNumber = 1;
		CurrentAbilityStar = AbilityStar::Laser;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	// 큰별
	if (true == GameEngineInput::IsDown('J'))
	{
		Star.SwallowedEnemyNumber = 2;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

}


// 치트 콜리전 Off
void Kirby::SwitchNoneBodyCollision()
{
	Cheat_NoneBodyCollision = !Cheat_NoneBodyCollision;
	if (true == Cheat_NoneBodyCollision)
	{
		Cheat_Invincibility = false;
	}
}



// 좌측 상단 커비용 디버깅 렌더
void Kirby::KirbyDebugRender(HDC _dc)
{
	int TextRenderNum = 0;
	

	{
		std::string Text = "";

		Text += "Char Key 1 : 무적 모드 : ";
		if (true == Cheat_Invincibility)
		{
			Text += "On";
		}
		else if (false == Cheat_Invincibility)
		{
			Text += "Off";
		}
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}
	
		

	{
		std::string Text = "";

		Text += "Char Key 2 : 충돌처리 : ";
		if (true == Cheat_NoneBodyCollision)
		{
			Text += "Off";
		}
		else if (false == Cheat_NoneBodyCollision)
		{
			Text += "On";
		}
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	{
		std::string Text = "";

		Text += "Char Key 4 : ++체력";
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	{
		std::string Text = "";

		Text += "Char Key 5 : --체력";
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}

	{
		std::string Text = "";

		Text += "Char Key 6 : 자폭";
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	++TextRenderNum;


	{
		std::string Text = "";

		Text += "Dir : ";
		if (ActorDir::Left == Dir)
		{
			Text += "Left";
		}
		else if (ActorDir::Right == Dir)
		{
			Text += "Right";
		}
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	{
		std::string Text = "";

		Text += "현재 위치 : ";
		Text += std::to_string(static_cast<int>(GetPos().X));
		Text += " ,";
		Text += std::to_string(static_cast<int>(GetPos().Y));
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	{
		std::string Text = "";

		Text += "1프레임 X 속도 : ";
		Text += std::to_string(KirbyMovePos.X);
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	{
		std::string Text = "";

		Text += "1프레임 Y 속도 : ";
		Text += std::to_string(KirbyMovePos.Y);
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	{
		std::string Text = "";

		Text += "현재 상태 : ";
		Text += CurState;
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	if (GetAirResistance() < 1.0f)
	{
		std::string Text = "";

		Text += "공중 저항 : ";
		Text += std::to_string(GetAirResistance());
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	{
		std::string Text = "";

		Text += "현재 모드 : ";
0		Text += CurMode;
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	{
		std::string Text = "";

		Text += "커비 몸 판정 : ";
		switch (BodyState)
		{
		case KirbyBodyState::Little:
			Text += "Little";
			break;
		case KirbyBodyState::Fat:
			Text += "Fat";
			break;
		case KirbyBodyState::Lower:
			Text += "Lower";
			break;
		default:
			break;
		}

		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}



	{
		std::string Text = "";

		Text += "커비 Hp : ";
		Text += std::to_string(m_KirbyHp);
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}
	


	{
		std::string Text = "";
		Text += "커비 상태 보존: ";
		switch (KeepDamagedState)
		{
		case KirbyState::Idle:
			Text += "Idle";
			break;
		case KirbyState::Fly:
			Text += "Fly";
			break;
		case KirbyState::Contain_Idle:
			Text += "Contain_Idle";
			break;
		default:
			break;
		}
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}
}


// 커비 몸통 위 디버깅 렌더
void Kirby::ThisDebugRender(HDC _dc)
{
	int TextRenderNum = 0;


	float4 ActorScenePos = ActorCameraPos();

	float4 Scale = GetKirbyScale();

	int TextXPos = ActorScenePos.iX() - Scale.Half().iX();
	int TextYPos = ActorScenePos.iY() - (Scale * 2.0f).iY();



	if (true == IsEnterPixel())
	{
		std::string Text = "";
		Text += "레벨 이동";
		TextOutA(_dc, TextXPos, 2 + TextYPos - TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	if (true == Cheat_Invincibility || true == ImmuneState)
	{
		std::string Text = "";
		Text += "무적 시간 : ";
		Text += std::to_string(ImmuneDuration - ImmuneTime);
		TextOutA(_dc, TextXPos, 2 + TextYPos - TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	// 커비 입안에 능력이 있으면
	if (KirbyState::UseSpecialAbility != State)
	{
		if (Star.SwallowedEnemyNumber >= 1)
		{
			std::string Text = "";
			Text += "별의 속성 : ";
			switch (CurrentAbilityStar)
			{
			case AbilityStar::Normal:
				Text += "Normal";
				break;
			case AbilityStar::Spark:
				Text += "Spark";
				break;
			case AbilityStar::Laser:
				Text += "Laser";
				break;
			case AbilityStar::Beam:
				Text += "Beam";
				break;
			case AbilityStar::Fire:
				Text += "Fire";
				break;
			case AbilityStar::Thorn:
				Text += "Thorn";
				break;
			case AbilityStar::Sword:
				Text += "Sword";
				break;
			case AbilityStar::Ice:
				Text += "Ice";
				break;
			case AbilityStar::Max:
				Text += "Max";
				break;
			default:
				break;
			}
			TextOutA(_dc, TextXPos, 2 + TextYPos - TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

			++TextRenderNum;
		}

		if (Star.SwallowedEnemyNumber >= 1)
		{
			std::string Text = "";
			Text += "Normal Grunt : ";
			Text += std::to_string(Star.SwallowedEnemyNumber - Star.SwallowedPowerEnemyNumber);
			TextOutA(_dc, TextXPos, 2 + TextYPos - TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

			++TextRenderNum;
		}

		if (Star.SwallowedEnemyNumber >= 1)
		{
			std::string Text = "";
			Text += "Power Grunt : ";
			Text += std::to_string(Star.SwallowedPowerEnemyNumber);
			TextOutA(_dc, TextXPos, 2 + TextYPos - TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

			++TextRenderNum;
		}
	}



	if (AbilityStar::Ice == Mode)
	{
		std::string Text = "";
		Text += "IceBlock Size : ";
		Text += std::to_string(IceBlockPtr_list.size());
		TextOutA(_dc, TextXPos, 2 + TextYPos - TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


}


// 키 다운 디버깅 렌더
void Kirby::KeyDownRender(HDC _dc)
{

	if (true == GameEngineInput::IsPress('W'))
	{
		std::string Text = "";
		Text += "Up";
		TextOutA(_dc, KeyDownPos.iX() - 2, KeyDownPos.iY() - 30, Text.c_str(), static_cast<int>(Text.size()));
	}

	if (true == GameEngineInput::IsPress('S'))
	{
		std::string Text = "";
		Text += "Down";
		TextOutA(_dc, KeyDownPos.iX() - 4, KeyDownPos.iY(), Text.c_str(), static_cast<int>(Text.size()));
	}

	if (true == GameEngineInput::IsPress('A'))
	{
		std::string Text = "";
		Text += "Left";
		TextOutA(_dc, KeyDownPos.iX() - 40, KeyDownPos.iY(), Text.c_str(), static_cast<int>(Text.size()));
	}

	if (true == GameEngineInput::IsPress('D'))
	{
		std::string Text = "";
		Text += "Right";
		TextOutA(_dc, KeyDownPos.iX() + 40, KeyDownPos.iY(), Text.c_str(), static_cast<int>(Text.size()));
	}


	if (true == GameEngineInput::IsPress('X'))
	{
		std::string Text = "";
		Text += "Jump";
		TextOutA(_dc, KeyDownPos.iX() - 90, KeyDownPos.iY(), Text.c_str(), static_cast<int>(Text.size()));
	}


	if (true == GameEngineInput::IsPress('Z'))
	{
		std::string Text = "";
		Text += "Special Key";
		TextOutA(_dc, KeyDownPos.iX() - 170, KeyDownPos.iY(), Text.c_str(), static_cast<int>(Text.size()));
	}


	if (true == GameEngineInput::IsPress(VK_SHIFT))
	{
		std::string Text = "";
		Text += "LShift";
		TextOutA(_dc, KeyDownPos.iX() - 220, KeyDownPos.iY(), Text.c_str(), static_cast<int>(Text.size()));
	}


	if (true == GameEngineInput::IsPress('M'))
	{
		int ModeMenuNumber = 0;

		{
			std::string Text = "";
			Text += "Mode Cheat Menu : ";
			TextOutA(_dc, KeyDownPos.iX() - 150, KeyDownPos.iY() + DebugRenderText_YInter * ModeMenuNumber - 400, Text.c_str(), static_cast<int>(Text.size()));

			ModeMenuNumber++;
		}


		{
			std::string Text = "";
			Text += "Key P : Thorn";
			TextOutA(_dc, KeyDownPos.iX() - 150, KeyDownPos.iY() + DebugRenderText_YInter * ModeMenuNumber - 400, Text.c_str(), static_cast<int>(Text.size()));

			ModeMenuNumber++;
		}


		{
			std::string Text = "";
			Text += "Key O : Sword";
			TextOutA(_dc, KeyDownPos.iX() - 150, KeyDownPos.iY() + DebugRenderText_YInter * ModeMenuNumber - 400, Text.c_str(), static_cast<int>(Text.size()));

			ModeMenuNumber++;
		}


		{
			std::string Text = "";
			Text += "Key I : Ice";
			TextOutA(_dc, KeyDownPos.iX() - 150, KeyDownPos.iY() + DebugRenderText_YInter * ModeMenuNumber - 400, Text.c_str(), static_cast<int>(Text.size()));

			ModeMenuNumber++;
		}


		{
			std::string Text = "";
			Text += "Key U : Beam";
			TextOutA(_dc, KeyDownPos.iX() - 150, KeyDownPos.iY() + DebugRenderText_YInter * ModeMenuNumber - 400, Text.c_str(), static_cast<int>(Text.size()));

			ModeMenuNumber++;
		}


		{
			std::string Text = "";
			Text += "Key Y : Fire";
			TextOutA(_dc, KeyDownPos.iX() - 150, KeyDownPos.iY() + DebugRenderText_YInter * ModeMenuNumber - 400, Text.c_str(), static_cast<int>(Text.size()));

			ModeMenuNumber++;
		}


		{
			std::string Text = "";
			Text += "Key K : Spark";
			TextOutA(_dc, KeyDownPos.iX() - 150, KeyDownPos.iY() + DebugRenderText_YInter * ModeMenuNumber - 400, Text.c_str(), static_cast<int>(Text.size()));

			ModeMenuNumber++;
		}


		{
			std::string Text = "";
			Text += "Key L : Laser";
			TextOutA(_dc, KeyDownPos.iX() - 150, KeyDownPos.iY() + DebugRenderText_YInter * ModeMenuNumber - 400, Text.c_str(), static_cast<int>(Text.size()));

			ModeMenuNumber++;
		}


		{
			std::string Text = "";
			Text += "Key J : Large Star";
			TextOutA(_dc, KeyDownPos.iX() - 150, KeyDownPos.iY() + DebugRenderText_YInter * ModeMenuNumber - 400, Text.c_str(), static_cast<int>(Text.size()));

			ModeMenuNumber++;
		}
	}
}