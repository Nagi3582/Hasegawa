#include "ExclamationMark.h"
#include "../../Actor/CollideActor.h"
#include "../../Base/Screen.h"
#include "../../Utility/Math/Math.h"

ExclamationMark::ExclamationMark(IWorld & world, CollideActor & player, CollideActor & enemy)
	: UITexture{ world,"Exclamation",GSvector2(0.0f,0.0f),40,60 }
	, p_Player{ &player }
	, p_Enemy{ &enemy }
	, m_RedPosition{ 0.0f,0.0f }
{
}

void ExclamationMark::on_update(float deltaTime)
{
	//画像を表示しない場合はリターン
	if (m_is_draw == false)return;

	//プレイヤーから敵の方向を2次元ベクトルに変換
	GSvector3 l_Vec3_Direction = p_Player->GetPosition() - p_Enemy->GetPosition();
	GSvector2 l_Direction(l_Vec3_Direction.x, l_Vec3_Direction.z);

	//位置を中心に合わせる
	m_position = GSvector2(WIDTH / 2, HEIGHT / 2);
	//画面外に出るように 画面の最大サイズの半分(半分より若干大きめ) を掛ける
	//30fpsの為deltaTimeを2で割る
	m_position += l_Direction.getNormalized() * WIDTH / 1.5f * deltaTime / 2;
	m_RedPosition = m_position;


	//クランプで画面内に戻す
	const float l_NearCenter = 40.0f;
	m_position.x = CLAMP(m_position.x, 0.0f + l_NearCenter, WIDTH - l_NearCenter);
	m_position.y = CLAMP(m_position.y, 0.0f + l_NearCenter, HEIGHT - l_NearCenter);

	const float l_LeaveCenterX = 35.0f;
	const float l_LeaveCenterY = 40.0f;
	m_RedPosition.x = CLAMP(m_RedPosition.x, 0.0f - l_LeaveCenterX, WIDTH + l_LeaveCenterX);
	m_RedPosition.y = CLAMP(m_RedPosition.y, 0.0f - l_LeaveCenterY, HEIGHT + l_LeaveCenterY);


}

void ExclamationMark::on_draw() const
{
	//{
	//	const float l_Width = 100.0f;
	//	const float l_Height = 100.0f;
	//	GSrect l_Rect(0.0f, 0.0f, l_Width, l_Height);
	//	GScolor l_Color(1.0f, 1.0f, 1.0f, 0.15f);
	//	GSvector2 l_Scale(1.8f, 3.0f);
	//	GSvector2 l_Center(l_Width / 2, l_Height / 2);
	//	gsDrawSprite2D((GSuint)TextureName::ExclamationRed, &m_RedPosition, &l_Rect, &l_Center, &l_Color, &l_Scale, NULL);
	//}
	//{
	//	const float l_Width = 40.0f;
	//	const float l_Height = 60.0f;
	//	GSrect l_Rect(0.0f, 0.0f, l_Width, l_Height);
	//	GScolor l_Color(1.0f, 1.0f, 1.0f, 0.5f);
	//	GSvector2 l_Scale(0.5f, 0.5f);
	//	GSvector2 l_Center(l_Width / 2, l_Height / 2);
	//	gsDrawSprite2D((GSuint)TextureName::ExclamationMark, &m_position, &l_Rect, &l_Center, &l_Color, &l_Scale, NULL);
	//}

	{
	}
}
