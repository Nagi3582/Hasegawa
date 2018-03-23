#ifndef PLAYER_LIGHT_H_
#define PLAYER_LIGHT_H_

#include<gslib.h>
#include "../../Actor/CollideActor.h"
#include"../Light/LightParam/LightParams.h"

class Renderer;
class Player;
class IWorld;
class ItemManager;
class CollideLight;

class PlayerLight
{
private:
	enum Light_Color
	{
		defult = 0,
		brue = 1,
		red = 2,
		green = 3
	};

public:
	PlayerLight(const CollideActor*actor, Renderer& renderer, IWorld&world, ItemManager& item);
	void update(float deltaTime);
	void draw(Renderer& renderer)const;
	void set_light_color(GScolor color);
	GSmatrix4 get_pose()const;
	GSmatrix4 get_rotate()const;
	GSvector3 get_position()const;
	void set_light_param();

private:
	void ChangeColor();
	void collide_light_to_enemy();
private:
	Renderer*p_renderer;
	const CollideActor* p_actor;
	GSvector3 m_position;
	GSvector3 m_light_direction;
	GSfloat m_inner_angle;
	GSfloat m_outer_angle;
	GSfloat m_exponent;
	GScolor m_light_color;
	GSvector3 m_up;
	int m_lisht_on;
	Light_Color m_color;
	int lightID;
	IWorld* p_world{ nullptr };
	GSmatrix4 m_rotate;
	ItemManager*p_item;
	CollideLight* p_CollideLight;
	LightParams *p_param;
};

#endif // !TEST_LIGHT_H_