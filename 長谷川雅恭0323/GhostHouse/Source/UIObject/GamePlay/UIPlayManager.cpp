#include "UIPlayManager.h"
#include"UIPlay.h"
#include"../../World/IWorld.h"
#include"../../UI/UIGroup.h"
#include"../../Scene/SceneInfo/SceneInfo.h"
#include"../../Scene/SceneType/SceneType.h"
#include"../../Base/Screen.h"
#include"../../GameObject/Item/ItemManager/ItemManager.h"
#include"UI_Gage.h"

#include<gslib.h>

UIPlayManager::UIPlayManager(SceneInfo & info, ItemManager& itemMana)
	:m_Cursor{ 0 }
	, m_Info{ info }
	, m_StickReset{ false }
	, m_ItemMana{ itemMana }
{
}

void UIPlayManager::Initialize(IWorld & world, Renderer& renderer)
{
	m_Cursor = 0;
	world.AddUI(UIGroup::main, std::make_shared<UI_Gage>(world, GSvector2{ 94.0f,550.0f }, m_Info, m_ItemMana, LightColor::White));
	world.AddUI(UIGroup::main, std::make_shared<UI_Gage>(world, GSvector2{ 204.0f,550.0f }, m_Info, m_ItemMana, LightColor::Red));
	world.AddUI(UIGroup::main, std::make_shared<UI_Gage>(world, GSvector2{ 314.0f,550.0f }, m_Info, m_ItemMana, LightColor::Green));
	world.AddUI(UIGroup::main, std::make_shared<UI_Gage>(world, GSvector2{ 424.0f,550.0f }, m_Info, m_ItemMana, LightColor::Blue));
	world.AddUI(UIGroup::main, std::make_shared<UIPlay>(world, m_Info, m_ItemMana));

}

void UIPlayManager::Update(float deltaTime)
{
	int l_color = (int)(m_ItemMana.GetColor());

	m_Cursor = l_color;





}

void UIPlayManager::Draw() const
{
	if (m_Info.m_Pause == false)
	{
		Cursor_Draw();
	}
}

void UIPlayManager::Cursor_Draw()const
{
	const float l_Width = 200.0f;
	const float l_Height = 160.0f;
	GSrect l_Rect(0.0f, 0.0f, l_Width, l_Height);
	GSvector2 l_Scale(0.65f, 0.7f);
	GSvector2 pos = GSvector2(135.0f, 590.0f);
	if (m_Cursor == 0)
		pos.x = 135.0f;

	if (m_Cursor == 1)
		pos.x = 245.0f;

	if (m_Cursor == 2)
		pos.x = 355.0f;

	if (m_Cursor == 3)
		pos.x = 465.0f;

	GSvector2 l_Center(l_Width / 2, l_Height / 2);
	gsDrawSprite2D((GSuint)TextureName::UICursor, &pos, &l_Rect, &l_Center, NULL, &l_Scale, NULL);
}
