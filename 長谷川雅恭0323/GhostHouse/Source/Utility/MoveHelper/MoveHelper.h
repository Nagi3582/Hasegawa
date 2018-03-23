#ifndef _MOVE_HELPER_H_
#define _MOVE_HELPER_H_
#include <gslib.h>

class MoveHelper
{
public:
	/*
	�Ȃ߂炩�ȏ㉺�ړ�(sin�g)
	����1�F1�����鎞��
	����2�F��f������J�E���^�[
	����3�F�ړ�����͈�
	*/
	static float EasingSwing(const float& swingTime, float& count, const float& range);

	/*
	�~��`���悤�Ɉړ�����
	����1�F���S��X���W
	����2�F���S��Y���W
	����3�F���S���痣��鋗��
	����4�F��]���x
	����5�F�p�x(�Q��)
	����6�F�f���^�^�C��
	*/
	static GSvector2 CircleRotate(float baseX, float baseY, float distance, float speed, float& angle, float deltaTime);


	//�u�[����true��false�𔽓]������
	static void BoolReverse(bool& reverse);


};

#endif // !_MOVE_HELPER_H_
