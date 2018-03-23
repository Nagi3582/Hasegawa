#include "DoorBase.h"
#include"../../Utility/Renderer/ShaderName/ShaderName.h"
#include"../../Utility/Renderer/Renderer.h"
#include "../../Utility/Asset/MeshName.h"
#include "../../World/IWorld.h"
#include "../../Actor/ActorGroup.h"
#include "DoorGoalCollide/DoorGoalCollide.h"
#include "../../Scene/SceneType/SceneType.h"


DoorBase::DoorBase(IWorld & world
	, std::string name
	, GSvector3 position
	, Shape * shape
	, GSuint meshName
	, SceneInfo & info
	, SceneType type
	, float default_roll)
	: CollideActor(world, name, position, shape)
	, m_Info(info)
	, m_Type{ type }
	, m_meshName{ meshName }
	, m_state{ DoorState::Close }
	, m_opening_timer{ 0.0f }
	, m_IsNextScene{ true }
	, p_OperationManager{ nullptr }
{
	m_Rotate.identity();
	m_Rotate.rotateY(default_roll);
}

DoorBase::DoorBase(IWorld & world, std::string name, GSvector3 position, Shape * shape, GSuint meshName,
	SceneInfo & info, SceneType type, OperationManager & operationManager, float default_roll)
	: CollideActor(world, name, position, shape)
	, m_Info(info)
	, m_Type{ type }
	, m_meshName{ meshName }
	, m_state{ DoorState::Close }
	, m_opening_timer{ 0.0f }
	, m_IsNextScene{ false }
	, p_OperationManager{ &operationManager }
{
	m_Rotate.identity();
	m_Rotate.rotateY(default_roll);
}

void DoorBase::OnUpdate(float deltaTime)
{
	update_state(deltaTime);
	DoorUpdate(deltaTime);
}

void DoorBase::DoorUpdate(float deltaTime) {}

void DoorBase::update_state(float deltaTime)
{
	switch (m_state)
	{
	case DoorState::Close:
		update_close(deltaTime);
		break;

	case DoorState::Opening:
		update_opening(deltaTime);
		break;

	case DoorState::Open:
		update_open(deltaTime);
		break;
	}
}

void DoorBase::update_close(float deltaTime)
{
	if (is_open)
		m_state = DoorState::Opening;

}

void DoorBase::update_opening(float deltaTime)
{
	m_opening_timer += 0.02f * deltaTime;
	if (m_opening_timer > 1.0)
	{
		m_opening_timer = 1.0f;
		m_state = DoorState::Open;
		const GSvector3 l_Position = m_Position + GSvector3(-2.5f, 0.0f, 0.0f);

		if (m_IsNextScene == true)
		{
			p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<DoorGoalCollide>(*p_World, l_Position, m_Info, m_Type));
		}
	}
	m_Rotate.rotate(LERP(m_opening_timer, 0.0f, 12.5f), m_Rotate.getAxisY());

}

void DoorBase::update_open(float deltaTime)
{
}

void DoorBase::OnDraw(bool is_shadow, Renderer& m_renderer) const
{
	m_renderer.set_world(GetPose());

	m_renderer.draw_manager(is_shadow
		, m_meshName
		, (GSuint)ShaderName::Standerd
		, (GSuint)ShaderName::Depth);

	//p_Body->Transform(GetPose())->Draw();
	on_draw(is_shadow, m_renderer);
}
