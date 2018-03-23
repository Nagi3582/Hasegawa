#ifndef COLOR_ENEMY_H_
#define COLOR_ENEMY_H_

#include "../../ModelBase.h"
#include "../EnemyState/EnemyStateName.h"
#include"../../../Light/CollideLight/CollideLight.h"
#include"../../../Light/LightColor.h"
#include<vector>

class CollideLight;

class ColorEnemy :public ModelBase
{
public:
	ColorEnemy(IWorld & world
		, CollideActor& player
		,GSuint mesh
		,int color_num
		, LightColor my_color1
		, LightColor my_color= LightColor::White);

	virtual void OnUpdate(float deltaTime)override;

	virtual void SubDraw(bool is_shadow, Renderer& m_renderer)const override;

	virtual void OnCollide(CollideActor& other)override;

private:
	void checkLight(CollideLight light);
	bool is_hit_color()const;
	void move_re_start();
private:
	CollideActor* p_Player;
	EnemyStateName m_State; //âºÇÃìGÇÃèÛë‘
	int m_Hp;
	GSuint m_mesh;
	std::vector<bool>m_is_hit_color;
	std::vector<float>m_color_timer;
	std::vector<LightColor>m_my_color;
};


#endif // !COLOR_ENEMY_H_