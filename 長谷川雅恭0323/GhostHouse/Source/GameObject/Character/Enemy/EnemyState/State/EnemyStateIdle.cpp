#include "EnemyStateIdle.h"
#include "../../../ModelBase.h"
#include "../../../../../Utility/Math/Math.h"
#include "../EnemyStateManager.h"
#include "../../../../../UI/UITexture.h"

#include "../../../../../Utility/Asset/SoundName.h"

EnemyStateIdle::EnemyStateIdle(float speedMax)
	: EnemyStateBase{}
	, m_Direction{ 1.0f,0.0f,0.0f }
	, MAX_SPEED{ speedMax }
	, m_SECounter{ 0 }
{
}

void EnemyStateIdle::Initialize()
{
	p_Manager->SetMotionID(5);
	p_Manager->GetMark()->HideOn();
}

void EnemyStateIdle::Update(float deltaTime)
{
	p_Manager->Rotate(deltaTime);
	if (p_Manager->GetTimer() >= 60 * 5)
	{
		m_Direction *= -1;
		p_Manager->TimerReset();
	}

	const float l_SpeedUp = 0.005f;
	p_Manager->SpeedUp(l_SpeedUp, MAX_SPEED, deltaTime);
	p_Manager->SetVelocity(m_Direction);
	p_Manager->Move(deltaTime);


	float l_Distance = Math::Distance(p_Me->GetPosition(), p_Player->GetPosition());
	if (l_Distance <= 20.0f)
	{
		p_Manager->SetNextState(EnemyStateName::Approach);

		if (m_SECounter <= 0)
		{
			gsPlaySE((GSuint)SoundName::DiscoverySE);
			m_SECounter = 30;
		}
	}
	m_SECounter -= deltaTime / 2;
}

void EnemyStateIdle::Draw() const
{
}

void EnemyStateIdle::Shutdown()
{
}
