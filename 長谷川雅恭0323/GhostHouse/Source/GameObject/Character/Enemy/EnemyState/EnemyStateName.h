#ifndef _ENEMY_STATE_NAME_H_
#define _ENEMY_STATE_NAME_H_

enum class EnemyStateName
{
	Idle = 0,	//����
	Approach,	//�v���C���[���߂Â�
	Stop,		//�~�܂�
	Attack,		//�U��
	Laugh,		//�U���𓖂Ă�Ɛ���

	None,

};

#endif // !_ENEMY_STATE_NAME_H_
