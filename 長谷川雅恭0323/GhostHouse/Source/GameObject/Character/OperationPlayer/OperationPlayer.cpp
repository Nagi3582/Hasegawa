#include "OperationPlayer.h"
#include "../../../Collide/BoundingSphere.h"
#include "../../../Utility/Asset/MeshName.h"
#include "../../../Utility/Asset/AnimationName.h"
#include "../../Light/PlayerLight.h"
#include"../../../Utility/Renderer/Renderer.h"
#include"../../../Utility/Renderer/ShaderName/ShaderName.h"

#include "../../../World/IWorld.h"
#include "../../../Actor/ActorGroup.h"

#include "../../../UIObject/Operation/OperationManager.h"

#include <iostream>

OperationPlayer::OperationPlayer(IWorld & world, const GSvector3 position, Renderer & renderer, ItemManager & item, SceneInfo & info, OperationManager& operationManager)
	: Player{ world, position, renderer,item,info ,true }
	, p_OperationManager{ &operationManager }
{
	m_Manager.SetUpOperation(renderer, operationManager);
}

void OperationPlayer::OnUpdate(float deltaTime)
{
	m_Manager.Update(deltaTime);

	m_Rotate = m_Manager.GetRotate();
	m_Rotate.rotateY(180.0f);
	m_Position += m_Manager.GetVelocity(deltaTime);

	MoveLimit();

	HitField();

	p_Renderer->anm_chamge(m_Manager.GetMotionID(), m_AnmID);

	p_Renderer->anm_update(deltaTime, m_AnmID, GetPose());
	m_player_light.update(deltaTime);

	m_HandLight.Update(p_Renderer->get_bone_matrices(m_AnmID, 7));

}

void OperationPlayer::MoveLimit()
{
	if (p_OperationManager->GetCurrentState() == (int)OperationState::TakeLight && m_Position.z >= -10)
	{
		m_Position.z = -10;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::TakeBattery && m_Position.z >= 13)
	{
		m_Position.z = 13;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::TakeKey && m_Position.z >= 30)
	{
		m_Position.z = 30;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::EnemyStop ||
		p_OperationManager->GetCurrentState() == (int)OperationState::EnemyStopPutLight)
	{
		if (m_Position.z >= 150)
			m_Position.z = 150;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::NormalDoor && m_Position.z >= 220)
	{
		m_Position.z = 220;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::LockDoor && m_Position.z >= 240)
	{
		m_Position.z = 240;
	}
	else if (p_OperationManager->GetCurrentState() == (int)OperationState::ColorDoor ||
		p_OperationManager->GetCurrentState() == (int)OperationState::PutLightColorDoor ||
		p_OperationManager->GetCurrentState() == (int)OperationState::OpenColorDoor)
	{
		if (m_Position.z >= 265)
			m_Position.z = 265;
	}

}

