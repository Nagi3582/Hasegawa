#include "TitleDoorLight.h"
#include"../../../Utility/Renderer/Renderer.h"
#include"../../../World/IWorld.h"

TitleDoorLight::TitleDoorLight(GSvector3 position
	, Renderer & renderer
	, IWorld & world)
	:p_renderer{ &renderer }
	, p_world{ &world }
	, m_position{ position }
	, m_inner_angle{ 20 }
	, m_outer_angle{ 30 }
	, m_rotate{ GS_MATRIX4_IDENTITY }
	, m_up{ GSvector3{0,1,0} }
{
	p_param = renderer.add_light();
}

void TitleDoorLight::initalize(const GSvector3 position
	, Renderer & renderer
	, IWorld & world)
{
	p_renderer = &renderer;
	p_world = &world;
	m_position = position;
	m_rotate = GS_MATRIX4_IDENTITY;
	m_up = GSvector3{ 0,1,0 };
	p_param = renderer.add_light();
}

void TitleDoorLight::update(float deltaTime)
{
}

void TitleDoorLight::draw(Renderer&renderer) const
{
	p_param->set_param(m_position
		, GSvector3{ 0,0,1 }
		, m_up
		, GScolor{ 1.0f,1.0f,1.0f,1.0f }
		, m_inner_angle
		, m_outer_angle
		, 100.0f);
	//renderer.set_light_param(m_position
	//	, GSvector3{ 0,0,1 }
	//	, m_up
	//	, GScolor{ 1.0f,1.0f,1.0f,1.0f }
	//	, m_inner_angle
	//	, m_outer_angle
	//	, m_param.get_ID());
}

/**********デバック用**********/
LightParams TitleDoorLight::get_param_at_debug() const
{
	return *p_param;
}

//int TitleDoorLight::get_ID() const
//{
//	return p_renderer->get
//}
/******************************/