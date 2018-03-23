#include "ModelBase.h"
#include "../../World/IWorld.h"
#include "../Field/Field.h"
#include "../../Collide/BoundingSphere.h"
#include "../../Utility/Renderer/Renderer.h"
#include "../../Utility/Asset/MeshName.h"

ModelBase::ModelBase(IWorld & world, std::string name, GSvector3 position, Shape * shape)
	: CollideActor{ world, name, position, shape }
	, m_Velocity{ 0.0f, 0.0f, 0.0f }
	, m_Speed{ 0.0f }
	, m_AnmID{ 0 }
	, m_Mesh{}
{
}

void ModelBase::OnDraw(bool is_shadow, Renderer& renderer) const
{
	//GSmatrix4 pose;
	//pose.identity();
	//renderer.set_world(pose);

	//renderer.draw_mesh((GSuint)m_Mesh, (GSuint)ShaderName::Anmation, true, 1, m_AnmID);

	SubDraw(is_shadow, renderer);
}

bool ModelBase::HitField(bool isHit)
{
	GSvector3 l_Intersect;
	BoundingSphere& l_Body = dynamic_cast<BoundingSphere&>(*p_Body->Transform(GetPose()));
	if (p_World->GetField()->IsCollide(l_Body, &l_Intersect, isHit))
	{
		m_Position.x = l_Intersect.x;
		m_Position.z = l_Intersect.z;
		return true;
	}
	return false;
}

void ModelBase::SetAnimation(Renderer & renderer, MeshName mesh, int motionID)
{
	m_Mesh = mesh;
	renderer.add_anm((GSuint)m_Mesh, (GSuint)m_Mesh, (GSuint)m_Mesh, motionID, m_AnmID);
}
