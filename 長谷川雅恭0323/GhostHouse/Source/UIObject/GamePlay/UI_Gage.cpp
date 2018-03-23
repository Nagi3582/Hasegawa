#include "UI_Gage.h"
#include "../../Utility/Number/NumberTexture.h"
#include "../../Scene/SceneInfo/SceneInfo.h"
#include<gslib.h>

UI_Gage::UI_Gage(IWorld & world
	, const GSvector2& position
	, SceneInfo& info
	, ItemManager & item
	, LightColor color)
	:UITexture{ world,"Gage",position,125.0f,16.0f }
	, p_item{ &item }
	, m_color{ color }
	, m_Info{ info }
	, m_color_R{ 0.0f }
	, m_color_G{ 1.0f }
{
}

void UI_Gage::on_update(float deltaTime)
{
	float battery = p_item->BatterySize(m_color);
	float battery_percent;

	if (battery > 50)
	{
		battery_percent = (battery - 50.0f) / 50.f;
		m_color_R = LERP(battery_percent, 1.0f, 0.0f);
		m_color_G = 1.0f;
	}
	if (battery <= 50)
	{
		battery_percent = battery / 50.0f;
		m_color_G = LERP(battery_percent, 0.0f, 1.0f);
		m_color_R = 1.0f;
	}

}

void UI_Gage::on_draw() const
{
	if (m_Info.m_PlayerDead == true || m_Info.m_Pause == true)return;

	float battery = p_item->BatterySize(m_color);
	float battery_percent = battery / 100;

	const GSvector2 l_FrameScale(0.67f, 0.7f);
	gsDrawSprite2D((GSuint)TextureName::Gage_Frame, &m_position, NULL, NULL, NULL, &l_FrameScale, NULL);
	gsDrawSprite2D((GSuint)TextureName::Gage, &GSvector2(m_position.x + 2, m_position.y + 2), NULL, NULL, &GScolor(m_color_R, m_color_G, 0.0f, 1.0f), &GSvector2(battery_percent, 1.0f), NULL);
}
