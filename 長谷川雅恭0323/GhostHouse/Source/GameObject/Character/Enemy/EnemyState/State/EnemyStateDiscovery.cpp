#include "EnemyStateDiscovery.h"
#include "../EnemyStateManager.h"
#include "../../../ModelBase.h"
#include "../../../../../Utility/Math/Math.h"
#include "../../../../../UI/UITexture.h"
#include "../../../../../Utility/Asset/SoundName.h"

EnemyStateDiscovery::EnemyStateDiscovery(float attackDistance, float maxSpeed)
	: EnemyStateBase{}
	, MAX_SPEED{ maxSpeed }
	, ATTACK_DISTANCE{ attackDistance }
	, m_MissTimer{ 0 }
{
}

void EnemyStateDiscovery::Initialize()
{}

void EnemyStateDiscovery::Update(float deltaTime)
{
	float l_Distance = Math::Distance(p_Player->GetPosition(), p_Me->GetPosition());

	if (l_Distance <= ATTACK_DISTANCE && p_Manager->GetTimer() >= 20.0f)
	{
		p_Manager->SetNextState(EnemyStateName::Attack);
	}
	else if (l_Distance <= 28 ||
		p_Manager->GetTimer() <= 60 * 5)
	{
		p_Manager->SetMotionID(5);
		p_Manager->GetMark()->HideOff();
		GSvector3 l_Velocity = p_Me->GetPosition() - p_Player->GetPosition();
		l_Velocity.y = 0.0f;
		p_Manager->SetVelocity(l_Velocity);

		const float l_SpeedUp = 0.002f;
		p_Manager->SpeedUp(l_SpeedUp, MAX_SPEED, deltaTime);
		p_Manager->Rotate(deltaTime);
		if (l_Distance >= ATTACK_DISTANCE)
			p_Manager->Move(deltaTime);

		m_MissTimer = 0;

	}
	else if (m_MissTimer <= 60 * 2)
	{
		p_Manager->SetMotionID(7);
		p_Manager->GetMark()->HideOn();
		m_MissTimer += deltaTime / 2;

		float l_RotateAngle = 3.0f;
		if (m_MissTimer == 100)
			l_RotateAngle *= -1;

		p_Manager->GetRotate().rotateY(l_RotateAngle);

	}
	else
	{
		p_Manager->SetNextState(EnemyStateName::Idle);
	}
}

void EnemyStateDiscovery::Draw() const
{
}

void EnemyStateDiscovery::Shutdown()
{
	p_Manager->GetMark()->HideOn();
}
