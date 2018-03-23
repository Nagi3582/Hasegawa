#include "ItemManager.h"
#include "../../Light/LightColor.h"
#include "../Flashlight/LightParameter.h"
#include "../../../World/IWorld.h"


#include "../../../Utility/Asset/SoundName.h"

#include "../../../UIObject/TakeItem/TakeItemManager.h"

#include <gslib.h>
#include <iostream>


//ライトの種類の数
const int LIGHT_COLOR_MAX = (int)LightColor::Blue + 1;
//ライトの最大個数
const int LIGHT_MAX = 5;

ItemManager::ItemManager()
	: m_UnLock{ false }
	, m_CurrentColor{ LightColor::White }
{
}

void ItemManager::Initialize(bool add_light)
{
	m_Lights.clear();


	for (int i = 0; i < LIGHT_COLOR_MAX; ++i)
	{
		for (int j = 0; j < LIGHT_MAX; ++j)
		{
			m_Lights[i].push_back(std::make_shared<LightParameter>(LightColor::None));
		}
	}

	if (add_light == true)
	{
		AddLight(LightColor::White);
	}

	m_CurrentColor = LightColor::White;

}

void ItemManager::Update(float deltaTime)
{
	ChangeColor();


	//{
	//	std::cout << "W::" << std::to_string(GetLightSize(LightColor::White)) << std::endl;
	//	std::cout << "R::" << std::to_string(GetLightSize(LightColor::Red)) << std::endl;
	//	std::cout << "G::" << std::to_string(GetLightSize(LightColor::Green)) << std::endl;
	//	std::cout << "B::" << std::to_string(GetLightSize(LightColor::Blue)) << std::endl;
	//}

	const int l_LightID = (int)m_CurrentColor;

	for (int i = 0; i < (int)m_Lights[l_LightID].size(); ++i)
	{
		if (m_Lights[l_LightID].at(i)->GetColor() == LightColor::None)
			continue;

		m_Lights[l_LightID].at(i)->Update(deltaTime);
		if (m_Lights[l_LightID].at(i)->BatterySize() <= 0)
		{
			m_Lights[l_LightID][i] = std::make_shared<LightParameter>(LightColor::None);
			if (GetLightSize(m_CurrentColor) <= 0)
				ChangeColor(true);
		}
		return;
	}
}

void ItemManager::SetUnLock(bool unlock)
{
	m_UnLock = unlock;
}

void ItemManager::DoorUnLock()
{
	m_UnLock = true;
}

bool ItemManager::get_is_lock() const
{
	return m_UnLock;
}

void ItemManager::AddLight(LightColor color, int batterySize)
{
	if (GetLightSize(color) >= LIGHT_MAX)return;

	int l_PrevBatterySize = batterySize;

	//新しいライトの追加
	for (int i = 0; i < (int)m_Lights[(int)color].size(); ++i)
	{
		if (m_Lights[(int)color].at(i)->GetColor() == LightColor::None)
		{
			m_Lights[(int)color][i] = std::make_shared<LightParameter>(color, l_PrevBatterySize);
			return;
		}
		else if (batterySize < m_Lights[(int)color].at(i)->BatterySize())
		{
			int l_ThisBatterySize = l_PrevBatterySize;
			l_PrevBatterySize = m_Lights[(int)color].at(i)->BatterySize();
			m_Lights[(int)color][i] = std::make_shared<LightParameter>(color, l_ThisBatterySize);
		}

	}
}

void ItemManager::AddLight(LightParameter & color)
{
	AddLight(color.GetColor(), color.BatterySize());
}

void ItemManager::RemoveLight(LightColor color)
{
	int l_ColorID = (int)color;

	for (int i = 0; i < (int)m_Lights[l_ColorID].size(); ++i)
	{
		if (m_Lights[l_ColorID].at(i)->GetColor() == LightColor::None)continue;

		m_Lights[l_ColorID][i] = std::make_shared<LightParameter>(LightColor::None);

		if (GetLightSize(color) <= 0)
		{
			ChangeColor(true);
		}

		return;
	}
}

