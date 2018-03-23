#ifndef _MATH_H_
#define _MATH_H_
#include <gslib.h>

class Math
{
public:
	/*
	***3次元空間の2つの点の距離***
	引数1：始点
	引数2：終点
	*/
	static float Distance(GSvector3 start, GSvector3 end);

	/*
	***2次元空間の2つの点の距離***
	引数1：始点
	引数2：終点
	*/
	static float Distance(GSvector2 start, GSvector2 end);

	/*
	***外積***
	引数1：ベクトル1
	引数2：ベクトル2
	*/
	static GSvector3 Cross(const GSvector3& v1, const GSvector3& v2);

	/*
	***2次元ベクトルの内積***
	引数1：ベクトル1
	引数2：ベクトル2
	*/
	static float Dot(const GSvector2 v1, const GSvector2 v2);

	/*
	***3次元ベクトルの内積***
	引数1：ベクトル1
	引数2：ベクトル2
	*/
	static float Dot(const GSvector3 v1, const GSvector3 v2);

	/*
	***　アークタンジェント　角度を求める***
	引数1：底辺の長さ
	引数2：高さの長さ
	*/
	static float ArcTangent(const float& x, const float& y);

	/*
	***角度(180度まで)***
	引数1：ベクトル1
	引数2：ベクトル2
	*/
	static float Angle(const GSvector2& first_vec2, const GSvector2& second_vec2);

	/*
	***ベクトルの回転***
	引数1：回転させるベクトル
	引数2：回転する角度
	*/
	static GSvector2 Vec2_Turn(const GSvector2& v, float& angle);

	/*
	***絶対値を求める***
	*/
	static float Absolute(float& f);

	//ベクトルが右側か左側を求める()
	//	引数1：主軸となるベクトル
	//	引数2：求めるベクトル
	static bool TurnLeft(GSvector2 main, GSvector2 ask);

	//ベクトルの回転
	static GSvector2 Vec2_Turn(GSvector2 vec2, float angle);

	//ラジアン角を角度に変換
	static float To_Degree(float radian);

	//角度をラジアン角に変換
	static float To_Radian(float degree);

	/*
	***小さい誤差をなくす***
	引数：0にしたい数
	*/
	static float FloatZero(float& f);

	/*平方根√*/
	static float Sqrt(float square);

	/****小さい誤差をなくす****/
	static const float EPSILON;


};

#endif // !_ENEMYSUPPORT_H_
