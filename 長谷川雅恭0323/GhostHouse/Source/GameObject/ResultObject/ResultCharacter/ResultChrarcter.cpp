#include "ResultChrarcter.h"
#include"../../../Utility/Renderer/Renderer.h"
#include"../../../Utility/Asset/MeshName.h"
#include"../../../Utility/Renderer/ShaderName/ShaderName.h"
#include "../../../Collide/BoundingSphere.h"

ResultCharacter::ResultCharacter(IWorld & world, GSvector3 position, Renderer&renderer)
	: CollideActor{ world, "Player", position , new BoundingSphere(GSvector3(0.0f, 0.0f, 0.0f), 2.0f) }
	, p_Renderer{ &renderer }
{
	m_Position.y += 1.5f;
	m_Rotate.rotateY(90);
}

void ResultCharacter::OnUpdate(float deltaTime)
{
}

void ResultCharacter::OnDraw(bool is_shadow, Renderer & renderer) const
{
	if (is_shadow)return;
	GSmatrix4 pose = GSmatrix4(m_Rotate).setPosition(m_Position);

	renderer.set_world(pose);
	renderer.draw_manager(is_shadow
		, (GSuint)MeshName::ResultPlayer
		, (GSuint)ShaderName::Result
		, (GSuint)ShaderName::Depth);
}
