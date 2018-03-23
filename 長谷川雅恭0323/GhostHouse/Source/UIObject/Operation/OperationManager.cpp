#include "OperationManager.h"
#include "../../GameObject/Item/ItemManager/ItemManager.h"
#include "../../GameObject/Light/LightColor.h"
#include <gslib.h>


OperationManager::OperationManager(ItemManager & itemManager)
	: m_State{ 0 }
	, p_ItemManager{ &itemManager }
	, m_IsMove{ true }
	, m_IsLightClear{ false }
{
}

void OperationManager::Initialize()
{
	m_State = 0;
	m_IsMove = true;
}

void OperationManager::Update(float deltaTime)
{
	TakeLight();
	LightChange();
	PutLight();
	TakeKey();
}

int OperationManager::GetCurrentState() const
{
	return m_State;
}

void OperationManager::SetCurrentState(OperationState state)
{
	m_State = (int)state;
}

bool OperationManager::IsPutLightClear() const
{
	return m_IsLightClear;
}

void OperationManager::SetPutLightClear(bool clear)
{
	m_IsLightClear = clear;
}

void OperationManager::TakeLight()
{
	if (m_State != (int)OperationState::TakeLight)return;

	if (p_ItemManager->GetLightSize(LightColor::Green) >= 1)
	{
		m_State = (int)OperationState::PlayerRotate;
		m_IsMove = false;
	}
}

void OperationManager::LightChange()
{
	if (m_State != (int)OperationState::LightChange)return;

	if (gsXBoxPadButtonTrigger(0, GS_XBOX_PAD_LEFT_SHOULDER) || gsXBoxPadButtonTrigger(0, GS_XBOX_PAD_RIGHT_SHOULDER))
	{
		m_State = (int)OperationState::PutLight;
		m_IsMove = false;
	}
}

void OperationManager::PutLight()
{
	if (m_State != (int)OperationState::PutLight)return;

	if (gsXBoxPadButtonTrigger(0, GS_XBOX_PAD_A))
	{
		m_State = (int)OperationState::TakeShiningLight;
		m_IsMove = false;
	}
}

void OperationManager::PlayerRotate()
{
	if (m_State != (int)OperationState::PlayerRotate)return;

	m_State = (int)OperationState::LightChange;

}

void OperationManager::TakeShiningLight()
{
	if (m_State != (int)OperationState::TakeShiningLight)return;

	{
		m_State = (int)OperationState::TakeBattery;
		m_IsMove = true;
	}
}

void OperationManager::TakeBattery()
{
	if (m_State != (int)OperationState::TakeBattery)return;

	{
		m_State = (int)OperationState::TakeKey;
		m_IsMove = true;
	}
}

void OperationManager::TakeKey()
{
	if (m_State != (int)OperationState::TakeKey)return;

	if (p_ItemManager->get_is_lock() == true)
	{
		m_State = (int)OperationState::NextRoom;
		m_IsMove = true;
	}
}

void OperationManager::EnemyStop()
{
	if (m_State != (int)OperationState::EnemyStop)return;

	{
		m_State = (int)OperationState::EnemyStopPutLight;
		m_IsMove = true;
	}
}

void OperationManager::EnemyStopPutLight()
{
	if (m_State != (int)OperationState::EnemyStopPutLight)return;

	{
		m_State = (int)OperationState::NextRoom;
		m_IsMove = true;
	}
}

void OperationManager::NormalDoor()
{
	if (m_State != (int)OperationState::NormalDoor)return;

	{
		m_State = (int)OperationState::LockDoor;
		m_IsMove = true;
	}
}

void OperationManager::LockDoor()
{
	if (m_State != (int)OperationState::LockDoor)return;

	{
		m_State = (int)OperationState::ColorDoor;
		m_IsMove = true;
	}
}

void OperationManager::ColorDoor()
{
	if (m_State != (int)OperationState::ColorDoor)return;

	{
		m_State = (int)OperationState::PutLightColorDoor;
		m_IsMove = true;
	}
}

void OperationManager::PutLightColorDoor()
{
	if (m_State != (int)OperationState::PutLightColorDoor)return;

	{
		m_State = (int)OperationState::OpenColorDoor;
		m_IsMove = true;
	}
}

void OperationManager::OpenColorDoor()
{
	//if (m_State != (int)OperationState::OpenColorDoor)return;

	{
		m_State = (int)OperationState::TutorialEnd;
		m_IsMove = true;
	}
}

bool OperationManager::IsMove()const
{
	return m_IsMove;
}
