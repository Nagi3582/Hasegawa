#include "NumberTexture.h"

#include<sstream>
#include<iomanip>

NumberTexture::NumberTexture(int width, int height)
	:m_width{ width }
	, m_height{ height }
{
}

void NumberTexture::draw(const GSvector2 & position, int num, int digit, char fill) const
{
	std::stringstream ss;
	ss << std::setw(digit) << std::setfill(fill) << num;
	draw(position, ss.str());
}

//void NumberTexture::draw_t(const GSvector2 & position, int num, int digit,  float alpha, char fill) const
//{
//	std::stringstream ss;
//	ss << std::setw(digit) << std::setfill(fill) << num;
//	draw_t(position, ss.str(), alpha);
//}

void NumberTexture::draw(const GSvector2 & position, int num, float scale) const
{
	draw(position, std::to_string(num), scale);
}

void NumberTexture::draw(const GSvector2 & position, const std::string & num, float scale) const
{
	for (int i = 0; i < (int)num.size(); i++)
	{
		if (num[i] == ' ')continue;
		const int n = num[(num.size() - 1) - i] - '0';
		const GSrect rect{ (float)n*m_width,0.0f,(float)(n*m_width) + (float)m_width,(float)m_height };
		const GSvector2 pos{ position.x - i*m_width*scale,position.y };

		GSvector2 l_Scale{ scale,scale };

		gsDrawSprite2D((GSuint)TextureName::NumberTexture, &pos, &rect, NULL, NULL, &l_Scale, 0);
	}
}

//void NumberTexture::draw_t(const GSvector2 & position, const std::string & num, float alpha) const
//{
//	for (int i = 0; i < (int)num.size(); i++)
//	{
//		if (num[i] == ' ')continue;
//		const int n = num[i] - '0';
//		const GSrect rect{ (float)n*m_width,0.0f,(float)(n*m_width) + (float)m_width,(float)m_height };
//		const GSvector2 pos{ position.x + i*m_width,position.y };
//		gsDrawSprite2D((GSuint)TextureName::NumberTexture, &pos, &rect, NULL, &GScolor{ 1.0f,1.0f,1.0f,alpha }, NULL, 0);
//	}
//
//}
