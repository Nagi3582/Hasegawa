#ifndef _PLAYER_STATE_H_
#define _PLAYER_STATE_H_

enum class PlayerState
{
	Idle = 0,	//�ʏ�
	PickUp,		//�E��
	Put,		//�u��
	OpenDoor,	//�h�A���J����
	Grab,		//���Ƃ�����
	Damage,		//�_���[�W���󂯂�
	Dead,		//���S(�Q�[���I�[�o�[)


	None,

};

#endif // !_PLAYER_STATE_H_
