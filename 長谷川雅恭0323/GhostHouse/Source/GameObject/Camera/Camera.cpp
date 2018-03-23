#include "Camera.h"
#include"../../Utility/Renderer/Renderer.h"
#include"../../Base/Screen.h"

const int RETURN_TIME = 80;
const float BACK_DISTANCE = 23.0f;
const float UP_DISTANCE = 23.0f;

Camera::Camera(CollideActorPtr& player)
	: CollideActor{}
	, p_Player{ player }
	, m_Velocity{ 0.0f,0.0f,0.0f }
	, m_TargetPos{ 0.0f,0.0f,0.0f }
	, m_Angle{ 45.0f }
	, m_CurrentState{ CameraState::Normal }
	, m_Timer{ 0 }
{
	m_Position = GSvector3(0.0f, 50.0f, -100.0f);
}

void Camera::OnUpdate(float deltaTime)
{
	m_Rotate.identity();
	m_Rotate.rotateX(m_Angle);

	if (m_CurrentState == CameraState::Normal)
	{
		NormalUpdate(deltaTime);
	}
	else if (m_CurrentState == CameraState::Target)
	{
		TargetUpdate(deltaTime);
	}

}

void Camera::OnDraw(bool is_shadow, Renderer& m_renderer) const
{
	const float angle = 60.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(angle, WIDTH / HEIGHT, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);

	GSmatrix4 l_Pose = GSmatrix4(GetRotate().setPosition(m_Position));
	glLoadMatrixf(l_Pose.convertViewRH());

	GSmatrix4 local_view;
	GSvector3 flont_vec = GetRotate().getAxisZ() + m_Position;
	local_view.setLookAtRH(m_Position, flont_vec, GSvector3{ 0.0f,1.0f,0.0f });
	m_renderer.set_view(local_view);
	m_renderer.set_camera_position(m_Position);
	GSmatrix4 projection;
	projection.setPerspectiveRH(angle, WIDTH / HEIGHT, 3.0f, 500.0f);
	m_renderer.set_projection(projection);
}

void Camera::SetTarget(const GSvector3 & position)
{
	m_TargetPos = position;
}

void Camera::Spring(
	const GSvector3& restPosition,
	float stiffness,
	float friction,
	float mass)
{
	//ばねの伸び具合
	const GSvector3 stretch = m_Position - restPosition;
	//ばねの力の計算
	const GSvector3 force = -stiffness * stretch;
	//加速度を追加(力/質量)
	const GSvector3 accelaration = force / mass;
	//移動速度を計算
	m_Velocity = friction * (m_Velocity + accelaration);

}

void Camera::NormalUpdate(float deltaTime)
{
	const GSvector3 l_Back = GSvector3(0.0f, 0.0f, -BACK_DISTANCE);
	const GSvector3 l_Up = GSvector3(0.0f, UP_DISTANCE, 0.0f);

	GSvector3 l_TargetPos = p_Player->GetPosition() + l_Back + l_Up;

	//デバック用
	if (gsGetKeyTrigger(GKEY_SPACE))
	{
		m_CurrentState = CameraState::Target;
	}

	Spring(l_TargetPos, 1.5f, 0.2f, 2.0f);

	m_Position += m_Velocity * deltaTime;
}

void Camera::TargetUpdate(float deltaTime)
{
	const GSvector3 l_Back = GSvector3(0.0f, 0.0f, -BACK_DISTANCE);
	const GSvector3 l_Up = GSvector3(0.0f, UP_DISTANCE, 0.0f);

	if (m_Timer >= 60 * 5 + RETURN_TIME)
	{
		m_CurrentState = CameraState::Normal;
		m_Timer = 0;
	}
	else if (m_Timer >= 60 * 5)
	{
		m_TargetPos = p_Player->GetPosition();
	}
	else
	{
		m_TargetPos = GSvector3(0.0f, 25.0f, 0.0f);
	}

	GSvector3 l_TargetPos = m_TargetPos + l_Back + l_Up;

	Spring(l_TargetPos, 1.5f, 0.2f, 6.0f);

	m_Position += m_Velocity * deltaTime;

	m_Timer += deltaTime;

}
