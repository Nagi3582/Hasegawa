#include "EnemyStateManager.h"
#include "EnemyStateName.h"
#include "EnemyStateBase.h"
#include "../../ModelBase.h"
#include "../../../../Utility/MoveHelper/MoveHelper.h"
#include "../../../../World/IWorld.h"
#include "../../../../UIObject/Effect/ExclamationMark3D.h"
#include "../../../../Actor/ActorGroup.h"

const float LERP_TIME = 10;


EnemyStateManager::EnemyStateManager(CollideActor& player, ModelBase& me, IWorld& world)
	: m_CurrentState{ nullptr }
	, m_CurrentStateName{ EnemyStateName::None }
	, m_Position{ me.GetPosition() }
	, m_Velocity{ 0.0f,0.0f,0.0f }
	, m_Rotate{ GS_MATRIX4_IDENTITY }
	, m_Speed{ 0.0f }
	, p_World{ &world }
	, m_Timer{ 0.0f }
	, m_NextState{ EnemyStateName::None }
	, m_LerpTimer{ 0 }
	, m_SwingTimer{ 0 }
	, m_MotionID{ 0 }
	, p_Mark{ nullptr }
{
	m_States.clear();
	ActorPtr l_Mark = std::make_shared<ExclamationMark3D>(*p_World, me);
	p_World->AddActor(ActorGroup::Effect, l_Mark);
	p_Mark = l_Mark.get();
	p_Mark->HideOn();
}

void EnemyStateManager::SetUp(EnemyStateName name)
{
	m_CurrentStateName = name;
	m_CurrentState = m_States[m_CurrentStateName];
	m_CurrentState->Initialize();


}

int EnemyStateManager::GetMotionID() const
{
	return m_MotionID;
}

void EnemyStateManager::SetMotionID(int id)
{
	m_MotionID = id;
}

void EnemyStateManager::Update(float deltaTime)
{
	m_CurrentState->Update(deltaTime);
	m_Timer += deltaTime;
	Change();
}

void EnemyStateManager::Collide(CollideActor & other)
{
	m_CurrentState->Collide(other);
}

void EnemyStateManager::Draw() const
{
	m_CurrentState->Draw();
}

GSvector3 EnemyStateManager::GetPosition()
{
	return m_Position;
}

GSmatrix4 EnemyStateManager::GetRotate() const
{
	return m_Rotate;
}

void EnemyStateManager::Rotate(float deltaTime)
{
	if (m_Velocity.x != 0.0f || m_Velocity.z != 0.0f)
	{
		m_LerpTimer = std::min(m_LerpTimer + deltaTime, LERP_TIME);
		GSvector3 l_Front = m_Velocity.lerp(m_Rotate.getAxisZ(), m_LerpTimer);
		l_Front.y = 0.0f;
		l_Front.normalize();
		const GSvector3 l_Up = m_Rotate.getAxisY();
		const GSvector3 l_Left = l_Up.cross(l_Front);

		m_Rotate.setAxisX(l_Left);
		m_Rotate.setAxisY(l_Up);
		m_Rotate.setAxisZ(l_Front);
	}
}

void EnemyStateManager::Move(float deltaTime)
{
	Fly(deltaTime);
	m_Position += m_Rotate.getAxisZ() * m_Speed * deltaTime;
}

void EnemyStateManager::Fly(float deltaTime)
{
	const float l_Swing = 120.0f;
	GSvector3 l_SwingVel(0.0f, 0.0f, 0.0f);
	l_SwingVel.y = MoveHelper::EasingSwing(l_Swing, m_SwingTimer, 0.05f);
	m_SwingTimer += deltaTime;
	m_Position += l_SwingVel * deltaTime;
}

void EnemyStateManager::SetVelocity(GSvector3 velocity)
{
	velocity.normalize();
	m_Velocity = velocity;
}

void EnemyStateManager::SetPosition(GSvector3 position)
{
	m_Position = position;
}

void EnemyStateManager::OnMove(GSvector3 velocity, float deltaTime)
{
	m_Position += velocity * m_Speed * deltaTime;
}

void EnemyStateManager::SpeedUp(float plus, float max, float deltaTime)
{
	m_Speed += plus * deltaTime;
	m_Speed = CLAMP(m_Speed, 0.0f, max);
}

void EnemyStateManager::SetSpeed(float speed)
{
	m_Speed = speed;
}

float EnemyStateManager::GetSpeed() const
{
	return m_Speed;
}

IWorld * EnemyStateManager::GetWorld()
{
	return p_World;
}

Actor * EnemyStateManager::GetMark()
{
	return p_Mark;
}

void EnemyStateManager::SetNextState(const EnemyStateName & next)
{
	m_NextState = next;
}

float EnemyStateManager::GetTimer()const
{
	return m_Timer;
}

void EnemyStateManager::TimerReset()
{
	m_Timer = 0;
}

void EnemyStateManager::AddState(EnemyStateName name, const EnemyStateBasePtr & state, CollideActor & player, ModelBase & me)
{
	m_States[name] = state;
	m_States[name]->SetUp(player, me, *this);
}

void EnemyStateManager::Change()
{
	if (m_NextState != EnemyStateName::None)
	{
		m_CurrentStateName = m_NextState;
		m_CurrentState->Shutdown();
		m_CurrentState = m_States[m_CurrentStateName];
		m_CurrentState->Initialize();
		m_Timer = 0;
		m_NextState = EnemyStateName::None;
	}
}
