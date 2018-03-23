#include "ObjectGenerator.h"
#include "../../Utility/csvReader/csvReader.h"
#include "../../World/World.h"
#include "../SceneType/SceneType.h"
#include "../../UI/UIGroup.h"
#include "../../UIObject/MiniMap/MiniMap.h"

#include "../../Actor/ActorGroup.h"
#include "../../GameObject/Character/Enemy/WhiteEnemy.h"
#include "../../GameObject/Character/Enemy/RedEnemy.h"
#include "../../GameObject/Character/Enemy/GreenEnemy.h"
#include "../../GameObject/Character/Enemy/BlueEnemy.h"
#include "../../GameObject/Character/Enemy/MusicEnemy.h"

#include "../../GameObject/Item/Flashlight/FlashLight.h"

#include "../../GameObject/Door/NormalDoor.h"
#include "../../GameObject/Door/ColorDoor/ColorDoor.h"
#include "../../GameObject/Door/LockDoor/LockDoor.h"

#include "../../GameObject/Item/Battery/Battery.h"
#include "../../GameObject/Item/DoorKey/DoorKey.h"

#include "../../GameObject/Character/Player/Player.h"
#include "../../GameObject/Camera/Camera.h"

#include "../../GameObject/Field/Field.h"

#include "../../GameObject/Item/DummyKey/DummyKey.h"

#include"../../GameObject/Door/RoomDoor/RoomDoor.h"
#include"../../GameObject/Item/Flashlight/RePopFlashLight.h"

//******** CSV�p ********************************************
//static const int STAGE_ID						= 1;
static const int OBJECT_ID = 2;
static const int POS_X = 3;
static const int POS_Y = 4;
static const int POS_Z = 5;
//***********************************************************


//**** �I�u�W�F�N�gID ***************************************
static const int WHITE_ENEMY = 0;	//�����΂�
static const int RED_ENEMY = 1;	//�Ԃ��΂�
static const int GREEN_ENEMY = 2;	//�΂��΂�
static const int BLUE_ENEMY = 3;	//���΂�
static const int MUSIC_ENEMY = 4;	//�I���S�[�����΂�
static const int WHITE_LIGHT = 5;	//�����C�g
static const int RED_LIGHT = 6;	//�ԃ��C�g
static const int GREEN_LIGHT = 7;	//�΃��C�g
static const int BLUE_LIGHT = 8;	//���C�g
static const int NORMAL_DOOR = 9;	//�ʏ�h�A
static const int RED_DOOR = 10;	//�ԃh�A
static const int GREEN_DOOR = 11;	//�΃h�A
static const int BLUE_DOOR = 12;	//�h�A
static const int YERROW_DOOR = 13;	//���F�h�A
static const int LIGHTBLUE_DOOR = 14;	//���F�h�A
static const int PURPLE_DOOR = 15;	//���F�h�A
static const int LOCK_DOOR = 16;	//���t���h�A


static const int BATTERY = 17;	//�o�b�e���[
static const int DOOR_KEY = 18;	//�h�A�̌�

static const int ROOM_DOOR_LEFT = 19;	//���J���h�A
static const int ROOM_DOOR_RIGHT = 20;	//�E�J���h�A
static const int ROOM_DOOR_BACK = 21;	//���J���h�A

static const int RE_POP_LIGHT_R = 22;	//�Đ������C�g��
static const int RE_POP_LIGHT_G = 23;	//�Đ������C�g��
static const int RE_POP_LIGHT_B = 24;	//�Đ������C�g��
//***********************************************************

static const int STAGE_MAX = 10;	//�X�e�[�W�̐�



ObjectGenerator::ObjectGenerator(World & world, Renderer & renderer, ItemManager & item, SceneInfo& info, SceneType scene)
	: p_World{ &world }
	, p_Player{ nullptr }
	, p_Renderer{ &renderer }
	, p_Item{ &item }
	, m_Info{ info }
	, m_Scene{ scene }
{
}


void ObjectGenerator::Generator(int stage)
{
	//��ԍŌ�̃X�e�[�W�̏ꍇ���U���g�V�[���Ɉړ�
	if (stage == STAGE_MAX)	m_Scene = SceneType::GameResult;

	CollideActorPtr l_Player = std::make_shared<Player>(*p_World, GSvector3(0.0f, 0.0f, -110.0f), *p_Renderer, *p_Item, m_Info);
	p_Player = l_Player.get();
	p_World->AddCollideActor(ActorGroup::Player, l_Player);
	CollideActorPtr l_CameraPtr = std::make_shared<Camera>(l_Player);
	p_World->AddCamera(l_CameraPtr);
	p_World->AddField(std::make_shared<Field>(FieldName::Stage));

	Camera* l_Camera = dynamic_cast<Camera*>(l_CameraPtr.get());


	csvReader l_CSV;
	l_CSV.Load("Resource/csv/Object.csv");

	for (int i = 1; i < l_CSV.GetLineSize(); ++i)
	{
		//�X�e�[�W�ԍ����Ⴄ�ꍇ�������Ȃ�
		if (l_CSV.GetI(i, STAGE_ID) != stage)continue;

		AddObject(l_CSV.GetI(i, OBJECT_ID), GSvector3(l_CSV.GetF(i, POS_X), l_CSV.GetF(i, POS_Y), l_CSV.GetF(i, POS_Z)));
	}

	//�~�j�}�b�v����
	p_World->AddUI(UIGroup::main, std::make_shared<MiniMap>(*p_World, *l_Player.get(), m_Info, stage));

}

