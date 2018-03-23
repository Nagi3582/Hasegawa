#include "Animation.h"

Animation::Animation(GSuint animation, GSuint motion)
	: mAnimationID(animation)
	, mMotion(motion)
	, mMotionTimer(0.0f)
	, mPrevMotion(motion)
	, mPrevMotionTimer(0.0f)
	, lerpTimer(0.0f)
{
	gsCalculateAnimation(mAnimationID
		, mMotion
		, mMotionTimer
		, mMatrices.data());
}

void Animation::Update(float time)
{
	mMotionTimer += time;
	//lerpTimer + time と LERP_TIMEの小さいほうを返す
	lerpTimer = std::min(lerpTimer + time, LERP_TIME);
	//今のアニメーションと前のアニメーションをくっつける
	gsCalculateAnimationLerp(
		mAnimationID, mPrevMotion, mPrevMotionTimer,
		mAnimationID, mMotion, mMotionTimer,
		lerpTimer / LERP_TIME,
		mMatrices.data()
	);

}

void Animation::ChangeMotion(GSuint motion)
{
	//同じモーションの時は何もしない
	if (motion == mMotion)
		return;
	//今のモーションをコピー
	mPrevMotion = mMotion;
	mPrevMotionTimer = mMotionTimer;
	//新しいモーションを入れる
	mMotion = motion;
	mMotionTimer = 0.0f;
	lerpTimer = 0.0f;
}

GSuint Animation::GetMotion()const
{
	return mMotion;
}

GSuint Animation::GetBornCount()const
{
	return gsGetAnimationNumBones(mAnimationID, mMotion);
}

GSuint Animation::GetEndTime()const
{
	return gsGetEndAnimationTime(mAnimationID, mMotion);
}

const Animation::Matrices& Animation::GetMatrices()const
{
	return mMatrices;
}