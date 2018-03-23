#ifndef _BOUNDING_SPHERE_H_
#define _BOUNDING_SPHERE_H_
#include "Shape.h"
#include "Collider/Collider.h"

class BoundingSphere :public Shape
{
public:
	BoundingSphere(const GSvector3& center, float radius)
		: Shape(center, true)
		, m_Radius(radius)
		, p_Transform(nullptr)
	{};

	BoundingSphere(const GSvector3& center, float radius, const bool isCollide)
		: Shape(center, isCollide)
		, m_Radius(radius)
		, p_Transform(nullptr)
	{};

	~BoundingSphere()
	{
		delete p_Transform;
	}

	virtual void SetUp()override
	{
		p_Transform = new BoundingSphere(m_Center, m_Radius, m_IsCollide);
	}

	//座標変換
	virtual Shape* Transform(const GSmatrix4& matrix)override
	{
		p_Transform->m_Center = matrix.transform(m_Center);
		p_Transform->m_Radius = m_Radius*matrix.getScale().y;
		p_Transform->m_IsCollide = m_IsCollide;
		return p_Transform;
	}

	//平行移動
	virtual Shape* Translate(const GSvector3& position)override
	{
		p_Transform->m_Center = m_Center + position;
		p_Transform->m_Radius = m_Radius;
		p_Transform->m_IsCollide = m_IsCollide;
		return p_Transform;
	};

	//交差しているか
	virtual bool Intersect(Shape& other) override { return other.Intersect(*this); };
	virtual bool Intersect(BoundingSphere& sphere) override { return Collider::SphereAndSphere(*this, sphere); };
	virtual bool Intersect(SpotLight& other)override { return Collider::SphereAndLight(*this, other); }

	virtual void Draw()const override
	{
		if (m_IsCollide == false)
			return;

		glPushMatrix();
		glTranslatef(m_Center.x, m_Center.y, m_Center.z);
		glutWireSphere(m_Radius, 16, 16);//( 球の半径, 横の分割数, 縦の分割数)
		glPopMatrix();
	}


public:
	float m_Radius;					// 半径
	BoundingSphere* p_Transform;	// トランスフォーム用の球体
};

#endif // !_BOUNDING_SPHERE_H_
