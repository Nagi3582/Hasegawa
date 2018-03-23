#include "Score.h"
#include"../../../Utility/Asset/TextureName.h"
#include "../../Item/ItemManager/ItemManager.h"
#include "../../Light/LightColor.h"
#include "../../../Scene/SceneInfo/SceneInfo.h"
#include "../../../Utility/Number/NumberTexture.h"

const int NUMBER_MAX = 8;

const float l_Scale = 0.5f;
const float l_Width = 170.0f * l_Scale;
const float l_Height = 130.0f * l_Scale;


Score::Score(IWorld & world, Renderer & renderer, ItemManager& item, SceneInfo& info)
	: m_position{ 0.0f,0.0f,0.0f }
	, m_ResultIcon{ world }
	, p_Item{ &item }
	, m_Info{ info }
{

}

void Score::initialize()
{
	int l_Numbers[NUMBER_MAX] = {
		p_Item->GetLightSize(LightColor::White),
		p_Item->GetLightSize(LightColor::Green),
		p_Item->GetLightSize(LightColor::Red),
		p_Item->GetLightSize(LightColor::Blue),
		m_Info.m_MusicBox,
		m_Info.m_Door,
		m_Info.m_ColorDoor ,
		m_Info.m_MixColorDoor,
	};

	for (int i = 0; i < NUMBER_MAX; ++i)
	{
		m_Numbers[i] = l_Numbers[i];
	}

	int l_Scores[NUMBER_MAX] = {
		100,
		200,
		200,
		200,
		300,
		1000,
		1500,
		2000,
	};

	for (int i = 0; i < NUMBER_MAX; ++i)
	{
		m_Scores[i] = l_Scores[i];
	}
}

void Score::update(float deltaTime)
{
	m_ResultIcon.main_update(deltaTime);
}

void Score::draw() const
{
	////各種レンダリングモードの退避
	//glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	////ライティングをオフにする
	//glDisable(GL_LIGHTING);
	////zバッファに書き込みを行わない
	//glDepthMask(GL_FALSE);
	////加算ブレンドを有効にする
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glEnable(GL_BLEND);
	////3Dスプライトの表示
	//gsDrawSprite3D((int)TextureName::ScoreSample, &m_position, &GSrect{ 0,0,2.8f,2.5f }, &GSrect{ 0,0,100,100 }, NULL, NULL, NULL);
	////各種レンダリングモードの復帰
	//glPopAttrib();
	//gsDrawSprite2D(0, &GSvector2{ 170,140 }, NULL, NULL, NULL, &GSvector2{ 5.5f,3.25f }, NULL);/*スコアボードの大きさ幅：550　高さ：325*/

	m_ResultIcon.main_draw();

	drawNum();
	drawScore();
	drawMultiply();
	drawTortalScore();

}

void Score::drawNum()const
{
	const int l_NumberSize = 50;
	static const NumberTexture l_Number(l_NumberSize, l_NumberSize);


	const GSvector2 l_BasePos(220.0f + 30 + (l_Width * 2), 130.0f);
	GSvector2 l_Pos = l_BasePos;

	for (int i = 0; i < NUMBER_MAX; ++i)
	{
		l_Number.draw(l_Pos, m_Numbers[i], l_Scale);

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

void Score::drawScore() const
{
	const int l_NumberSize = 50;
	static const NumberTexture l_Number(l_NumberSize, l_NumberSize);


	const GSvector2 l_BasePos(220.0f + l_Width + l_NumberSize, 130.0f);
	GSvector2 l_Pos = l_BasePos;

	for (int i = 0; i < NUMBER_MAX; ++i)
	{
		l_Number.draw(l_Pos, m_Scores[i], l_Scale);

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

void Score::drawMultiply() const
{
	const GSvector2 l_BasePos(220.0f + (l_Width * 2), 130.0f + 5.0f);
	GSvector2 l_Pos = l_BasePos;

	for (int i = 0; i < NUMBER_MAX; ++i)
	{
		const float l_MultiplyScale = 0.5f;
		const float l_MultiplyWidth = 50.0f * l_MultiplyScale;
		const float l_MultiplyHeight = 50.0f * l_MultiplyScale;
		const GSrect l_Rect(0.0f, 0.0f, l_MultiplyWidth / l_MultiplyScale, l_MultiplyHeight / l_MultiplyScale);
		const GSvector2 l_Center(l_MultiplyWidth / 2, l_MultiplyHeight / 2);

		gsDrawSprite2D((GSuint)TextureName::Kakeru, &l_Pos, &l_Rect, &l_Center, NULL, &GSvector2(l_MultiplyScale, l_MultiplyScale), NULL);

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

void Score::drawTortalScore() const
{
	const int l_NumberSize = 50;
	static const NumberTexture l_Number(l_NumberSize, l_NumberSize);

	const GSvector2 l_Pos(580.0f, 480.0f);

	int l_TortalScore = 0;

	for (int i = 0; i < NUMBER_MAX; ++i)
	{
		l_TortalScore += m_Numbers[i] * m_Scores[i];
	}


	l_Number.draw(l_Pos, l_TortalScore);


	const float l_EqualScale = 0.5f;
	const float l_Width = 100.0f * l_EqualScale;
	const float l_Height = 70.0f * l_EqualScale;
	const GSvector2 l_EqualPos = l_Pos - GSvector2((l_Width + 30) * 3 + 20, -l_Width / 2 + 10);
	const GSrect l_Rect(0.0f, 0.0f, l_Width / l_EqualScale, l_Height / l_EqualScale);
	const GSvector2 l_Center(l_Width / 2, l_Height / 2);
	gsDrawSprite2D((GSuint)TextureName::Equal, &l_EqualPos, &l_Rect, &l_Center, NULL, &GSvector2(l_EqualScale, l_EqualScale), NULL);

}
