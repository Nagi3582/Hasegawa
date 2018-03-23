#include "UIPlay.h"
#include"../../Scene/SceneInfo/SceneInfo.h"
#include"../../Base/Screen.h"
#include "../../Utility/Number/NumberTexture.h"
#include "../../GameObject/Light/LightColor.h"

UIPlay::UIPlay(IWorld & world, SceneInfo & info, ItemManager& item)
	:UITexture{ world,"UIPlay",GSvector2(0.0f,0.0f),540.0f,200.0f }
	, m_Info{ info }
	, p_item{ &item }
{
}

void UIPlay::on_update(float deltaTime)
{
}

void UIPlay::on_draw() const
{
	if (m_Info.m_Pause == false)
	{
		Window_Draw();
		//Battery_Draw();
		Flashlight_Draw();
		Number_Draw();
		Kakeru_Draw();
	}
}

void UIPlay::Window_Draw()const
{
	const float l_Width = 750.0f;
	const float l_Height = 200.0f;
	GSrect l_Rect(0.0f, 0.0f, l_Width, l_Height);
	GSvector2 l_Scale(0.65f, 0.65f);
	GSvector2 pos = GSvector2(300.0f, 590.0f);
	GSvector2 l_Center(l_Width / 2, l_Height / 2);
	gsDrawSprite2D((GSuint)TextureName::Window, &pos, &l_Rect, &l_Center, NULL, &l_Scale, NULL);
}

void UIPlay::Battery_Draw()const
{
	const float l_Width = 345.0f;
	const float l_Height = 200.0f;
	GSrect l_Rect(0.0f, 0.0f, l_Width, l_Height);
	GSvector2 l_Scale(0.4f, 0.4f);
	GSvector2 pos = GSvector2(50.0f, 680.0f);
	GSvector2 l_Center(l_Width / 2, l_Height / 2);
	gsDrawSprite2D((GSuint)TextureName::Battery, &pos, &l_Rect, &l_Center, NULL, &l_Scale, NULL);
}

void UIPlay::Flashlight_Draw()const
{
	const float l_Width = 170.0f;
	const float l_Height = 130.0f;
	GSvector2 pos = GSvector2(135.0f, 590.0f);
	GSrect l_Rect(0.0f, 0.0f, l_Width, l_Height);
	GSvector2 l_Center(l_Width / 2, l_Height / 2);
	GSvector2 l_Scale(0.4f, 0.4f);
	gsDrawSprite2D((GSuint)TextureName::White_light, &pos, &l_Rect, &l_Center, NULL, &l_Scale, NULL);


	GSvector2 pos_R = GSvector2(245.0f, 590.0f);
	gsDrawSprite2D((GSuint)TextureName::Red_light, &pos_R, &l_Rect, &l_Center, NULL, &l_Scale, NULL);


	GSvector2 pos_G = GSvector2(355.0f, 590.0f);
	gsDrawSprite2D((GSuint)TextureName::Green_light, &pos_G, &l_Rect, &l_Center, NULL, &l_Scale, NULL);


	GSvector2 pos_B = GSvector2(465.0f, 590.0f);
	gsDrawSprite2D((GSuint)TextureName::Blue_light, &pos_B, &l_Rect, &l_Center, NULL, &l_Scale, NULL);
}

void UIPlay::Number_Draw() const
{
	int width = 50;
	int height = 50;

	static const NumberTexture l_Number(width, height);
	l_Number.draw((GSvector2(135.0f, 616.0f)), p_item->GetLightSize(LightColor::White), 0.5f);
	l_Number.draw((GSvector2(245.0f, 616.0f)), p_item->GetLightSize(LightColor::Red), 0.5f);
	l_Number.draw((GSvector2(355.0f, 616.0f)), p_item->GetLightSize(LightColor::Green), 0.5f);
	l_Number.draw((GSvector2(465.0f, 616.0f)), p_item->GetLightSize(LightColor::Blue), 0.5f);

	static const NumberTexture l_Number_(width, height);

	//l_Number_.draw((GSvector2(100.0f, 635.0f)), p_item->BatterySize(), 0.5f);
}

void UIPlay::Kakeru_Draw() const
{
	const float l_Width = 50.0f;
	const float l_Height = 50.0f;
	GSvector2 pos = GSvector2(120.0f, 629.0f);
	GSrect l_Rect(0.0f, 0.0f, l_Width, l_Height);
	GSvector2 l_Center(l_Width / 2, l_Height / 2);
	GSvector2 l_Scale(0.4f, 0.4f);
	gsDrawSprite2D((GSuint)TextureName::Kakeru, &pos, &l_Rect, &l_Center, NULL, &l_Scale, NULL);


	GSvector2 pos_2 = GSvector2(230.0f, 629.0f);
	gsDrawSprite2D((GSuint)TextureName::Kakeru, &pos_2, &l_Rect, &l_Center, NULL, &l_Scale, NULL);

	GSvector2 pos_3 = GSvector2(340.0f, 629.0f);
	gsDrawSprite2D((GSuint)TextureName::Kakeru, &pos_3, &l_Rect, &l_Center, NULL, &l_Scale, NULL);

	GSvector2 pos_4 = GSvector2(450.0f, 629.0f);
	gsDrawSprite2D((GSuint)TextureName::Kakeru, &pos_4, &l_Rect, &l_Center, NULL, &l_Scale, NULL);

}
