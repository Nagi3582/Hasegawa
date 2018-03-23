#include "EnemyStateGreenFind.h"
#include "../EnemyStateManager.h"
#include "../../../../../Actor/CollideActor.h"
#include "../../../../../Utility/Math/Math.h"
#include "../../../../../World/IWorld.h"
#include "../../../../Field/Field.h"
#include "../../../../../Collide/Line.h"
#include "../../../../../UI/UITexture.h"
#include <gslib.h>

EnemyStateGreenFind::EnemyStateGreenFind()
	: EnemyStateBase{}
	, m_State{ GreenEnemyState::Idle }
	, m_MissTimer{ 0 }
{
}

void EnemyStateGreenFind::Initialize()
{
	m_State = GreenEnemyState::Idle;
	m_MissTimer = 0;
	p_Manager->TimerReset();
}

void EnemyStateGreenFind::Update(float deltaTime)
{
	if (Math::Distance(p_Manager->GetPosition(), p_Player->GetPosition()) >= 40 && m_State == GreenEnemyState::Idle)
	{
		if (m_MissTimer <= 60 * 2)
		{
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
	else if (Math::Distance(p_Manager->GetPosition(), p_Player->GetPosition()) >= 20 && m_State == GreenEnemyState::Idle)
	{
		p_Manager->GetMark()->HideOff();
		p_Manager->SetMotionID(5);
		GSvector3 l_Front = p_Manager->GetPosition() - p_Player->GetPosition();
		l_Front.y = 0.0f;
		p_Manager->SetVelocity(l_Front.getNormalized());
		p_Manager->SetSpeed(0.4f);
		p_Manager->Rotate(deltaTime);
		p_Manager->Move(deltaTime);
		p_Manager->TimerReset();
	}
	else if (Math::Distance(p_Manager->GetPosition(), p_Player->GetPosition()) <= 20 && m_State == GreenEnemyState::Idle)
	{
		m_State = GreenEnemyState::Dive;
	}
	else if (m_State == GreenEnemyState::Dive)
	{
		p_Manager->GetMark()->HideOn();
		p_Manager->SetMotionID(3);
		p_Manager->SetSpeed(0.1f);
		GSvector3 l_Velocity(0.0f, 0.0f, 0.0f);
		if (p_Manager->GetTimer() <= 120)
		{
			l_Velocity.y = -1.3f;
		}
		else if (p_Manager->GetTimer() <= 140)
		{
			l_Velocity.y = 0;
			GSvector3 l_MovePosition = p_Player->GetPosition() - p_Player->GetRotate().getAxisZ().getNormalized() * 12.0f;
			//プレイヤーの後ろに壁がある場合壁を超えないようにする
			Line l_Line(p_Player->GetPosition(), l_MovePosition);
			GSvector3 l_Intersect;
			if (p_Manager->GetWorld()->GetField()->IsCollide(l_Line, &l_Intersect))
			{
				l_MovePosition = l_Intersect;
				//当たった場所より少し前に出す
				GSvector3 l_Front = p_Player->GetPosition() - l_MovePosition;
				l_MovePosition += l_Front.getNormalized() * 4.0f * deltaTime;
			}
			l_MovePosition.y = -10.0f;
			p_Manager->SetPosition(l_MovePosition);
		}
		else if (p_Manager->GetPosition().y <= 0.8f)
		{
			p_Manager->GetMark()->HideOn();
			l_Velocity.y = 2.3f;
			GSvector3 l_Front = p_Manager->GetPosition() - p_Player->GetPosition();
			l_Front.y = 0.0f;
			p_Manager->SetVelocity(l_Front.getNormalized());
			p_Manager->Rotate(deltaTime);

		}
		else
		{
			p_Manager->SetNextState(EnemyStateName::Attack);
		}

		p_Manager->OnMove(l_Velocity, deltaTime);
	}
}

void EnemyStateGreenFind::Draw() const
{
}

void EnemyStateGreenFind::Shutdown()
{
	GSvector3 l_Position = p_Manager->GetPosition();
	l_Position.y = 0.8f;
	p_Manager->SetPosition(l_Position);
	m_State = GreenEnemyState::Idle;
	p_Manager->TimerReset();
}
