#include "GameOverUI.h"
#include "../../Scene/SceneInfo/SceneInfo.h"

#include "../../Base/Screen.h"

GameOverUI::GameOverUI(IWorld & world, SceneInfo & info)
	: UITexture{ world,"GameOver",GSvector2(),540,200 }
	, m_Info{ info }
{
}

void GameOverUI::on_update(float deltaTime)
{
}

void GameOverUI::on_draw() const
{
	if (m_Info.m_PlayerDead == true)
	{
		const float l_Width = 540.0f;
		const float l_Height = 200.0f;
		GSrect l_Rect(0.0f, 0.0f, l_Width, l_Height);
		GSvector2 l_Scale(1.0f, 1.0f);
		GSvector2 pos = GSvector2(WIDTH / 2, l_Height / 2 + 20.0f);
		GSvector2 l_Center(l_Width / 2, l_Height / 2);
		gsDrawSprite2D((GSuint)TextureName::GameOver, &pos, &l_Rect, &l_Center, NULL, &l_Scale, NULL);
	}
}
