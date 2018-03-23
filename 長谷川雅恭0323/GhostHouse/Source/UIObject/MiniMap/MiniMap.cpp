#include "MiniMap.h"
#include "../../Base/Screen.h"
#include "../../Scene/SceneInfo/SceneInfo.h"
#include "../../Actor/CollideActor.h"
#include "../../Utility/Asset/TextureName.h"

const float k_StageMapSide = 1200;	//ステージミニマップの縦横の幅
const float k_StageCenterX = 600;	//ステージマップの中心位置のX座標
const float k_StageCenterY = 800;	//ステージマップの中心位置のY座標


MiniMap::MiniMap(IWorld& world, CollideActor & player, SceneInfo& info, int stage)
	: UITexture{ world,"MiniMap",GSvector2(WIDTH - 130,HEIGHT - 130) ,200,200 }
	, p_Player{ &player }
	, m_Info{ info }
	, m_StageMapPosition{ 0.0f,0.0f }
	, m_Texture{ TextureName::MiniMapStage1 }
	, m_PlayerAlpha{ 0.7f }
	, m_PlayerAlphaPlus{ 0.004f }
{
	SetTexture(stage);
}

void MiniMap::on_update(float deltaTime)
{
	m_StageMapPosition.x = -p_Player->GetPosition().x + k_StageCenterX;
	m_StageMapPosition.y = -(p_Player->GetPosition().z + 110) + k_StageCenterY;


	//プレイヤーの位置を点滅させる
	m_PlayerAlpha += m_PlayerAlphaPlus * deltaTime;
	if (m_PlayerAlpha >= 1.0f || m_PlayerAlpha <= 0.7f)
	{
		m_PlayerAlphaPlus *= -1;
	}

}

void MiniMap::on_draw() const
{
	if (m_Info.m_PlayerDead == true || m_Info.m_Pause == true)return;

	//ミニマップ背景
	{
		const GSvector2 l_Center(100.0f, 100.0f);
		gsDrawSprite2D((GSuint)TextureName::MiniMapBack, &GSvector2(m_position.x, m_position.y), NULL, &l_Center, &GScolor(1.0f, 1.0f, 1.0f, 0.7f), NULL, 0.0f);
	}

	//ステージのミニマップを表示
	{
		const GSrect l_Rect(m_StageMapPosition.x - 100, m_StageMapPosition.y - 100, m_StageMapPosition.x + 100, m_StageMapPosition.y + 100);
		const float l_Scale = 0.7f;
		gsDrawSprite2D((GSuint)m_Texture, &GSvector2(m_position.x - 100, m_position.y - 100), &l_Rect, NULL, &GScolor(1.0f, 1.0f, 1.0f, 0.7f), NULL, 0.0f);
	}


	//プレイヤーの位置表示
	{
		const GSvector2 l_Center(5.0f, 5.0f);
		const GScolor l_Color(m_PlayerAlpha, m_PlayerAlpha, m_PlayerAlpha, 1.0f);
		gsDrawSprite2D((GSuint)TextureName::MiniMapPlayer, &GSvector2(m_position.x, m_position.y), NULL, &l_Center, &l_Color, NULL, 0.0f);
	}

}

void MiniMap::SetTexture(int stage)
{
	if (stage == 1)
	{
		m_Texture = TextureName::MiniMapStage1;
	}
	else if (stage == 2)
	{
		m_Texture = TextureName::MiniMapStage2;
	}
	else if (stage == 3)
	{
		m_Texture = TextureName::MiniMapStage3;
	}
	else if (stage == 4)
	{
		m_Texture = TextureName::MiniMapStage4;
	}
	else if (stage == 5)
	{
		m_Texture = TextureName::MiniMapStage5;
	}
	else if (stage == 6)
	{
		m_Texture = TextureName::MiniMapStage6;
	}
	else if (stage == 7)
	{
		m_Texture = TextureName::MiniMapStage7;
	}
	else if (stage == 8)
	{
		m_Texture = TextureName::MiniMapStage8;
	}
	else if (stage == 9)
	{
		m_Texture = TextureName::MiniMapStage9;
	}
	else if (stage == 10)
	{
		m_Texture = TextureName::MiniMapStage10;
	}
}
