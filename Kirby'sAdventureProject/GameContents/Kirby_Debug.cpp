#include "Kirby.h"


#include <GameEnginePlatform/GameEngineInput.h>

#include "VegetableValleyPlayLevel.h"



// Ŀ�� ����� ����
void Kirby::KirbysDebugShortcut(float _Delta)
{
	if (false == VegetableValleyPlayLevel::Level_DebugRenderValue)
	{
		return;
	}


	// ġƮ ����Ű
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


	// ���� ���� Ȯ��Ű (�ӽ� Ȱ��ȭ)
	//if (true == GameEngineInput::IsDown('J'))
	//{
	//	ChangeState(KirbyState::StageClear);
	//	return;
	//}


	if (AbilityStar::Max != Mode && AbilityStar::Normal != Mode)
	{
		return;
	}

	// ����
	if (true == GameEngineInput::IsDown('I'))
	{
		Star.SwallowedEnemyNumber = 1;
		Star.SwallowedPowerEnemyNumber = 1;
		CurrentAbilityStar = AbilityStar::Ice;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	// ��
	if (true == GameEngineInput::IsDown('O'))
	{
		Star.SwallowedEnemyNumber = 1;
		Star.SwallowedPowerEnemyNumber = 1;
		CurrentAbilityStar = AbilityStar::Sword;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	// ����
	if (true == GameEngineInput::IsDown('P'))
	{
		Star.SwallowedEnemyNumber = 1;
		Star.SwallowedPowerEnemyNumber = 1;
		CurrentAbilityStar = AbilityStar::Thorn;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	// ��
	if (true == GameEngineInput::IsDown('U'))
	{
		Star.SwallowedEnemyNumber = 1;
		Star.SwallowedPowerEnemyNumber = 1;
		CurrentAbilityStar = AbilityStar::Beam;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	// ȭ��
	if (true == GameEngineInput::IsDown('Y'))
	{
		Star.SwallowedEnemyNumber = 1;
		Star.SwallowedPowerEnemyNumber = 1;
		CurrentAbilityStar = AbilityStar::Fire;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	// ����ũ
	if (true == GameEngineInput::IsDown('K'))
	{
		Star.SwallowedEnemyNumber = 1;
		Star.SwallowedPowerEnemyNumber = 1;
		CurrentAbilityStar = AbilityStar::Spark;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	// ������
	if (true == GameEngineInput::IsDown('L'))
	{
		Star.SwallowedEnemyNumber = 1;
		Star.SwallowedPowerEnemyNumber = 1;
		CurrentAbilityStar = AbilityStar::Laser;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

	// ū��
	if (true == GameEngineInput::IsDown('J'))
	{
		Star.SwallowedEnemyNumber = 2;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}

}


// ġƮ �ݸ��� Off
void Kirby::SwitchNoneBodyCollision()
{
	Cheat_NoneBodyCollision = !Cheat_NoneBodyCollision;
	if (true == Cheat_NoneBodyCollision)
	{
		Cheat_Invincibility = false;
	}
}



// ���� ��� Ŀ��� ����� ����
void Kirby::KirbyDebugRender(HDC _dc)
{
	int TextRenderNum = 0;
	

	{
		std::string Text = "";

		Text += "Char Key 1 : ���� ��� : ";
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

		Text += "Char Key 2 : �浹ó�� : ";
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

		Text += "Char Key 4 : ++ü��";
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	{
		std::string Text = "";

		Text += "Char Key 5 : --ü��";
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}

	{
		std::string Text = "";

		Text += "Char Key 6 : ����";
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

		Text += "���� ��ġ : ";
		Text += std::to_string(static_cast<int>(GetPos().X));
		Text += " ,";
		Text += std::to_string(static_cast<int>(GetPos().Y));
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	{
		std::string Text = "";

		Text += "1������ X �ӵ� : ";
		Text += std::to_string(KirbyMovePos.X);
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	{
		std::string Text = "";

		Text += "1������ Y �ӵ� : ";
		Text += std::to_string(KirbyMovePos.Y);
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	{
		std::string Text = "";

		Text += "���� ���� : ";
		Text += CurState;
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	if (GetAirResistance() < 1.0f)
	{
		std::string Text = "";

		Text += "���� ���� : ";
		Text += std::to_string(GetAirResistance());
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	{
		std::string Text = "";

		Text += "���� ��� : ";
0		Text += CurMode;
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	{
		std::string Text = "";

		Text += "Ŀ�� �� ���� : ";
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

		Text += "Ŀ�� Hp : ";
		Text += std::to_string(m_KirbyHp);
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}
	


	{
		std::string Text = "";
		Text += "Ŀ�� ���� ����: ";
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


// Ŀ�� ���� �� ����� ����
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
		Text += "���� �̵�";
		TextOutA(_dc, TextXPos, 2 + TextYPos - TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	if (true == Cheat_Invincibility || true == ImmuneState)
	{
		std::string Text = "";
		Text += "���� �ð� : ";
		Text += std::to_string(ImmuneDuration - ImmuneTime);
		TextOutA(_dc, TextXPos, 2 + TextYPos - TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


	// Ŀ�� �Ծȿ� �ɷ��� ������
	if (KirbyState::UseSpecialAbility != State)
	{
		if (Star.SwallowedEnemyNumber >= 1)
		{
			std::string Text = "";
			Text += "���� �Ӽ� : ";
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


// Ű �ٿ� ����� ����
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