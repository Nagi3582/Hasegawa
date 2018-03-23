#include "CollideLight.h"
#include"../../../Collide/SpotLight.h"
#include"../LightColor.h"
#include "../../Item/ItemManager/ItemManager.h"

CollideLight::CollideLight(IWorld & world
	, PlayerLight & light
	, LightColor color, ItemManager& item, std::string name)
	:CollideActor(world, name, GSvector3{ 0.0f,0.0f,0.0f }, new SpotLight(), color)
	, p_test_light{ &light }
	, m_With{ true }
	, p_ItemManager{ &item }
{}

CollideLight::CollideLight(IWorld & world, GSmatrix4 rotate, LightColor color, ItemManager& item, std::string name)
	:CollideActor(world, name, GSvector3{ 0.0f,0.0f,0.0f }, new SpotLight(), color)
	, p_test_light{ nullptr }
	, m_With{ false }
	, p_ItemManager{ &item }
{
	m_Position = rotate.getPosition() /*- rotate.getAxisZ().getNormalized()*/;
	m_Rotate = rotate;
}

CollideLight::~CollideLight()
{
}

void CollideLight::OnUpdate(float deltaTime)
{
	if (m_With == false)
	{
		return;
	}


	GSvector3 l_Position = p_test_light->get_position() /*- p_test_light->get_rotate().getAxisZ().getNormalized()*/;
	m_Position = l_Position;
	m_Rotate = p_test_light->get_rotate();


	if (p_ItemManager->BatterySize() <= 0)
	{
		p_Body->CollideOff();
	}
	else
	{
		p_Body->CollideOn();
	}
}

void CollideLight::OnDraw(bool is_shadow, Renderer& m_renderer) const
{}

void CollideLight::OnCollide(CollideActor & other)
{
	if (other.GetName() == "Enemy")
	{
		int a = 0;
	}
}

LightColor CollideLight::get_color() const
{
	return m_Color;
}

void CollideLight::set_color(LightColor color)
{
	m_Color = color;
}
