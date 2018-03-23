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

	//���W�ϊ�
	virtual Shape* Transform(const GSmatrix4& matrix)override
	{
		p_Transform->m_Center = matrix.transform(m_Center);
		p_Transform->m_Radius = m_Radius*matrix.getScale().y;
		p_Transform->m_IsCollide = m_IsCollide;
		return p_Transform;
	}

	//���s�ړ�
	virtual Shape* Translate(const GSvector3& position)override
	{
		p_Transform->m_Center = m_Center + position;
		p_Transform->m_Radius = m_Radius;
		p_Transform->m_IsCollide = m_IsCollide;
		return p_Transform;
	};

	//�������Ă��邩
	virtual bool Intersect(Shape& other) override { return other.Intersect(*this); };
	virtual bool Intersect(BoundingSphere& sphere) override { return Collider::SphereAndSphere(*this, sphere); };
	virtual bool Intersect(SpotLight& other)override { return Collider::SphereAndLight(*this, other); }

	virtual void Draw()const override
	{
		if (m_IsCollide == false)
			return;

		glPushMatrix();
		glTranslatef(m_Center.x, m_Center.y, m_Center.z);
		glutWireSphere(m_Radius, 16, 16);//( ���̔��a, ���̕�����, �c�̕�����)
		glPopMatrix();
	}


public:
	float m_Radius;					// ���a
	BoundingSphere* p_Transform;	// �g�����X�t�H�[���p�̋���
};

#endif // !_BOUNDING_SPHERE_H_
