#include "OperationUI.h"
#include <gslib.h>
#include "../../Base/Screen.h"
#include "../../Utility/Asset/TextureName.h"
#include "OperationManager.h"

#include <iostream>

OperationUI::OperationUI()
	: p_OperationManager{ nullptr }
	, m_Texture{ TextureName::TakeLight }
	, m_PrevTexture{ TextureName::TutorialEnd }
	, m_Alpha{ 0.0f }
	, m_IsOperation{ false }
	, m_OperateTexture{ TextureName::BatteryOperation }
{
}

void OperationUI::SetUp(OperationManager & operationManager)
{
	p_OperationManager = &operationManager;
}


void OperationUI::Update(float deltaTime)
{
	SetTexture();
	if (m_Texture != m_PrevTexture)
	{
		m_PrevTexture = m_Texture;
		m_Alpha = 0.0f;
	}

	m_Alpha += 0.008f * deltaTime;

	if (m_Alpha >= 0.7f)m_Alpha = 0.8f;
}

void OperationUI::Draw() const
{
	{
		const GSrect l_Rect(0.0f, 0.0f, 530.0f, 200.0f);
		const GSvector2 l_Center(530 / 2, 200 / 2);
		gsDrawSprite2D((int)TextureName::OperationCharBack, &GSvector2(WIDTH - 150.0f, 50.0f), &l_Rect, &l_Center, NULL, NULL, 0.0f);

		const GSvector2 l_CharCenter(500 / 2, 150 / 2);
		GScolor l_Color(1.0f, 1.0f, 1.0f, m_Alpha);
		const float l_Scale = 0.8f;
		gsDrawSprite2D((int)m_Texture, &GSvector2(WIDTH - 200.0f, 70.0f), NULL, &l_CharCenter, &l_Color, &GSvector2(l_Scale, l_Scale), 0.0f);
	}

	if (m_IsOperation == true)
	{
		const GSrect l_Rect(0.0f, 0.0f, 530.0f, 200.0f);
		const GSvector2 l_Center(530 / 2, 200 / 2);
		const float l_ScaleX = 0.8f;
		const float l_ScaleY = 0.4f;

		gsDrawSprite2D((int)TextureName::OperationCharBack, &GSvector2(WIDTH - 70.0f, 190.0f), &l_Rect, &l_Center, NULL, &GSvector2(l_ScaleX, l_ScaleY), 0.0f);

		const GSvector2 l_OperationCenter(500 / 2, 150 / 2);
		GScolor l_OperationColor(1.0f, 1.0f, 1.0f, m_Alpha);
		const float l_OperationScale = 0.5f;
		gsDrawSprite2D((int)m_OperateTexture, &GSvector2(WIDTH - 135.0f, 190.0f), NULL, &l_OperationCenter,
			&l_OperationColor, &GSvector2(l_OperationScale, l_OperationScale), 0.0f);
	}
}

void OperationUI::SetTexture()
{
	if (p_OperationManager->GetCurrentState() == (int)OperationState::TakeLight)
	{
		m_Texture = TextureName::TakeLight;
		m_IsOperation = true;
		m_OperateTexture = TextureName::TakeLightOperation;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::PlayerRotate)
	{
		m_Texture = TextureName::ColorDoorPutLightOperation;
		m_IsOperation = false;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::LightChange)
	{
		m_Texture = TextureName::ChangeLight;
		m_IsOperation = false;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::PutLight)
	{
		m_Texture = TextureName::PutLight;
		m_IsOperation = false;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::TakeShiningLight)
	{
		m_Texture = TextureName::TakeShiningLight;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::TakeBattery)
	{
		m_Texture = TextureName::TakeBattery;
		m_IsOperation = true;
		m_OperateTexture = TextureName::BatteryOperation;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::TakeKey)
	{
		m_Texture = TextureName::TakeKey;
		m_IsOperation = true;
		m_OperateTexture = TextureName::TakeKeyOperate;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::EnemyStop)
	{
		m_Texture = TextureName::EnemyStop;
		m_IsOperation = true;
		m_OperateTexture = TextureName::EnemyStopOperation;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::EnemyStopPutLight)
	{
		m_Texture = TextureName::EnemyStopPutLight;
		m_IsOperation = true;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::NormalDoor)
	{
		m_Texture = TextureName::OpenNormalDoor;
		m_IsOperation = true;
		m_OperateTexture = TextureName::NormalDoorOperation;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::LockDoor)
	{
		m_Texture = TextureName::OpenLockDoor;
		m_IsOperation = false;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::ColorDoor)
	{
		m_Texture = TextureName::OpenColorDoor;
		m_IsOperation = true;
		m_OperateTexture = TextureName::ColorDoorOperate;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::PutLightColorDoor)
	{
		m_Texture = TextureName::ColorDoorPutLight;
		m_IsOperation = false;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::OpenColorDoor)
	{
		m_Texture = TextureName::ColorDoorOperate2;
		m_IsOperation = false;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::NextRoom)
	{
		m_Texture = TextureName::NextRoom;
		m_IsOperation = false;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::TutorialEnd)
	{
		m_Texture = TextureName::TutorialEnd;
		m_IsOperation = false;
	}

}
