#include "UI_Key.h"
#include"../../Scene/SceneInfo/SceneInfo.h"

UI_Key::UI_Key(IWorld & world, const GSvector2 & position, SceneInfo & info)
	:UITexture{ world,"UI_Key",position,50.0f,50.0f }
	, m_Info{ info }
{

}

void UI_Key::on_update(float deltaTime)
{
}

void UI_Key::on_draw() const
{
	if (m_Info.m_PlayerDead == true || m_Info.m_Pause == true)return;


	const GSvector2 l_Scale(0.5f, 0.5f);
	
	GSvector2 l_pos(550.0f,575.0f);
	gsDrawSprite2D((GSuint)TextureName::Key_Window, &l_pos, NULL, NULL, NULL, &l_Scale, NULL);

	if (m_Info.m_GetKey == true)
	{
		GSvector2 l_pos2(557.5f, 583.0f);
		gsDrawSprite2D((GSuint)TextureName::Key, &l_pos2, NULL, NULL, NULL, &l_Scale, NULL);
	}

}