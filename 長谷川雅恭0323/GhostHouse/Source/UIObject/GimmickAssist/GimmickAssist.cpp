#include "GimmickAssist.h"

GSuint GimmickAssist::m_bindID{(GSuint) -1 };
int GimmickAssist::m_del_count{ 0 };
GSvector2 GimmickAssist::m_pos{ GSvector2{0.0f,0.0f} };

void GimmickAssist::initialize()
{
	finalize();
}

void GimmickAssist::finalize()
{
	m_bindID = -1;
	m_del_count = 0;
}

void GimmickAssist::update()
{
	if (m_del_count <= 0 && m_bindID != -1)
	{
		m_bindID = -1;
	}
	if (m_bindID != -1 && m_del_count > 0)
	{
		m_del_count--;
	}
}

void GimmickAssist::draw()
{
	if (m_bindID == -1)return;
	gsDrawSprite2D((GSuint)TextureName::GimmiccAssist, &m_pos, NULL, &GSvector2{ 32.0f,32.0f }, NULL, NULL, NULL);
	gsDrawSprite2D(m_bindID, &m_pos, NULL, &GSvector2{ 32.0f,32.0f }, NULL, NULL, NULL);
}

void GimmickAssist::bind(GSuint texID, GSvector2 pos)
{
	if (m_bindID == texID || m_bindID == -1)
	{
		m_del_count = 1;
		m_bindID = texID;
		m_pos = pos;
	}
}
