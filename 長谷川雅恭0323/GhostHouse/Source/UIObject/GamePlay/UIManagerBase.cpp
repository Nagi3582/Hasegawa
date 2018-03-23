#include "UIManagerBase.h"
#include "../../Base/Screen.h"
#include "../../Utility/Asset/TextureName.h"

#include <gslib.h>

UIManagerBase::UIManagerBase(SceneInfo& info, int select, GSvector2 select_size, float select_centerY)
	: m_Cursor{ 0 }
	, m_Info{ info }
	, m_StickReset{ false }
	, SELECT_MAX{ select }
	, SELECT_CENTER{ (WIDTH / 2) ,select_centerY }
	, SELECT_SIZE{ select_size }
	, SELECT1_POS_Y{ select == 2 ? 400.0f : SELECT_CENTER.y + SELECT_SIZE.y }
	, SELECT2_POS_Y{ select == 2 ? 560.0f : SELECT_CENTER.y }
	, SELECT3_POS_Y{ select == 2 ? 0.0f : SELECT_CENTER.y - SELECT_SIZE.y }
{}

void UIManagerBase::Update(float deltaTime)
{
	OnUpdate(deltaTime);
	CursorMove();
	if (gsXBoxPadButtonTrigger(0, GS_XBOX_PAD_A))
	{
		Decision();
	}
}

void UIManagerBase::CursorMove()
{
	GSvector2 l_LeftStick;
	gsXBoxPadGetLeftAxis(0, &l_LeftStick);

	const float l_MAX = 0.9f;
	if (l_LeftStick.y >= l_MAX && m_StickReset == false)
	{
		m_Cursor -= 1;
		m_StickReset = true;
		CursorSE();
	}
	else if (l_LeftStick.y <= -l_MAX && m_StickReset == false)
	{
		m_Cursor += 1;
		m_StickReset = true;
		CursorSE();
	}
	else if (l_LeftStick.y <= l_MAX &&l_LeftStick.y >= -l_MAX)
	{
		m_StickReset = false;
	}

	if (m_Cursor >= SELECT_MAX)
		m_Cursor = 0;
	else if (m_Cursor < 0)
		m_Cursor = SELECT_MAX - 1;
}

void UIManagerBase::SelectDraw(int num, const TextureName & name)const
{
	GSrect l_Rect(0.0f, 0.0f, SELECT_SIZE.x, SELECT_SIZE.y);
	GSvector2 l_Scale(1.0f, 1.0f);

	GSvector2 pos = GSvector2(WIDTH / 2, SELECT1_POS_Y);
	if (num == 2)
		pos.y = SELECT2_POS_Y;
	else if (num == 3)
		pos.y = SELECT3_POS_Y;

	GSvector2 l_Center(SELECT_SIZE.x / 2, SELECT_SIZE.y / 2);
	gsDrawSprite2D((GSuint)name, &pos, &l_Rect, &l_Center, NULL, &l_Scale, NULL);
}

void UIManagerBase::CursorDraw() const
{
	const float l_Width = 720.0f;
	const float l_Height = 240.0f;
	GSrect l_Rect(0.0f, 0.0f, l_Width, l_Height);
	GSvector2 l_Scale(1.0f, 1.0f);

	GSvector2 pos = GSvector2(SELECT_CENTER.x - 100.0f, SELECT1_POS_Y);
	if (m_Cursor == 1)
		pos.y = SELECT2_POS_Y;
	else if (m_Cursor == 2)
		pos.y = SELECT3_POS_Y;

	GSvector2 l_Center(l_Width / 2, l_Height / 2);
	gsDrawSprite2D((GSuint)TextureName::Cursor, &pos, &l_Rect, &l_Center, NULL, &l_Scale, NULL);
}
