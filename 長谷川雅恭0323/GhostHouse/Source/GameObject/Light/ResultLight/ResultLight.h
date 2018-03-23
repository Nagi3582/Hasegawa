#ifndef RESULT_LIGHT_H_
#define RESULT_LIGHT_H_

#include<gslib.h>
#include "../LightParam/LightParams.h"

class ResultCharacter;
class Renderer;

class ResultLight
{
public:
	ResultLight();
	void initialize( Renderer&renderer);
	void update(float deltaTime);
	void draw(Renderer& renderer)const;
	bool get_end()const;
	bool get_light_up()const;
private:
	float m_light_up_timer;
	int at_wallID;
	GSvector3 at_wall_position{ 10.0f,10.0f,-5.0f };
	GSvector3 at_wall_direction{ 0.75f,0.0f,1.0f };

	GSvector3 m_up{ 0.0f,1.0f,0.0f };
	GScolor m_lightColor{ 1.0f,1.0f,1.0f,1.0f };

	Renderer* p_renderer;
	bool is_end;
	bool is_light_up;

	LightParams *p_LightParam;

};

#endif // !RESULT_LIGHT_H_