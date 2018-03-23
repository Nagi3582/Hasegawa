#ifndef NUMBER_TEXTURE_H_
#define NUMBER_TEXTURE_H_

#include<gslib.h>
#include<string>

#include"../Asset/TextureName.h"

class NumberTexture
{
public:
	NumberTexture(int width, int height);
	//�`��
	void draw(const GSvector2&position, int num, int digit, char fill = '0')const;
	////�`��
	//void draw_t(const GSvector2 & position, int num, int digit, float alpha, char fill = '0') const;
	//�`��
	void draw(const GSvector2&position, int num, float scale = 1.0f)const;
	//�`��
	void draw(const GSvector2&position, const std::string&num ,float scale = 1.0f)const;
	////�`��
	//void draw_t(const GSvector2 & position, const std::string & num, float alpha) const;

private:
	//�����̕�
	int m_width;
	//�����̍���
	int m_height;

};

#endif // !NUMBER_TEXTURE_H_