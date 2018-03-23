#ifndef LIGHT_PARAM_H_
#define LIGHT_PARAM_H_

#include<gslib.h>

class LightParams
{
private:
	GSvector3 m_light_pos;
	GSvector3 m_light_direc;
	GSvector3 m_light_up;
	GScolor m_light_color;
	float m_light_cos_inner_angle;
	float m_light_cos_outer_angle;
	float m_lenge;
	float m_area_lenge;
	float m_area_power;
	bool is_delete;
	int m_ID;
public:
	void initialize()
	{
		is_delete = false;
	}
	void delete_light()
	{
		is_delete = true;
	}
	int get_ID()const
	{
		return m_ID;
	}
	void set_ID(int ID)
	{
		m_ID = ID;
	}
	bool get_is_delete()const
	{
		return is_delete;
	}
	void set_param(GSvector3 pos
		, GSvector3 direc
		, GSvector3 up
		, GScolor color
		, float inner_angle
		, float outer_angle
		, float lenge = 40.0f
		, float area_leng = 3.0f
		, float area_power = 1.0f)
	{
		m_light_pos = pos;
		m_light_direc = direc;
		m_light_up = up;
		m_light_color = color;
		m_light_cos_inner_angle = inner_angle;
		m_light_cos_outer_angle = outer_angle;
		m_lenge = lenge;
		m_area_lenge = area_leng;
		m_area_power = area_power;
	}

	GSvector3 get_light_pos()const
	{
		return m_light_pos;
	}

	GSvector3 get_light_direc()const
	{
		return m_light_direc;
	}
	GSvector3 get_light_up()const
	{
		return m_light_up;
	}
	GScolor get_light_color()const
	{
		return m_light_color;
	}
	float get_light_cos_inner_angle()const
	{
		return m_light_cos_inner_angle;
	}
	float get_light_cos_outer_angle()const
	{
		return m_light_cos_outer_angle;
	}
	float get_lenge()const
	{
		return m_lenge;
	}
	float get_area_lenge()const
	{
		return m_area_lenge;
	}
	float get_area_power()const
	{
		return m_area_power;
	}
};

#endif // !LIGHT_PARAM_H_