#include "SceneHide.h"
#include "../../Utility/Asset/TextureName.h"

SceneHide::SceneHide()
	: m_Color{ 0.0f,0.0f,0.0f,0.0f }
{
}

void SceneHide::Draw() const
{
	gsDrawSprite2D((int)TextureName::ScreenHide, &GSvector2(0.0f, 0.0f), NULL, NULL, &m_Color, NULL, 0.0f);


}

void SceneHide::SetColor(const float r, const float g, const float b)
{
	m_Color = GScolor(r, g, b, m_Color.a);
}

void SceneHide::SetAlpha(const float alpha)
{
	float l_alpha = CLAMP(alpha, 0.0f, 1.0f);
	m_Color.a = l_alpha;
}
