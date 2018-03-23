#include "Collider.h"
#include "../BoundingSphere.h"
#include "../../Utility/Math/Math.h"
#include"../SpotLight.h"

bool Collider::SphereAndSphere(const BoundingSphere& s1, const BoundingSphere& s2)
{
	float l_Distance = Math::Distance(s1.m_Center, s2.m_Center);
	float l_Radius = s1.m_Radius + s2.m_Radius;

	if (l_Distance <= l_Radius)
		return true;

	return false;
}
bool Collider::SphereAndLight(const BoundingSphere & s, const SpotLight & l)
{
	float l_distance = l.m_Center.distance(s.m_Center);
	float l_angle = l.m_direction.innerDegree(s.m_Center - l.m_Center);
	if (l_distance > l.m_hit_distance)
		return false;
	if (l_angle > l.m_angle)
		return false;

	return true;
}
