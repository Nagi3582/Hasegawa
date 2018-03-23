#include "EnemyBase.h"
#include "../../../Collide/BoundingSphere.h"
#include "../../../Utility/Renderer/Renderer.h"
#include "../../../Utility/Renderer/ShaderName/ShaderName.h"
#include "../../Light/CollideLight/CollideLight.h"
#include "../../../Utility/Asset/MeshName.h"

EnemyBase::EnemyBase(IWorld & world, MeshName mesh, LightColor color, GSvector3 position, CollideActor & player, Renderer& renderer)
	: ModelBase{ world,"Enemy",position,new BoundingSphere(GSvector3(0.0f,0.0f,0.0f),2.0f) }
	, m_Manager{ player,*this,world }
	, m_Mesh{ mesh }
	, m_Color{ color }
	, p_Renderer{ &renderer }
{}

void EnemyBase::OnUpdate(float deltaTime)
{
	m_Manager.Update(deltaTime);

	m_Rotate = m_Manager.GetRotate();
	m_Position = m_Manager.GetPosition();
	if (HitField(false))
	{
		m_Manager.SetPosition(m_Position);
	}

	p_Renderer->anm_chamge(m_Manager.GetMotionID(), m_AnmID);
	p_Renderer->anm_update(deltaTime, m_AnmID, GetPose());

}

void EnemyBase::SubDraw(bool is_shadow, Renderer & m_renderer) const
{
	m_renderer.set_world(GetPose());
	m_renderer.draw_manager(is_shadow
		, (GSuint)m_Mesh
		, (GSuint)ShaderName::Anmation
		, (GSuint)ShaderName::AnmDepth
		, true
		, 1
		, m_AnmID);

	//p_Body->Translate(m_Position)->Draw();
}

void EnemyBase::OnCollide(CollideActor & other)
{
	if (other.GetColor() == m_Color)
	{
		m_Manager.Collide(other);
	}
}