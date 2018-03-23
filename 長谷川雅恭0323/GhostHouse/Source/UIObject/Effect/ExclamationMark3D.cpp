#include "ExclamationMark3D.h"
#include "../../Actor/CollideActor.h"
#include "../../Utility/Asset/TextureName.h"
#include "../../Utility/Renderer/Renderer.h"
#include "../../Utility/Renderer/ShaderName/ShaderName.h"
#include "../../Utility/Asset/MeshName.h"


ExclamationMark3D::ExclamationMark3D(IWorld& world, CollideActor& enemy)
	: Actor{ world,"ExclamationMark",GSvector3(0.0f,0.0f,0.0f) }
	, p_Enemy{ &enemy }
{
}


void ExclamationMark3D::OnUpdate(float deltaTime)
{
	m_Position = p_Enemy->GetPosition() + GSvector3(0.0f, 6.0f, 0.0f);
}

void ExclamationMark3D::OnDraw(bool is_shadow, Renderer & renderer) const
{
	if (is_shadow)return;
	renderer.set_world(GetPose());
	renderer.draw_manager(is_shadow
		, (GSuint)MeshName::ExclamationMark
		, (GSuint)ShaderName::Icon
		, (GSuint)ShaderName::Depth);

}
