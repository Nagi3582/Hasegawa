#ifndef _TEXTURE_NAME_H_
#define _TEXTURE_NAME_H_

//************************
// ID�̂���
// 3���ڂ�ǂݍ��ރV�[�����Ƃɕς���

// 9 = �S���̃V�[���œǂݍ���
// 1 = �^�C�g��
// 2 = �v���C�V�[��
// 3 = ���U���g

//************************

enum class TextureName
{
	Title									= 101,	//�^�C�g��

	Cursor									= 201,	//�J�[�\��
	GameOver								= 280,	//�Q�[���I�[�o�[����
	Retry									= 281,	//���g���C����
	Pause									= 290,	//�|�[�Y����
	BackGame								= 205,	//�Q�[���ɖ߂镶��
	TitleReturn								= 206,  //�^�C�g���ɖ߂镶��


	Battery									= 207,	//�o�b�e���[UI
	Window									= 208,	//���C�gUI�̘g
	Red_light								= 209,	//�Ԃ����C�g
	Green_light								= 210,	//�΂̃��C�g
	Blue_light								= 211,	//�����C�g
	White_light								= 212,	//�������C�g
	UICursor								= 213,	//���C�g�̑I���J�[�\��
	Kakeru									= 214,	//���C�g�̌�

	Gage_Frame								= 215,	//�Q�[�W�i�t���[���j
	Gage									= 216,	//�Q�[�W
	GimmiccAssist							= 217,	//����A�V�X�g�i�����o���j
	GimmiccAssist_ButtomX					= 218,	//����A�V�X�g�iX�{�^���j
	GimmiccAssist_ButtomA					= 221,	//����A�V�X�g�iA�{�^���j
	GimmiccAssist_ButtomB					= 222,	//����A�V�X�g�iB�{�^���j
	GimmiccAssist_CulorPurple				= 223,//����A�V�X�g�i������j
	GimmiccAssist_CulorYellow				= 224,//����A�V�X�g�i���F�j
	GimmiccAssist_CulorLightblue			= 225,//����A�V�X�g�i���F�j


	ExclamationMark							= 219,	//�G�ɔ������ꂽ�r�b�N���}�[�N
	ExclamationRed							= 220,	//�G�ɔ������ꂽ��Ԃ������

	Key										= 230,	//��
	Key_Window								= 231,	//���̎擾�g

	StageTitle1								= 232,	//�X�e�[�W�^�C�g��1
	StageTitle2								= 233,	//�X�e�[�W�^�C�g��2
	StageTitle3								= 234,	//�X�e�[�W�^�C�g��3
	StageTitle4								= 235,	//�X�e�[�W�^�C�g��4
	StageTitle5								= 236,	//�X�e�[�W�^�C�g��5
	StageTitle6								= 237,	//�X�e�[�W�^�C�g��6
	StageTitle7								= 238,	//�X�e�[�W�^�C�g��7
	StageTitle8								= 239,	//�X�e�[�W�^�C�g��8
	StageTitle9								= 240,	//�X�e�[�W�^�C�g��9
	StageTitle10							= 241,	//�X�e�[�W�^�C�g��10
	StageTitle_rouka						= 242,	//�X�e�[�W�^�C�g���L��
	StageTitleFrame							= 243,	//�X�e�[�W�^�C�g���t���[��

	ItemTakeWhiteLight						= 260,	//�������C�g����肵��UI
	ItemTakeRedLight						= 261,	//�Ԃ����C�g����肵��UI
	ItemTakeGreenLight						= 262,	//�΂̃��C�g����肵��UI
	ItemTakeBlueLight						= 263,	//�����C�g����肵��UI
	ItemTakeBattery							= 264,	//�o�b�e���[����肵��UI
	ItemTakeKey								= 265,	//������肵��UI


	TakeLight								= 300,	//���C�g���E�����o��
	TakeLightOperation						= 301,	//���C�g���E������
	ChangeLight								= 302,	//���C�g�̐؂�ւ�����
	PutLight								= 303,	//���C�g��u�����o��
	TakeShiningLight						= 304,	//�u�������C�g���E�����o��
	TakeBattery								= 305,	//�o�b�e���[���E�����o��
	BatteryOperation						= 306,	//�o�b�e���[�̐���
	TakeKey									= 307,	//�����E�����o��
	TakeKeyOperate							= 308,	//�����E������
	EnemyStop								= 309,	//�G�̓������~�߂錩�o��
	EnemyStopOperation						= 310,	//�G�̓������~�߂����
	EnemyStopPutLight						= 311,	//�u�������C�g�œG�̓������~�߂錩�o��
	OpenNormalDoor							= 312,	//�ʏ�h�A�̌��o��
	NormalDoorOperation						= 313,	//�ʏ�h�A�̐���
	OpenLockDoor							= 314,	//���h�A�̐���
	OpenColorDoor							= 315,	//�F�t���h�A�̌��o��
	ColorDoorOperate						= 316,	//�F�t���h�A�̐���
	ColorDoorPutLight						= 317,	//�F�t���h�A���C�g��u�����o��
	ColorDoorPutLightOperation				= 318,	//�F�t���h�A���C�g��u������
	ColorDoorOperate2						= 319,	//�F�t���h�A�̐���2
	NextRoom								= 320,	//���̕����Ɉړ����o��
	TutorialEnd								= 321,	//�`���[�g���A���I�����o��
	
	OperationCharBack						= 330,	//�`���[�g���A�����o���̔w�i


	MiniMapBack								= 400,	//�~�j�}�b�v�w�i
	MiniMapStage1							= 401,	//�X�e�[�W1�~�j�}�b�v
	MiniMapStage2							= 402,	//�X�e�[�W2�~�j�}�b�v
	MiniMapStage3							= 403,	//�X�e�[�W3�~�j�}�b�v
	MiniMapStage4							= 404,	//�X�e�[�W4�~�j�}�b�v
	MiniMapStage5							= 405,	//�X�e�[�W5�~�j�}�b�v
	MiniMapStage6							= 406,	//�X�e�[�W6�~�j�}�b�v
	MiniMapStage7							= 407,	//�X�e�[�W7�~�j�}�b�v
	MiniMapStage8							= 408,	//�X�e�[�W8�~�j�}�b�v
	MiniMapStage9							= 409,	//�X�e�[�W9�~�j�}�b�v
	MiniMapStage10							= 410,	//�X�e�[�W10�~�j�}�b�v

	MiniMapPlayer							= 420,	//�~�j�}�b�v�̃v���C���[�ʒu



	Clear									= 700,	//�N���A�[



	ResultTitle								= 800,	//�u���U���g�v�̕�����\��
	NextB									= 801,	//B�{�^���Ŏ��ɐi��
	DoorIcon								= 802,	//�ʏ�h�A�̃A�C�R��
	ColorDoorIcon							= 803,	//3�F�h�A�̃A�C�R��
	MixColorDoorIcon						= 804,	//�����F�h�A�̃A�C�R��
	MusicBoxIcon							= 805,	//�I���S�[���̃A�C�R��
	Equal									= 806,	//�u=�v�̕�����\��
	ResultScore								= 807,	//�u�_�v�̕�����\��




	NumberTexture							= 900,	//��������

	OperationControl						= 901,
	OperationGhost							= 902,
	OperationDoor							= 903,


	ScreenHide								= 999,	//��ʂ̐F��ς���

};

#endif // !_TEXTURE_NAME_H_
