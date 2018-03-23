#include "TakeItem.h"
#include "../../Base/Screen.h"


const int DELETE_TIME = 60 * 5;				//消すまでの時間
const float HIDE_POS_X = WIDTH + 300.0f;	//画面外に移動させるX座標
const float TARGET_POS_X = WIDTH - 210.0f;	//移動させるX座標
const float TARGET_POS_Y = 400.0f;			//移動させるY座標
const float MOVE_UI_Y = 30.0f;				//UIが上に移動する距離

TakeItem::TakeItem(IWorld & world, TextureName texture)
	: UITexture{ world,"TakeItem",GSvector2(HIDE_POS_X,TARGET_POS_Y),400,100 }
	, m_Velocity{ 0.0f,0.0f }
	, m_Timer{ 0 }
	, m_TakeItemID{ -1 }
	, m_Name{ texture }
{
}

void TakeItem::on_update(float deltaTime)
{
	GSvector2 l_TargetPos(0.0f, 0.0f);

	if (m_Timer <= DELETE_TIME / 2)
	{
		l_TargetPos = GSvector2(TARGET_POS_X, TARGET_POS_Y - MOVE_UI_Y * m_TakeItemID);
	}
	else
	{
		l_TargetPos = GSvector2(HIDE_POS_X, TARGET_POS_Y - MOVE_UI_Y * m_TakeItemID);
	}

	Spring(l_TargetPos, 1.5f, 0.2f, 6.0f);
	m_position += m_Velocity * deltaTime;

	if (m_Timer >= DELETE_TIME)
	{
		delete_UI();
	}


	m_Timer += deltaTime;
}

void TakeItem::on_draw() const
{
	const GSvector2 l_Scale(0.5f, 0.5f);

	gsDrawSprite2D((GSuint)m_Name, &m_position, NULL, NULL, NULL, &l_Scale, NULL);

}

void TakeItem::AddTakeItem()
{
	m_TakeItemID++;
}

void TakeItem::Spring(const GSvector2 & restPosition, float stiffness, float friction, float mass)
{
	//ばねの伸び具合
	const GSvector2 stretch = m_position - restPosition;
	//ばねの力の計算
	const GSvector2 force = -stiffness * stretch;
	//加速度を追加(力/質量)
	const GSvector2 accelaration = force / mass;
	//移動速度を計算
	m_Velocity = friction * (m_Velocity + accelaration);
}
