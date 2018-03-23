#include "MoveHelper.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "../Math/Math.h"


float MoveHelper::EasingSwing(const float & swingTime, float & count, const float & range)
{
	float l_Result = sin(M_PI * 2 / swingTime * count) * range;
	return l_Result;
}

GSvector2 MoveHelper::CircleRotate(float baseX, float baseY, float distance, float speed, float& angle, float deltaTime)
{
	float l_Radian = Math::To_Radian(angle);

	GSvector2 l_Position(0.0f, 0.0f);

	l_Position.x = baseX + cos(l_Radian) * distance;
	l_Position.y = baseY + sin(l_Radian) * distance;

	angle += speed * deltaTime;

	return l_Position;
}

void MoveHelper::BoolReverse(bool & reverse)
{
	if (reverse == true)
		reverse = false;
	else
		reverse = true;
}
