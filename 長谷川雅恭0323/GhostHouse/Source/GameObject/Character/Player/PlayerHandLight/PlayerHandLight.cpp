#include "PlayerHandLight.h"
#include "../../../../Utility/Renderer/Renderer.h"
#include "../../../../Utility/Asset/MeshName.h"
#include "../../../../Utility/Renderer/ShaderName/ShaderName.h"
#include "../../../Item/ItemManager/ItemManager.h"
#include "../../../Light/LightColor.h"

PlayerHandLight::PlayerHandLight(CollideActor& player, ItemManager& item)
	: p_Player{ &player }
	, p_Item{ &item }
	, m_Mesh{ MeshName::WhiteFlashlight }
	, m_Rotate{ GS_MATRIX4_IDENTITY }
{
}

void PlayerHandLight::Update(const GSmatrix4 & rotate)
{
	SetMesh();
	m_Rotate = rotate;
	GSvector3 l_Position = m_Rotate.getPosition();
	l_Position += m_Rotate.getAxisZ().getNormalized() * 0.5f;
	l_Position.y += -0.6f;
	m_Rotate.setPosition(l_Position);
}

void PlayerHandLight::Draw(bool is_shadow, Renderer & renderer) const
{
	if (is_shadow == true)return;

	renderer.set_world(m_Rotate);
	renderer.draw_manager(is_shadow
		, (GSuint)m_Mesh
		, (GSuint)ShaderName::Standerd
		, (GSuint)ShaderName::Depth);

}

void PlayerHandLight::SetMesh()
{
	if (p_Item->GetColor() == LightColor::White)
		m_Mesh = MeshName::WhiteFlashlight;
	else if (p_Item->GetColor() == LightColor::Red)
		m_Mesh = MeshName::RedFlashlight;
	else if (p_Item->GetColor() == LightColor::Green)
		m_Mesh = MeshName::GreenFlashlight;
	else if (p_Item->GetColor() == LightColor::Blue)
		m_Mesh = MeshName::BlueFlashlight;
}
