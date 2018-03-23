#include "EnemyStateRotate.h"
#include "../EnemyStateManager.h"
#include "../../../../../Utility/MoveHelper/MoveHelper.h"
#include "../../../../../Utility/Math/Math.h"
#include "../../../ModelBase.h"

#include "../../../../../Utility/Asset/SoundName.h"

const float MAX_SPEED = 0.05f;

EnemyStateRotate::EnemyStateRotate(float distance, float rotateSpeed, float discovery)
	: EnemyStateBase{}
	, DISTANCE_MAX{ distance }
	, m_Angle{ 0.0f }
	, m_Distance{ distance }
	, m_RotateSpeed{ rotateSpeed }
	, m_BasePosition{ 0.0f,3.0f,0.0f }
	, DISCOVERY_DISTANCE{ discovery }
	, m_SECounter{ 0 }
{
}

void EnemyStateRotate::Initialize()
{
	m_BasePosition = p_Manager->GetPosition();
	p_Manager->SetMotionID(5);
	//m_Distance = 0.0f;
}

void EnemyStateRotate::Update(float deltaTime)
{
	p_Manager->Rotate(deltaTime);

	const float l_DistancePlus = 0.07f;
	m_Distance += l_DistancePlus * deltaTime;
	if (m_Distance >= DISTANCE_MAX)
		m_Distance = DISTANCE_MAX;

	//回転する位置をセット
	GSvector2 l_Vec2_Position = MoveHelper::CircleRotate(m_BasePosition.x, m_BasePosition.z, m_Distance, m_RotateSpeed, m_Angle, deltaTime);
	GSvector3 l_Position(l_Vec2_Position.x, 3.0f, l_Vec2_Position.y);



	//進む方向をセット
	GSvector3 l_Velocity = p_Manager->GetPosition() - l_Position;

	//p_Manager->SetPosition(l_Position);


	p_Manager->Move(deltaTime);
	const float l_SpeedUp = 0.005f;
	p_Manager->SpeedUp(l_SpeedUp, MAX_SPEED, deltaTime);
	p_Manager->SetVelocity(l_Velocity);


	float l_Distance = Math::Distance(p_Me->GetPosition(), p_Player->GetPosition());
	if (l_Distance <= DISCOVERY_DISTANCE)
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

void EnemyStateRotate::Draw() const
{
}

void EnemyStateRotate::Shutdown()
{
}
