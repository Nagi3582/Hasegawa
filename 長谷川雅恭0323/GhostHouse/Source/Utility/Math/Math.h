#ifndef _MATH_H_
#define _MATH_H_
#include <gslib.h>

class Math
{
public:
	/*
	***3������Ԃ�2�̓_�̋���***
	����1�F�n�_
	����2�F�I�_
	*/
	static float Distance(GSvector3 start, GSvector3 end);

	/*
	***2������Ԃ�2�̓_�̋���***
	����1�F�n�_
	����2�F�I�_
	*/
	static float Distance(GSvector2 start, GSvector2 end);

	/*
	***�O��***
	����1�F�x�N�g��1
	����2�F�x�N�g��2
	*/
	static GSvector3 Cross(const GSvector3& v1, const GSvector3& v2);

	/*
	***2�����x�N�g���̓���***
	����1�F�x�N�g��1
	����2�F�x�N�g��2
	*/
	static float Dot(const GSvector2 v1, const GSvector2 v2);

	/*
	***3�����x�N�g���̓���***
	����1�F�x�N�g��1
	����2�F�x�N�g��2
	*/
	static float Dot(const GSvector3 v1, const GSvector3 v2);

	/*
	***�@�A�[�N�^���W�F���g�@�p�x�����߂�***
	����1�F��ӂ̒���
	����2�F�����̒���
	*/
	static float ArcTangent(const float& x, const float& y);

	/*
	***�p�x(180�x�܂�)***
	����1�F�x�N�g��1
	����2�F�x�N�g��2
	*/
	static float Angle(const GSvector2& first_vec2, const GSvector2& second_vec2);

	/*
	***�x�N�g���̉�]***
	����1�F��]������x�N�g��
	����2�F��]����p�x
	*/
	static GSvector2 Vec2_Turn(const GSvector2& v, float& angle);

	/*
	***��Βl�����߂�***
	*/
	static float Absolute(float& f);

	//�x�N�g�����E�������������߂�()
	//	����1�F�厲�ƂȂ�x�N�g��
	//	����2�F���߂�x�N�g��
	static bool TurnLeft(GSvector2 main, GSvector2 ask);

	//�x�N�g���̉�]
	static GSvector2 Vec2_Turn(GSvector2 vec2, float angle);

	//���W�A���p���p�x�ɕϊ�
	static float To_Degree(float radian);

	//�p�x�����W�A���p�ɕϊ�
	static float To_Radian(float degree);

	/*
	***�������덷���Ȃ���***
	�����F0�ɂ�������
	*/
	static float FloatZero(float& f);

	/*��������*/
	static float Sqrt(float square);

	/****�������덷���Ȃ���****/
	static const float EPSILON;


};

#endif // !_ENEMYSUPPORT_H_
