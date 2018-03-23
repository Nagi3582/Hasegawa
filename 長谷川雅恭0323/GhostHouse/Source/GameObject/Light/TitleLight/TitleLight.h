#ifndef TITLE_LIGHT_H_
#define TITLE_LIGHT_H_

#include<gslib.h>
#include"../LightParam/LightParams.h"

class Renderer;
class IWorld;

class TitleLight
{
public:
	TitleLight(GSvector3 position
		, Renderer& renderer
		, IWorld&world
		, float roll_x = 0.0f
		, float roll_y = 0.0f);
	void update(float deltaTime);
	void draw(Renderer&renderer)const;
protected:
	Renderer * p_renderer;
	GSvector3 m_position;
	GSvector3 m_light_direction;
	const GSfloat m_inner_angle;
	const GSfloat m_outer_angle;
	GSvector3 m_up;
	IWorld*p_world{ nullptr };
	GSmatrix4 m_rotate;
	LightParams* p_param;

	float roll_X;
	float roll_Y;
};

#endif