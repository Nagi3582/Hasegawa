#include "LightParameter.h"
#include "../ItemBase/../../Light/LightColor.h"

LightParameter::LightParameter(LightColor color)
	: m_Color{ color }
	, m_Battery{ 100 }
	, m_Timer{ 0 }
{}

LightParameter::LightParameter(LightColor color, int batterySize)
	: m_Color{ color }
	, m_Battery{ batterySize }
	, m_Timer{ 0 }
{}

void LightParameter::Update(float deltaTime)
{
	if (m_Timer >= 30 && m_Color != LightColor::None)
	{
		m_Battery -= 1;
		m_Timer = 0;
	}
	m_Timer += deltaTime;
}

void LightParameter::ChangeBattery()
{
	m_Battery = 100;
	m_Timer = 0;
}

LightColor LightParameter::GetColor() const
{
	return m_Color;
}

int LightParameter::BatterySize() const
{
	return (int)m_Battery;
}
