#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "../../Actor/CollideActor.h"
#include "../../Actor/CollideActorPtr.h"

class Renderer;

enum class CameraState
{
	Normal,
	Target,

};

class Camera :public CollideActor
{
public:
	Camera(CollideActorPtr& player);

	virtual void OnUpdate(float deltaTime)override;
	virtual void OnDraw(bool is_shadow, Renderer& m_renderer)const override;

	void SetTarget(const GSvector3& position);


private:
	void Spring(const GSvector3& restPosition, float stiffness, float friction, float mass);

	void NormalUpdate(float deltaTime);
	void TargetUpdate(float deltaTime);


private:
	CollideActorPtr p_Player;
	GSvector3 m_Velocity;
	GSvector3 m_TargetPos;
	float m_Angle;
	CameraState m_CurrentState;


	float m_Timer;

};

#endif // !_CAMERA_H_