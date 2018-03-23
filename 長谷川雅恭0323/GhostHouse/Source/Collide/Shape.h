#ifndef _SHAPE_H_
#define _SHAPE_H_
#include <gslib.h>

class BoundingSphere;
class SpotLight;

class Shape
{
public:
	Shape(const GSvector3 center, const bool isCollide)
		: m_Center{ center }
		, m_IsCollide(isCollide)
		, p_Transform{ nullptr }
	{};

	virtual ~Shape()
	{
		delete p_Transform;
	}

	virtual void SetUp()
	{
		p_Transform = new Shape(m_Center, m_IsCollide);
	}

	//À•W•ÏŠ·
	virtual Shape* Transform(const GSmatrix4& matrix) { return p_Transform; }

	//•½sˆÚ“®
	virtual Shape* Translate(const GSvector3& position) { return p_Transform; }

	//Œğ·‚µ‚Ä‚¢‚é‚©
	virtual bool Intersect(Shape& other) { return false; };
	virtual bool Intersect(BoundingSphere& other) { return false; };
	virtual bool Intersect(SpotLight&other) { return false; };

	virtual void Draw()const {};

	bool IsCollide()const { return m_IsCollide; };

	void CollideOn() { m_IsCollide = true; }

	void CollideOff() { m_IsCollide = false; }

	void SetCollide(const bool collide) { m_IsCollide = collide; }


public:
	GSvector3 m_Center{ 0.0f,0.0f,0.0f };
	bool m_IsCollide;	//“–‚½‚è”»’è‚·‚é‚©
	Shape* p_Transform;

};

#endif // !_SHAPE_H_
