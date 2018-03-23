#include "EnemyStateBlueFind.h"
#include "../EnemyStateManager.h"
#include "../EnemyStateName.h"
#include "../../../../../Utility/MoveHelper/MoveHelper.h"
#include "../../../../../Actor/CollideActor.h"
#include "../../../../../Utility/Math/Math.h"
#include "../../../../../UI/UITexture.h"

const float MOVE_SPEED_MAX = 0.3f;
//const float ROTATE_SPEED_MAX = 0.23f;
const float ROTATE_SPEED_MAX = 0.3f;
const float ROTATE_FRONT_SPEED_MAX = 0.3f;


EnemyStateBlueFind::EnemyStateBlueFind()
	: EnemyStateBase{}
	, m_Rand{ 0 }
	, m_Direction{ 1 }
	, m_NextStateTime{ 0 }
	, m_State{ BlueFindState::Idle }
	, m_MissTimer{ 0 }
{
}

void EnemyStateBlueFind::Initialize()
{
	m_Rand = gsRand(0, 10);
	m_MissTimer = 0;
	m_NextStateTime = gsRand(60, 120);
	m_State = BlueFindState::Idle;
}

void EnemyStateBlueFind::Update(float deltaTime)
{
	p_Manager->SetMotionID(5);
	p_Manager->GetMark()->HideOff();
	GSvector3 l_Front = p_Manager->GetPosition() - p_Player->GetPosition();
	l_Front.y = 0.0f;
	p_Manager->SetVelocity(l_Front.getNormalized());
	p_Manager->Rotate(deltaTime);


	if (m_State == BlueFindState::Idle)
	{
		if (Math::Distance(p_Manager->GetPosition(), p_Player->GetPosition()) >= 14)
		{
			p_Manager->SpeedUp(0.05f, MOVE_SPEED_MAX, deltaTime);
			p_Manager->Move(deltaTime);
			if (p_Manager->GetTimer() >= m_NextStateTime)
			{
				Think();
			}
		}
		else
		{
			p_Manager->SetSpeed(0);
		}

		if (p_Manager->GetTimer() >= m_NextStateTime)
		{
			Think();
		}
	}
	else if (m_State == BlueFindState::Move)
	{
		p_Manager->Fly(deltaTime);
		p_Manager->SetSpeed(ROTATE_SPEED_MAX);

		GSvector3 l_Velocity = p_Manager->GetRotate().getAxisX().getNormalized() * m_Direction * deltaTime;
		GSvector3 l_Front = p_Player->GetPosition() - p_Manager->GetPosition();
		l_Velocity += l_Front.getNormalized() * ROTATE_FRONT_SPEED_MAX * deltaTime;
		p_Manager->OnMove(l_Velocity, deltaTime);
		if (p_Manager->GetTimer() >= 70)
		{
			m_State = BlueFindState::Idle;
			m_NextStateTime = gsRand(60, 120);
			p_Manager->SetSpeed(0);
		}
	}
	if (Math::Distance(p_Manager->GetPosition(), p_Player->GetPosition()) >= 40)
	{
		if (m_MissTimer <= 60 * 2)
		{
			m_State = BlueFindState::Idle;
			p_Manager->SetMotionID(7);
			p_Manager->GetMark()->HideOn();
			p_Manager->TimerReset();
			m_MissTimer += deltaTime / 2;

			float l_RotateAngle = 3.0f;
			if (m_MissTimer == 100)
				l_RotateAngle *= -1;

			p_Manager->GetRotate().rotateY(l_RotateAngle);

		}
		else
		{
			p_Manager->GetMark()->HideOn();
			p_Manager->SetNextState(EnemyStateName::Idle);
		}

	}
}

void EnemyStateBlueFind::Draw() const
{
}

void EnemyStateBlueFind::Shutdown()
{
}

void EnemyStateBlueFind::Think()
{
	if (m_Rand <= 3)
	{
		m_State = BlueFindState::Move;
		m_Direction = 1;
		m_Rand = gsRand(0, 10);
		p_Manager->SetSpeed(0.0f);
	}
	else if (m_Rand <= 6)
	{
		m_State = BlueFindState::Move;
		m_Direction = -1;
		m_Rand = gsRand(0, 10);
		p_Manager->SetSpeed(0.0f);
	}
	else
	{
		p_Manager->SetNextState(EnemyStateName::Attack);
	}
	p_Manager->TimerReset();
}
