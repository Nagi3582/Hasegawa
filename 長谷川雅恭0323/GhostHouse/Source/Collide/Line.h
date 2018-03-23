#ifndef _LINE_H_
#define _LINE_H_
#include <gslib.h>

class Line
{
public:

	Line(const GSvector3 start, const GSvector3 end)
		: m_Start(start)
		, m_End(end)
	{}


public:
	GSvector3 m_Start;
	GSvector3 m_End;

};

#endif // !_LINE_H_