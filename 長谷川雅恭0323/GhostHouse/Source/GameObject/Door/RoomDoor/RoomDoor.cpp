#include "RoomDoor.h"
#include "../../../Collide/BoundingSphere.h"
#include "../../../Utility/Asset/SoundName.h"
#include "../../../Scene/SceneType/SceneType.h"
#include "../../../UIObject/Operation/OperationManager.h"

RoomDoor::RoomDoor(IWorld & world
	, const GSvector3 & position
	, GSuint meshName
	, SceneInfo& info
	, float default_roll)
	:DoorBase(world
		, "Door"
		, position
		, new BoundingSphere(GSvector3(0.0f, 0.0f, 2.5f), 10.0f)
		, meshName
		, info
		, SceneType::GamePlay
		, default_roll)
	, m_reverse_open{ false }
	, m_default_roll{ default_roll }
	, p_OperationManager{ nullptr }
	, m_NextOperation{ OperationState::TutorialEnd }
{
	if (default_roll == 0)
		m_dir = DefaultDir::Left;
	else if (default_roll == 180)
		m_dir = DefaultDir::Right;
	else if (default_roll == 90)
		m_dir = DefaultDir::Back;
	else if (default_roll == 270)
		m_dir = DefaultDir::Top;
}

RoomDoor::RoomDoor(IWorld & world, const GSvector3 & position, GSuint meshName, SceneInfo & info,
	float default_roll, OperationManager & operationManager, OperationState state)
	:DoorBase(world
		, "Door"
		, position
		, new BoundingSphere(GSvector3(0.0f, 0.0f, 2.5f), 10.0f)
		, meshName
		, info
		, SceneType::GamePlay
		, default_roll)
	, m_reverse_open{ false }
	, m_default_roll{ default_roll }
	, p_OperationManager{ &operationManager }
	, m_NextOperation{ state }
{
	if (default_roll == 0)
		m_dir = DefaultDir::Left;
	else if (default_roll == 180)
		m_dir = DefaultDir::Right;
	else if (default_roll == 90)
		m_dir = DefaultDir::Back;
	else if (default_roll == 270)
		m_dir = DefaultDir::Top;
}

void RoomDoor::OnCollide(CollideActor & other)
{
	if (other.GetName() == "Player"&& is_open == false)
	{
		check_recerse(other);
		is_open = true;
		gsPlaySE((GSuint)SoundName::OpenDoorSE);

		if (p_OperationManager != nullptr)
		{
			p_OperationManager->SetCurrentState(m_NextOperation);
			//置いたライトを消す
			p_OperationManager->SetPutLightClear(true);
		}
	}
}

void RoomDoor::update_opening(float deltaTime)
{
	if (!m_reverse_open)
	{
		m_opening_timer += 0.02f * deltaTime;
		if (m_opening_timer > 1.0)
		{
			m_opening_timer = 1.0f;
			m_state = DoorState::Open;
		}
		m_Rotate.identity();
		m_Rotate.rotateY(m_default_roll);

		m_Rotate.rotate(LERP(m_opening_timer, 0.0f, 90.0f), m_Rotate.getAxisY());
	}
	else
	{
		m_opening_timer += 0.02f * deltaTime;
		if (m_opening_timer > 1.0)
		{
			m_opening_timer = 1.0f;
			m_state = DoorState::Open;
		}
		m_Rotate.identity();
		m_Rotate.rotateY(m_default_roll);

		m_Rotate.rotate(LERP(m_opening_timer, 0.0f, -90.0f), m_Rotate.getAxisY());
	}
	//update_openingなら常に呼ばれるわけではないのでここで置いたライトを消すフラグを戻す
	if (p_OperationManager != nullptr)
	{
		p_OperationManager->SetPutLightClear(false);
	}
}

void RoomDoor::check_recerse(CollideActor& other)
{
	switch (m_dir)
	{
	case RoomDoor::Right:
		if (m_Position.x > other.GetPosition().x)
			m_reverse_open = true;
		break;
	case RoomDoor::Left:
		if (m_Position.x < other.GetPosition().x)
			m_reverse_open = true;
		break;
	case RoomDoor::Back:
		if (m_Position.z > other.GetPosition().z)
			m_reverse_open = true;
		break;
	case RoomDoor::Top:
		if (m_Position.z < other.GetPosition().z)
			m_reverse_open = true;
		break;
	default:
		break;
	}
}
