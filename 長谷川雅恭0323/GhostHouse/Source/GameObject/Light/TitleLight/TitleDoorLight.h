#ifndef TITLE_DOOR_LIGHT_H_
#define TITLE_DOOR_LIGHT_H_

#include<gslib.h>
#include"../LightParam/LightParams.h"

class Renderer;
class IWorld;

class TitleDoorLight
{
public:
	TitleDoorLight( GSvector3 position
		, Renderer& renderer
		, IWorld&world);
	void initalize(const GSvector3 position
		, Renderer& renderer
		, IWorld&world);
	void update(float deltaTime);
	void draw(Renderer&renderer)const;

	LightParams get_param_at_debug()const;
private:
	Renderer*p_renderer;
	GSvector3 m_position;
	const GSvector3 m_light_direction;
	const GSfloat m_inner_angle;
	const GSfloat m_outer_angle;
	GSvector3 m_up;
	IWorld*p_world{ nullptr };
	GSmatrix4 m_rotate;
	LightParams* p_param;
};

#endif // !TITLE_DOOR_LIGHT_H_
