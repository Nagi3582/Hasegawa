#include "Smoke.h"
#include "../../../Scene/SceneInfo/SceneInfo.h"
#include "../../../Utility/Renderer/Renderer.h"
#include "../../../Utility/Asset/MeshName.h"
#include "../../../Utility/Renderer/ShaderName/ShaderName.h"

Smoke::Smoke(IWorld & world, const GSvector3 & position, Camera& camera, SceneInfo& info)
	: m_Timer{ 0 }
	, m_Info{ info }
	, p_Camera{ &camera }
{
}

void Smoke::OnUpdate(float deltaTime)
{
	if (m_Timer >= 60 * 4)
	{
		Dead();
		m_Info.m_Direction = false;
	}

	m_Timer += deltaTime;
}

void Smoke::OnDraw(bool is_shadow, Renderer & renderer) const
{
	renderer.set_world(GetPose());
	renderer.draw_manager(is_shadow
		, (GSuint)MeshName::Smoke
		, (GSuint)ShaderName::Standerd
		, (GSuint)ShaderName::Depth);

}
