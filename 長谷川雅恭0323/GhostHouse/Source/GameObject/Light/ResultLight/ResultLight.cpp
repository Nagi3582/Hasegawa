#include "ResultLight.h"
#include"../../../Utility/Renderer/Renderer.h"
#include"../../../GameObject/ResultObject/ResultCharacter/ResultChrarcter.h"

#include "../../../Utility/Renderer/ShaderName/ShaderName.h"

ResultLight::ResultLight()
{
}

void ResultLight::initialize(Renderer & renderer)
{
	p_renderer = &renderer;
	p_LightParam= p_renderer->add_light();

	gsLoadShader((GSuint)ShaderName::Standerd, "Resource/Shader/Standerd.vert", "Resource/Shader/Standerd.frag");
	if (!gsLoadShader((GSuint)ShaderName::Anmation, "Resource/Shader/AnmShader.vert", "Resource/Shader/Standerd.frag"))throw;
	if (!gsLoadShader((GSuint)ShaderName::Floor, "Resource/Shader/Standerd_Texture.vert", "Resource/Shader/Floor.frag"))throw;
	if (!gsLoadShader((GSuint)ShaderName::Depth, "Resource/Shader/Shadow.vert", "Resource/Shader/Shadow.frag"))throw;

	at_wall_direction.getNormalized();
	m_light_up_timer = 90.0f;
	is_end = false;
	is_light_up = false;
}

void ResultLight::update(float deltaTime)
{
	m_light_up_timer -= deltaTime;
	if (m_light_up_timer > 0)return;
	is_light_up = true;
	if (gsXBoxPadButtonTrigger(0, GS_XBOX_PAD_A))
		is_end = true;
}

void ResultLight::draw(Renderer & renderer) const
{
	if (m_light_up_timer > 0)return;
	renderer.set_light_param(at_wall_position
		, at_wall_direction
		, m_up
		, m_lightColor
		, 22
		, 25
		, p_LightParam->get_ID());
}

bool ResultLight::get_end() const
{
	return is_end;
}

bool ResultLight::get_light_up() const
{
	return is_light_up;
}
