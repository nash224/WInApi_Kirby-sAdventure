#include "Kirby.h"


#include <GameEnginePlatform/GameEngineInput.h>




void Kirby::KirbysDebugShortcut(float _Delta)
{
	// 치트 무적키
	if (true == GameEngineInput::IsDown('1'))
	{
		Cheat_Invincibility = !Cheat_Invincibility;
	}

	// 지정 상태 확인키
	//if (true == GameEngineInput::IsDown('J'))
	//{
	//	ChangeState(KirbyState::StageClear);
	//	return;
	//}

	if (true == GameEngineInput::IsDown('I'))
	{
		Star.SwallowedEnemyNumber = 1;
		Star.SwallowedPowerEnemyNumber = 1;
		CurrentAbilityStar = AbilityStar::Ice;
		ChangeState(KirbyState::Contain_Idle);
		return;
	}
}




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
		else if (true == Cheat_Invincibility)
		{
			Text += "Off";
		}
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}



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

		Text += "X,Y 속도 : ";
		Text += std::to_string(static_cast<int>(CurrentSpeed));
		Text += " ,";
		Text += std::to_string(static_cast<int>(GetGravityVector().Y));
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
		Text += CurMode;
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

		Text += "IceBlock Size : ";

		Text += std::to_string(IceBlockPtr_list.size());
		TextOutA(_dc, 2, 2 + TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}

}



void Kirby::ThisDebugRender(HDC _dc)
{
	int TextRenderNum = 0;


	float4 ActorScenePos = ActorCameraPos();

	float4 Scale = GetKirbyScale();

	int TextXPos = ActorScenePos.iX() - Scale.Half().iX();
	int TextYPos = ActorScenePos.iY() - (Scale * 2.0f).iY();


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



	{
		std::string Text = "";
		Text += "IceBlock Size : ";
		Text += std::to_string(IceBlockPtr_list.size());
		TextOutA(_dc, TextXPos, 2 + TextYPos - TextRenderNum * DebugRenderText_YInter, Text.c_str(), static_cast<int>(Text.size()));

		++TextRenderNum;
	}


}
