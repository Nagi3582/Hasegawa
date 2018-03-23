#include "Math.h"
#define _USE_MATH_DEFINES
#include <cmath>

const float Math::EPSILON = 0.0000001f;

/*２点間の距離を求める*/
float Math::Distance(GSvector3 start, GSvector3 end)
{
	float distance;
	distance =
		(end.x - start.x) * (end.x - start.x)
		+ (end.y - start.y) * (end.y - start.y)
		+ (end.z - start.z) * (end.z - start.z);

	float result = Sqrt(distance);

	return result;
}
/*２点間の距離を求める*/
float Math::Distance(GSvector2 start, GSvector2 end)
{
	float distance;
	distance =
		(end.x - start.x) * (end.x - start.x)
		+ (end.y - start.x) * (end.y - start.y);

	float result = Sqrt(distance);

	return result;
}


//2つのベクトルの外積を求める
GSvector3 Math::Cross(const GSvector3& v1, const GSvector3& v2)
{
	GSvector3 l_Result;

	l_Result.x = (v1.y * v2.z) - (v1.z * v2.y);
	l_Result.y = (v1.z * v2.x) - (v1.x * v2.z);
	l_Result.z = (v1.x * v2.y) - (v1.y * v2.x);

	return l_Result;
}
//二つのベクトルの内積を求める
float Math::Dot(const GSvector2 v1, const GSvector2 v2)
{
	float l_Result;
	l_Result = (v1.x * v2.x) + (v1.y * v2.y);
	return l_Result;
}

//二つのベクトルの内積を求める
float Math::Dot(const GSvector3 v1, const GSvector3 v2)
{
	float l_Result;

	l_Result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

	return l_Result;
}
//二つのベクトルの角度を求める(360度)
float Math::ArcTangent(const float& x, const float& y)
{
	float result;

	result = atan2f(y, x);
	result = To_Degree(result);
	if (result < 0)
		result += 360;


	return result;
}

float Math::Angle(const GSvector2& first_vec2, const GSvector2& second_vec2)
{
	float result = 0;
	//一つ目のベクトルの長さを求める
	float first_Length = (first_vec2.x * first_vec2.x) + (first_vec2.y * first_vec2.y);
	first_Length = Sqrt(first_Length);
	//二つ目のベクトルの長さを求める	
	float second_Length = (second_vec2.x * second_vec2.x) + (second_vec2.y * second_vec2.y);
	second_Length = Sqrt(second_Length);
	//角度を求める
	result = Dot(first_vec2, second_vec2) / (first_Length * second_Length);
	//l_Result = l_Result * 3.14159 / 180;
	result = acos(result);
	result = To_Degree(result);

	if (result <= EPSILON)
		result = 0;
	if (result >= 180 - EPSILON)
		result = 180;

	return result;
}

GSvector2 Math::Vec2_Turn(const GSvector2 & v, float & angle)
{
	GSvector2 result;
	//ラジアンを求める
	float radian = To_Radian(angle);

	result.x = v.x * cos(radian) - v.y * sin(radian);
	result.y = v.x * sin(radian) - v.y * cos(radian);

	return result;
}

float Math::Absolute(float & f)
{
	if (f < 0)
		return f * -1;

	return f;
}

//ベクトルが右回転か左回転かを求める
bool Math::TurnLeft(GSvector2 main, GSvector2 ask)
{
	float cross(main.x * ask.y - main.y * ask.x);

	if (cross >= 0)
		return true;
	else if (cross < 0)
		return false;

	return false;
}

//反時計回りにベクトルを回転
GSvector2 Math::Vec2_Turn(GSvector2 vec2, float angle)
{
	GSvector2 result;
	//ラジアンを求める
	float radian = To_Radian(angle);

	result.x = vec2.x * cos(radian) - vec2.y * sin(radian);
	result.y = vec2.x * sin(radian) - vec2.y * cos(radian);

	return result;
}

//ラジアン角を角度に変換
float Math::To_Degree(float radian)
{
	return radian * (180 / 3.14159);
}

//角度をラジアン角に変換
float Math::To_Radian(float degree)
{
	return degree * (3.14159 / 180);
}

float Math::FloatZero(float & f)
{
	float lResult = f;
	if (lResult <= EPSILON)
		lResult = 0;

	return lResult;
}

float Math::Sqrt(float square)
{
	float result;
	result = std::sqrt(square);
	return result;
}


