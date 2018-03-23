#include "RePopFlashLight.h"
#include "../../../Utility/Renderer/Renderer.h"
#include"../../../Collide/BoundingSphere.h"
#include "../../../Utility/Renderer/ShaderName/ShaderName.h"
#include "../ItemManager/ItemManager.h"
#include "../../Light/LightColor.h"
#include "../../../Utility/Asset/SoundName.h"
#include "../../../Utility/Asset/TextureName.h"

RePopFlashLight::RePopFlashLight(IWorld & world, GSvector3 position, LightColor color, ItemManager & item, int popTime)
	:CollideActor(world, "Item", position, new BoundingSphere(GSvector3(0.0f, 0.0f, 0.0f), 2.0f))
	, m_Counter{ 0 }
	, m_Battery{ 100 }
	, p_Manager{ &item }
	, m_Color{ color }
	, m_MeshID{ 0 }
	, m_is_get{ false }
	, m_re_pop_timer{ 0.0f }
	, m_Texture{ TextureName::ItemTakeWhiteLight }
	, m_PopTime{ popTime }
{
	SetMeshName();
	m_Position.y += 0.3f;
	m_Rotate.rotateY(-90);
}

void RePopFlashLight::OnUpdate(float deltaTime)
{
	if (!m_is_get)return;
	m_re_pop_timer -= deltaTime;
	if (m_re_pop_timer <= 0)
	{
		m_is_get = false;
	}
}

void RePopFlashLight::OnCollide(CollideActor & other)
{
	if (other.GetName() == "Player"
		&&!m_is_get)
	{
		p_Manager->AddLight(m_Color);
		if (p_Manager->GetLightSize(p_Manager->GetColor()) <= 0)
		{
			p_Manager->ChangeColor(true);
		}

		p_Manager->TakeItem(m_Texture);
		m_is_get = true;
		m_re_pop_timer = m_PopTime;
		gsPlaySE((GSuint)SoundName::GetItemSE);
	}

}

void RePopFlashLight::OnDraw(bool is_shadow, Renderer & renderer) const
{
	if (m_is_get)return;
	renderer.set_world(GetPose());
	renderer.draw_manager(is_shadow
		, (GSuint)m_MeshID
		, (GSuint)ShaderName::Standerd
		, (GSuint)ShaderName::Depth);

}

void RePopFlashLight::SetMeshName()
{
	switch (m_Color)
	{
	case LightColor::White:
		m_MeshID = (int)MeshName::WhiteFlashlight;
		m_Texture = TextureName::ItemTakeWhiteLight;
		break;
	case LightColor::Red:
		m_MeshID = (int)MeshName::RedFlashlight;
		m_Texture = TextureName::ItemTakeRedLight;
		break;
	case LightColor::Green:
		m_MeshID = (int)MeshName::GreenFlashlight;
		m_Texture = TextureName::ItemTakeGreenLight;
		break;
	case LightColor::Blue:
		m_MeshID = (int)MeshName::BlueFlashlight;
		m_Texture = TextureName::ItemTakeBlueLight;
		break;
	}

}
