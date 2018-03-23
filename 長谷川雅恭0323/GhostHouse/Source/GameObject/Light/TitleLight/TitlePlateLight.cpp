#include "TitlePlateLight.h"

TitlePlateLight::TitlePlateLight(GSvector3 position
	, float roll_y
	, Renderer & renderer
	, IWorld & world)
	:p_renderer{ &renderer }
	, p_world{ &world }
	, m_position{ position }
	, m_inner_angle{ 20 }
	, m_outer_angle{ 30 }
	, m_rotate{ GS_MATRIX4_IDENTITY }
{
	m_rotate.setRotationX(45);
	m_rotate.setRotationY(roll_y);
	m_light_direction = m_rotate.getAxisZ();
}

void TitlePlateLight::initalize(const GSvector3 position, Renderer & renderer, IWorld & world)
{
}

void TitlePlateLight::update(float deltaTime)
{
}

void TitlePlateLight::draw(Renderer & renderer) const
{
}

LightParams TitlePlateLight::get_param_at_debug() const
{
	return LightParams();
}
