#include "StageTitle.h"
#include"../../Utility/Asset/TextureName.h"
#include"../../Base/Screen.h"

StageTitle::StageTitle(IWorld & world, GSuint TexID)
	:UITexture(world
		, "StageTitle"
		, GSvector2{ WIDTH / 2,-45 }
		, 254, 84)
	, m_timer{ 0.0f }
	, base_pos{ WIDTH -150 ,-45.0f }
	, target_pos{ WIDTH -150 ,45.0f }
	,m_TexID{TexID}
{
}

void StageTitle::on_update(float deltaTime)
{
	m_timer += deltaTime;
	float move_percentage = m_timer / 100.0f;
	if (move_percentage > 1.0f)
	{
		return;
	}
	m_position = LERP(move_percentage, base_pos, target_pos);

}

void StageTitle::on_draw() const
{
	gsDrawSprite2D((GSuint)TextureName::StageTitleFrame, &m_position, NULL, &GSvector2{ 127,42 }, NULL, NULL, NULL);
	gsDrawSprite2D(m_TexID, &m_position, NULL, &GSvector2{ 80,32 }, NULL, NULL, NULL);
}
