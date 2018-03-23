#include "ShiningLight.h"
#include "../../../Collide/BoundingSphere.h"
#include "../ItemManager/ItemManager.h"
#include "LightParameter.h"
#include "../../../Utility/Renderer/Renderer.h"
#include "../../../Utility/Renderer/ShaderName/ShaderName.h"
#include "../../Light/LightColor.h"
#include "../../../Utility/Asset/MeshName.h"
#include "../../Light/PlayerLight.h"

#include "../../../World/IWorld.h"
#include "../../../Actor/ActorGroup.h"
#include "../../Light/CollideLight/CollideLight.h"
#include "../../../Utility/Asset/TextureName.h"

#include "../../../UIObject/Operation/OperationManager.h"

ShiningLight::ShiningLight(IWorld & world, GSvector3 position, int batterySize, LightColor color,
	ItemManager & item, CollideActor& player, Renderer& renderer, bool is_UseBattery)
	: CollideActor{ world,"PutLight", position,new BoundingSphere(GSvector3(0.0f, 0.0f, 0.0f),3.0f) }
	, p_Light{ new LightParameter(color, batterySize) }
	, m_MeshID{ 0 }
	, m_Color{ color }
	, p_Renderer{ &renderer }
	, p_ItemManager{ &item }
	, m_LightColor{ 1.0f,1.0f,1.0f,1.0f }
	, p_CollideLight{ nullptr }
	, m_Texture{ TextureName::ItemTakeWhiteLight }
	, m_TimeUp{ false }
	, m_IsUseBattery{ is_UseBattery }
	, p_OperationManager{ nullptr }
{
	m_Rotate = player.GetRotate();
	CollideActorPtr l_CollideLight = std::make_shared<CollideLight>(world, GetPose(), color, item, "ShiningLight");
	world.AddCollideActor(ActorGroup::Light, l_CollideLight);
	p_CollideLight = dynamic_cast<CollideLight*>(l_CollideLight.get());
	SetMeshName();
	p_param = renderer.add_light();
	m_Position.y += 0.6f;
}

ShiningLight::ShiningLight(IWorld & world, GSvector3 position, int batterySize, LightColor color, ItemManager & item, CollideActor & player, Renderer & renderer, OperationManager & operationManager, bool is_UseBattery)
	: CollideActor{ world,"PutLight", position,new BoundingSphere(GSvector3(0.0f, 0.0f, 0.0f),3.0f) }
	, p_Light{ new LightParameter(color, batterySize) }
	, m_MeshID{ 0 }
	, m_Color{ color }
	, p_Renderer{ &renderer }
	, p_ItemManager{ &item }
	, m_LightColor{ 1.0f,1.0f,1.0f,1.0f }
	, p_CollideLight{ nullptr }
	, m_Texture{ TextureName::ItemTakeWhiteLight }
	, m_TimeUp{ false }
	, m_IsUseBattery{ is_UseBattery }
	, p_OperationManager{ &operationManager }
{
	m_Rotate = player.GetRotate();
	CollideActorPtr l_CollideLight = std::make_shared<CollideLight>(world, GetPose(), color, item, "ShiningLight");
	world.AddCollideActor(ActorGroup::Light, l_CollideLight);
	p_CollideLight = dynamic_cast<CollideLight*>(l_CollideLight.get());
	SetMeshName();
	p_param = renderer.add_light();
	m_Position.y += 0.6f;
}

ShiningLight::~ShiningLight()
{
	delete p_Light;
}

void ShiningLight::OnUpdate(float deltaTime)
{
	if (m_IsUseBattery == true)
		p_Light->Update(deltaTime);

	set_light_param();

	if (p_Light->BatterySize() <= 0)
	{
		p_Renderer->remove_light(p_param->get_ID());
		Dead();
		p_CollideLight->Dead();
		m_TimeUp = true;
	}
	if ((p_OperationManager != nullptr && p_OperationManager->IsPutLightClear()))
	{
		p_Renderer->remove_light(p_param->get_ID());
		Dead();
		p_CollideLight->Dead();
		m_TimeUp = true;
	}

}

void ShiningLight::OnCollide(CollideActor & other)
{
	if (other.GetName() == "Player" && IsDead() && m_TimeUp == false)
	{
		p_ItemManager->AddLight(p_Light->GetColor(), p_Light->BatterySize());
		if (p_ItemManager->GetLightSize(p_ItemManager->GetColor()) <= 0)
		{
			p_ItemManager->ChangeColor(true);
		}

		p_ItemManager->TakeItem(m_Texture);
		p_Renderer->remove_light(p_param->get_ID());
		Dead();
		p_CollideLight->Dead();
	}
}

void ShiningLight::OnDraw(bool is_shadow, Renderer & renderer) const
{
	if (is_shadow)return;

	p_Renderer->set_world(GetPose());
	p_Renderer->draw_manager(false, (GSuint)m_MeshID, (GSuint)ShaderName::Standerd, (GSuint)ShaderName::Depth);

}

void ShiningLight::SetMeshName()
{
	switch (m_Color)
	{
	case LightColor::White:
		m_MeshID = (int)MeshName::WhiteFlashlight;
		m_LightColor = GScolor{ 1.0f,1.0f,1.0f,1.0f };
		p_CollideLight->set_color(LightColor::White);
		m_Texture = TextureName::ItemTakeWhiteLight;
		break;
	case LightColor::Red:
		m_MeshID = (int)MeshName::RedFlashlight;
		m_LightColor = GScolor{ 1.0f,0.1f,0.1f,1.0f };
		p_CollideLight->set_color(LightColor::Red);
		m_Texture = TextureName::ItemTakeRedLight;
		break;
	case LightColor::Green:
		m_MeshID = (int)MeshName::GreenFlashlight;
		m_LightColor = GScolor{ 0.1f,1.0f,0.1f,1.0f };
		p_CollideLight->set_color(LightColor::Green);
		m_Texture = TextureName::ItemTakeGreenLight;
		break;
	case LightColor::Blue:
		m_MeshID = (int)MeshName::BlueFlashlight;
		m_LightColor = GScolor{ 0.1f,0.1f,1.0f,1.0f };
		p_CollideLight->set_color(LightColor::Blue);
		m_Texture = TextureName::ItemTakeBlueLight;
		break;
	}
}

void ShiningLight::set_light_param()
{
	const GSvector3 l_Position = m_Position + GSvector3(0.0f, 1.0f, 0.0f);

	if (p_Light->GetColor() == LightColor::None || p_Light->BatterySize() <= 0)
	{
		p_Renderer->set_light_param(l_Position
			, m_Rotate.getAxisZ()
			, m_Rotate.getAxisY()
			, GScolor{ 0.0f,0.0f,0.0f,0.0f }
			, 20.0f
			, 30.0f
			, p_param->get_ID());
	}
	else
	{
		p_Renderer->set_light_param(l_Position
			, m_Rotate.getAxisZ()
			, m_Rotate.getAxisY()
			, m_LightColor
			, 20.0f
			, 30.0f
			, p_param->get_ID());
	}

}
