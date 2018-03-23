#include "TitleLight.h"
#include"../../../Utility/Renderer/Renderer.h"
#include"../../../World/IWorld.h"

TitleLight::TitleLight(GSvector3 position
	, Renderer & renderer
	, IWorld & world
	, float roll_x
	, float roll_y)
	:p_renderer{ &renderer }
	, p_world{ &world }
	, m_position{ position }
	, m_inner_angle{ 20 }
	, m_outer_angle{ 30 }
	, m_rotate{ GS_MATRIX4_IDENTITY }
	,roll_X{roll_x}
	,roll_Y{roll_y}
{
	m_rotate.setRotationX(roll_x);
	m_rotate.rotateY(roll_y);
	m_up = m_rotate.getAxisY();
	m_light_direction = m_rotate.getAxisZ();
	p_param = renderer.add_light();
}

void TitleLight::update(float deltaTime)
{
}

void TitleLight::draw(Renderer & renderer) const
{
	p_param->set_param(m_position
		, m_light_direction
		, m_up
		, GScolor{ 1.0f,1.0f,1.0f,1.0f }
		, m_inner_angle
		, m_outer_angle
		, 100.0f);

}
