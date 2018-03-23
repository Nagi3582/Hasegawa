#include "PlayerLight.h"
#include"../../Utility/Renderer/Renderer.h"
#include"../../Actor/CollideActorPtr.h"
#include"../../Actor/CollideActor.h"
#include"../Character/Player/Player.h"
#include"../../Actor/ActorGroup.h"
#include"../../World/IWorld.h"
#include"CollideLight\CollideLight.h"
#include"../../Actor/ActorGroup.h"
#include"../Light/LightColor.h"
#include"../Item/ItemManager/ItemManager.h"
#include "../Light/CollideLight/CollideLight.h"

PlayerLight::PlayerLight(const CollideActor * actor, Renderer&renderer, IWorld&world, ItemManager&item)
	:p_actor{ actor }
	, m_inner_angle{ 20 }
	, m_outer_angle{ 30 }
	, m_exponent{ 40 }
	, m_light_color{ 1.0f,1.0f,1.0f,1.0f }
	, m_lisht_on{ 1 }
	, m_color{ Light_Color::defult }
	, m_up{ GSvector3{ 0.0f,1.0f,0.0f } }
	, p_renderer{ &renderer }
	, p_world{ &world }
	, m_rotate{ GS_MATRIX4_IDENTITY }
	, p_item{ &item }
	, p_CollideLight{ nullptr }
{
	p_param = renderer.add_light();
	CollideActorPtr l_CollideLight = std::make_shared<CollideLight>(world, *this, item.GetColor(), item);
	p_world->AddCollideActor(ActorGroup::Light, l_CollideLight);
	p_CollideLight = dynamic_cast<CollideLight*>(l_CollideLight.get());
}

void PlayerLight::update(float deltaTime)
{
	//	m_light_direction = p_actor->GetRotate().getAxisZ();

	m_rotate = p_actor->GetRotate();

	m_position = p_actor->GetPosition() + 1.0f*m_rotate.getAxisZ();
	m_position.y += 2.0f;
	if (gsXBoxPadButtonTrigger(0, GS_XBOX_PAD_A))
		m_lisht_on *= -1;

	ChangeColor();


	collide_light_to_enemy();
	set_light_param();
}

void PlayerLight::draw(Renderer& renderer) const
{
	//if (p_item->GetColor() == LightColor::None || p_item->BatterySize() <= 0)
	//	renderer.set_light_param(m_position
	//		, m_rotate.getAxisZ()
	//		, m_up
	//		, GScolor{ 0.0f,0.0f,0.0f,0.0f }
	//		, m_inner_angle
	//		, m_outer_angle
	//		, p_param->get_ID());
	//else
	//	renderer.set_light_param(m_position
	//		, m_rotate.getAxisZ()
	//		, m_up
	//		, m_light_color
	//		, m_inner_angle
	//		, m_outer_angle
	//		, p_param->get_ID()
	//		, 40.0f
	//		, 10.0f);
}

void PlayerLight::set_light_color(GScolor color)
{
	m_light_color = color;
}

GSmatrix4 PlayerLight::get_pose() const
{
	return GSmatrix4(m_rotate).setPosition(m_position);
}

GSmatrix4 PlayerLight::get_rotate() const
{
	return m_rotate;
}

GSvector3 PlayerLight::get_position() const
{
	return m_position;
}

void PlayerLight::set_light_param()
{
	if (p_item->GetColor() == LightColor::None || p_item->BatterySize() <= 0)
		p_renderer->set_light_param(m_position
			, m_rotate.getAxisZ()
			, m_up
			, GScolor{ 0.0f,0.0f,0.0f,0.0f }
			, m_inner_angle
			, m_outer_angle
			, p_param->get_ID());
	else
		p_renderer->set_light_param(m_position
			, m_rotate.getAxisZ()
			, m_up
			, m_light_color
			, m_inner_angle
			, m_outer_angle
			, p_param->get_ID()
			, 40.0f
			, 10.0f);


}

void PlayerLight::ChangeColor()
{
	switch (p_item->GetColor())
	{
	case LightColor::White:
		m_light_color = GScolor{ 1.0f,1.0f,1.0f,1.0f };
		p_CollideLight->set_color(LightColor::White);
		break;

	case LightColor::Blue:
		m_light_color = GScolor{ 0.3f,0.3f,1.0f,1.0f };
		p_CollideLight->set_color(LightColor::Blue);
		break;

	case LightColor::Red:
		m_light_color = GScolor{ 1.0f,0.3f,0.3f,1.0f };
		p_CollideLight->set_color(LightColor::Red);
		break;

	case LightColor::Green:
		m_light_color = GScolor{ 0.3f,1.0f,0.3f,1.0f };
		p_CollideLight->set_color(LightColor::Green);
		break;
	}
}

void PlayerLight::collide_light_to_enemy()
{
}