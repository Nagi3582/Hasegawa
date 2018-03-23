#ifndef _SCENE_TYPE_H_
#define _SCENE_TYPE_H_


enum class SceneType
{
	GameTitle			= 0,	   // csv�̃X�e�[�W�ԍ��ƍ��킹��
	GamePlay			= 1,

	Stage1				= 1,
	Stage2				= 2,
	Stage3				= 3,
	Stage4				= 4,
	Stage5				= 5,
	Stage6				= 6,
	Stage7				= 7,
	Stage8				= 8,
	Stage9				= 9,		
	Stage10				= 10,


	GameOver			= 100,
	GameResult			= 101,	   // ���U���g�V�[��
	Operation			= 102,
	GameClear			= 103,

	ShaderTest			= 103,     //�V�F�[�_�[�e�X�g�p

	Debug				= 104,	   //�f�o�b�N�p�X�e�[�W

	None				= 1000,	   //�ǂ̃X�e�[�W�ł��ǂݍ��ރ��\�[�X�p

};

#endif // !_SCENE_TYPE_H_
