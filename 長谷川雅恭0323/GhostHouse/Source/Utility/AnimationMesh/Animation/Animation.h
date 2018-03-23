#ifndef _ANIMATION_H_
#define _ANIMATION_H

#include <array>
#include <gslib.h>

class Animation
{
public:
	using Matrices = std::array<GSmatrix4, 256>;

public:
	Animation(GSuint animation, GSuint motion);

	void Update(float time);

	//モーションの変更
	void ChangeMotion(GSuint motion);
	//再生中のモーション
	GSuint GetMotion()const;
	//ボーンの数
	GSuint GetBornCount()const;
	//終了時間
	GSuint GetEndTime()const;
	//変換行列を返す
	const Animation::Matrices& GetMatrices()const;

private:
	//補間フレーム数
	const GSfloat LERP_TIME = 10.0f;
	//アニメーション番号
	GSuint mAnimationID;
	//再生中のモーション番号
	GSuint mMotion;
	//再生中のモーションタイマー
	GSfloat mMotionTimer;
	//前回再生したモーション番号
	GSuint mPrevMotion;
	//前回再生した最終モーションタイマー
	GSfloat mPrevMotionTimer;
	//補間アニメーションタイマー
	GSfloat lerpTimer;
	//アニメーション変換行列
	Matrices mMatrices;
};

#endif // !_ANIMATION_H_