void ItemManager::TakeBattery()
{
	for (int i = 0; i < (int)m_Lights[(int)m_CurrentColor].size(); ++i)
	{
		//ライトが無いとき追加する
		if (m_Lights[(int)m_CurrentColor].at(i)->GetColor() == LightColor::None)
		{
			AddLight(m_CurrentColor);
			return;
		}
		else if (m_Lights[(int)m_CurrentColor][i]->GetColor() != LightColor::None)
		{
			m_Lights[(int)m_CurrentColor][i]->ChangeBattery();
			return;
		}
	}
}

int ItemManager::GetLightSize(LightColor color)
{
	return GetLightSize((int)color);
}

int ItemManager::GetLightSize(int color)
{
	int l_Num = 0;
	for (int i = 0; i < (int)m_Lights[color].size(); ++i)
	{
		if (m_Lights[(int)color].at(i)->GetColor() == LightColor::None)continue;

		l_Num += 1;
	}
	return l_Num;
}

int ItemManager::BatterySize()
{
	return BatterySize(m_CurrentColor);
}

int ItemManager::BatterySize(LightColor color)
{
	for (int i = 0; i < (int)m_Lights[(int)color].size(); ++i)
	{
		if (m_Lights[(int)color].at(i)->GetColor() == LightColor::None)continue;

		return m_Lights[(int)color][i]->BatterySize();
	}
	return 0;
}

void ItemManager::HitEnemy()
{
	RemoveLight(m_CurrentColor);
}

bool ItemManager::IsHaveLight()
{
	if (GetLightSize(LightColor::White) <= 0 &&
		GetLightSize(LightColor::Red) <= 0 &&
		GetLightSize(LightColor::Green) <= 0 &&
		GetLightSize(LightColor::Blue) <= 0)
	{
		return false;
	}

	return true;
}

LightColor ItemManager::GetColor() const
{
	return m_CurrentColor;
}

void ItemManager::ChangeColor(bool change)
{
	if (IsHaveLight() == true)
	{
		if (gsXBoxPadButtonTrigger(0, GS_XBOX_PAD_RIGHT_SHOULDER) || change == true)
		{
			ChangeColor(1);
		}
		else if (gsXBoxPadButtonTrigger(0, GS_XBOX_PAD_LEFT_SHOULDER))
		{
			ChangeColor(-1);
		}
	}
}

void ItemManager::ChangeColor(int direction)
{
	int l_Color = (int)m_CurrentColor;
	for (int i = 0; i < 4; ++i)
	{
		l_Color += direction;
		if (l_Color > (int)LightColor::Blue)l_Color = 0;
		if (l_Color < (int)LightColor::White)l_Color = 3;


		if (GetLightSize(l_Color) >= 1)
		{
			switch (l_Color)
			{
			case 0:
				m_CurrentColor = LightColor::White;
				break;
			case 1:
				m_CurrentColor = LightColor::Red;
				break;
			case 2:
				m_CurrentColor = LightColor::Green;
				break;
			case 3:
				m_CurrentColor = LightColor::Blue;
				break;
			}
			gsPlaySE((GSuint)SoundName::GetItemSE);
			return;
		}
	}
}


void ItemManager::SetPrevLight(ItemManager & prev)
{
	for (int w = 0; w < prev.GetLightSize(LightColor::White); ++w)
	{
		AddLight(LightColor::White);
	}
	for (int r = 0; r < prev.GetLightSize(LightColor::Red); ++r)
	{
		AddLight(LightColor::Red);
	}
	for (int g = 0; g < prev.GetLightSize(LightColor::Green); ++g)
	{
		AddLight(LightColor::Green);
	}
	for (int b = 0; b < prev.GetLightSize(LightColor::Blue); ++b)
	{
		AddLight(LightColor::Blue);
	}
	m_CurrentColor = prev.GetColor();
}

void ItemManager::SetTakeItemManager(TakeItemManager & takeItemManager)
{
	p_TakeItemManager = &takeItemManager;
}

void ItemManager::TakeItem(TextureName texture)
{
	p_TakeItemManager->AddTakeItem(texture);
}

