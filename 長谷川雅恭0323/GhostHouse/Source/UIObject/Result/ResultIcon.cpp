#include "ResultIcon.h"
#include "../../Utility/Asset/TextureName.h"


ResultIcon::ResultIcon(IWorld & world)
	: UITexture{ world,"ResultIcon",GSvector2(0.0f,0.0f),170,130 }
{
	const int TEXTURE_MAX = 8;
	TextureName l_Textures[TEXTURE_MAX] =
	{
		TextureName::White_light,
		TextureName::Green_light,
		TextureName::Red_light,
		TextureName::Blue_light,
		TextureName::MusicBoxIcon,
		TextureName::DoorIcon,
		TextureName::ColorDoorIcon,
		TextureName::MixColorDoorIcon,
	};


	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		m_TextureNames.push_back(l_Textures[i]);
	}
}

void ResultIcon::on_update(float deltaTime)
{
}

void ResultIcon::on_draw() const
{
	const float l_Scale = 0.5f;
	const float l_Width = 170.0f * l_Scale;
	const float l_Height = 130.0f * l_Scale;
	const GSrect l_Rect(0.0f, 0.0f, l_Width / l_Scale, l_Height / l_Scale);
	const GSvector2 l_Center(l_Width / 2, l_Height / 2);
	const GSvector2 l_BasePos(220.0f, 130.0f);
	GSvector2 l_Pos = l_BasePos;
	for (int i = 0; i < (int)m_TextureNames.size(); ++i)
	{
		gsDrawSprite2D((GSuint)m_TextureNames[i], &l_Pos, &l_Rect, &l_Center, NULL, &GSvector2(l_Scale, l_Scale), NULL);

		if (i % 2 == 0)
		{
			l_Pos.x += l_Width * 3;
		}
		else
		{
			l_Pos.x = l_BasePos.x;
			l_Pos.y += l_Height + 20;
		}
	}
}
