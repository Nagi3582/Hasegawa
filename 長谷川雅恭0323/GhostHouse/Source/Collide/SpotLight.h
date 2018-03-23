#ifndef SPOT_LIGHT_H_
#define SPOT_LIGHT_H_
#include"Shape.h"
#include"Collider\Collider.h"

class SpotLight :public Shape
{
public:
	SpotLight()
		:Shape(GSvector3{ 0.0f,0.0f,0.0f }, true)
		, m_direction{ 0.0f,0.0f,0.0f }
		, m_angle{ 30.0f }
		, m_hit_distance{ 30.0f }
		, p_Transform{ nullptr }
	{}
	SpotLight(bool isCollide)
		:Shape(GSvector3{ 0.0f,0.0f,0.0f }, isCollide)
		, m_direction{ 0.0f,0.0f,0.0f }
		, m_angle{ 30.0f }
		, m_hit_distance{ 30.0f }
		, p_Transform{ nullptr }
	{}
	~SpotLight()
	{
		delete p_Transform;
	}
	virtual void SetUp()override
	{
		p_Transform = new SpotLight(m_IsCollide);
	}
	virtual Shape*Transform(const GSmatrix4& matrix)override
	{
		p_Transform->m_Center = matrix.transform(m_Center);
		p_Transform->m_direction = matrix.getAxisZ();
		p_Transform->m_IsCollide = m_IsCollide;
		return p_Transform;
	}
	virtual Shape* Translate(const GSvector3& position)override
	{
		p_Transform->m_Center = m_Center + position;
		p_Transform->m_IsCollide = m_IsCollide;
		return p_Transform;
	}
	//Œğ·‚µ‚Ä‚¢‚é‚©
	virtual bool Intersect(Shape& other) override { return other.Intersect(*this); };
	virtual bool Intersect(BoundingSphere& other)override { return Collider::SphereAndLight(other, *this); }

public:
	GSvector3 m_direction;
	float m_angle;
	float m_hit_distance;
	SpotLight*p_Transform;
};

#endif // !SPOT_LIGHT_H_