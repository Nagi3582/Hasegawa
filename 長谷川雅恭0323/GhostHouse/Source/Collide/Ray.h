#ifndef _RAY_H_
#define _RAY_H_
#include <gslib.h>

class Ray
{
public:
	//’¼üƒNƒ‰ƒX
	Ray(const GSvector3 start, const GSvector3 direction)
		: m_Start(start)
		, m_Direction(direction)
	{}

public:
	GSvector3 m_Start;
	GSvector3 m_Direction;

};

#endif // !_RAY_H_
