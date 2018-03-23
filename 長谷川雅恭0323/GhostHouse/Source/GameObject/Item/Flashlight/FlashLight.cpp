#include "FlashLight.h"
#include "../../../Utility/Renderer/Renderer.h"
#include"../../../Collide/BoundingSphere.h"
#include "../../../Utility/Renderer/ShaderName/ShaderName.h"
#include "../ItemManager/ItemManager.h"
#include "../../Light/LightColor.h"
#include "../../../Utility/Asset/SoundName.h"
#include "../../../Utility/Asset/TextureName.h"
#include "LightParameter.h"


Flashlight::Flashlight(IWorld & world, GSvector3 position, LightColor color, ItemManager& item, int batterySize)
	:CollideActor{ world ,"Item",position,new BoundingSphere(GSvector3(0.0f, 0.0f, 0.0f),2.0f) }
	, m_Counter{ 0 }
	, m_Battery{ 100 }
	, p_Manager{ &item }
	, m_Color{ color }
	, m_MeshID{ 0 }
	, m_Texture{ TextureName::ItemTakeWhiteLight }
	, p_Light{ new LightParameter(color,batterySize) }
{
	SetMeshName();
	m_Position.y += 0.6f;
	m_Rotate.rotateY(-90);
}

void Flashlight::OnUpdate(float deltaTime)
{
	/*if (m_Get_Battery_Flag)
	{
		m_Battery += 50;
	}

	if (m_Counter / 60 == 0)
	{
		m_Battery--;

		if (m_Battery == 0)
		{
			m_Light_Flag = false;
		}
		else
		{
			m_Light_Flag = true;
		}
	}

	m_Counter++;
*/
}

void Flashlight::OnCollide(CollideActor & other)
{
	if (other.GetName() == "Player")
	{
		p_Manager->AddLight(p_Light->GetColor(), p_Light->BatterySize());
		if (p_Manager->GetLightSize(p_Manager->GetColor()) <= 0)
		{
			p_Manager->ChangeColor(true);
		}

		p_Manager->TakeItem(m_Texture);
		Dead();
		gsPlaySE((GSuint)SoundName::GetItemSE);
	}
}

void Flashlight::OnDraw(bool is_shadow, Renderer & renderer) const
{
	renderer.set_world(GetPose());
	renderer.draw_manager(is_shadow
		, (GSuint)m_MeshID
		, (GSuint)ShaderName::Standerd
		, (GSuint)ShaderName::Depth);
}

void Flashlight::SetMeshName()
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
