#ifndef _COLLIDER_H_
#define _COLLIDER_H_

class BoundingSphere;
class SpotLight;

class Collider
{
public:
	static bool SphereAndSphere(const BoundingSphere& s1, const BoundingSphere& s2);
	static bool SphereAndLight(const BoundingSphere&s, const SpotLight&l);
};

#endif // !_COLLIDER_H_