void ObjectGenerator::AddObject(int objectID, GSvector3 position)
{
	if (objectID == WHITE_ENEMY) p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<WhiteEnemy>(*p_World, position, *p_Player, *p_Renderer));
	if (objectID == RED_ENEMY)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<RedEnemy>(*p_World, position, *p_Player, *p_Renderer));
	if (objectID == GREEN_ENEMY)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<GreenEnemy>(*p_World, position, *p_Player, *p_Renderer));
	if (objectID == BLUE_ENEMY)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<BlueEnemy>(*p_World, position, *p_Player, *p_Renderer));
	if (objectID == MUSIC_ENEMY)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<MusicEnemy>(*p_World, position, *p_Player, *p_Renderer, m_Info));

	if (objectID == WHITE_LIGHT)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<Flashlight>(*p_World, position, LightColor::White, *p_Item));
	if (objectID == RED_LIGHT)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<Flashlight>(*p_World, position, LightColor::Red, *p_Item));
	if (objectID == GREEN_LIGHT)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<Flashlight>(*p_World, position, LightColor::Green, *p_Item));
	if (objectID == BLUE_LIGHT)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<Flashlight>(*p_World, position, LightColor::Blue, *p_Item));

	if (objectID == NORMAL_DOOR)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<NormalDoor>(*p_World, position, (int)MeshName::Door, m_Info, m_Scene));
	if (objectID == RED_DOOR)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<ColorDoor>(*p_World, position, m_Info, m_Scene, (int)MeshName::RedDoor, 1, LightColor::Red));
	if (objectID == GREEN_DOOR)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<ColorDoor>(*p_World, position, m_Info, m_Scene, (int)MeshName::GreenDoor, 1, LightColor::Green));
	if (objectID == BLUE_DOOR)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<ColorDoor>(*p_World, position, m_Info, m_Scene, (int)MeshName::BlueDoor, 1, LightColor::Blue));
	if (objectID == YERROW_DOOR)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<ColorDoor>(*p_World, position, m_Info, m_Scene, (int)MeshName::YellowDoor, 2, LightColor::Red, LightColor::Green));
	if (objectID == LIGHTBLUE_DOOR)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<ColorDoor>(*p_World, position, m_Info, m_Scene, (int)MeshName::LightBlueDoor, 2, LightColor::Blue, LightColor::Green));
	if (objectID == PURPLE_DOOR)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<ColorDoor>(*p_World, position, m_Info, m_Scene, (int)MeshName::PurpleDoor, 2, LightColor::Red, LightColor::Blue));
	if (objectID == LOCK_DOOR)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<LockDoor>(*p_World, position, (int)MeshName::LockDoor, m_Info, m_Scene));

	if (objectID == BATTERY)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<Battery>(*p_World, position, *p_Item));
	if (objectID == DOOR_KEY)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<DoorKey>(*p_World, position, *p_Item, m_Info));

	if (objectID == ROOM_DOOR_LEFT)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<RoomDoor>(*p_World, position, (GSuint)MeshName::Door, m_Info, 0));
	if (objectID == ROOM_DOOR_RIGHT)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<RoomDoor>(*p_World, position, (GSuint)MeshName::Door, m_Info, 180));
	if (objectID == ROOM_DOOR_BACK)
		p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<RoomDoor>(*p_World, position, (GSuint)MeshName::Door, m_Info, 270));

	if (objectID == RE_POP_LIGHT_R)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<RePopFlashLight>(*p_World, position, LightColor::Red, *p_Item));
	if (objectID == RE_POP_LIGHT_G)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<RePopFlashLight>(*p_World, position, LightColor::Green, *p_Item));
	if (objectID == RE_POP_LIGHT_B)p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<RePopFlashLight>(*p_World, position, LightColor::Blue, *p_Item));

}

void ObjectGenerator::AddField(int stage)
{
	//FieldName l_Name = FieldName::Stage1;

	//if (stage == 2)l_Name = FieldName::Stage2;
	//if (stage == 3)l_Name = FieldName::Stage3;

	//p_World->AddField(std::make_shared<Field>(FieldName::Stage));
}
