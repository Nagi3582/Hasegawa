#include "EnemyAttack.h"
#include "../../../../Collide/BoundingSphere.h"
#include "../../ModelBase.h"

EnemyAttack::EnemyAttack(IWorld & world, ModelBase & enemy, float deadTime, bool isFront, float radius, const std::string& name)
	: CollideActor{ world, name, GSvector3(0.0f, 0.0f, 0.0f), new BoundingSphere(GSvector3(0.0f, 0.0f, 0.0f), radius) }
	, m_DeadTime{ deadTime }
	, m_Counter{ 0 }
	, p_Enemy{ &enemy }
	, m_IsFront{ isFront }
	, m_IsHit{ false }
{
}

void EnemyAttack::OnUpdate(float deltaTime)
{
	m_Position = p_Enemy->GetPosition();

	//“–‚½‚è”»’è‚ð‘O•û‚Éo‚·
	if (m_IsFront == true)
	{
		m_Position += p_Enemy->GetRotate().getAxisZ().getNormalized()   * deltaTime;
	}

	if (m_Counter >= m_DeadTime)
	{
		m_Dead = true;
	}

	m_Counter += deltaTime;
}

void EnemyAttack::OnDraw(bool is_shadow, Renderer & renderer) const
{
}

void EnemyAttack::OnCollide(CollideActor & other)
{
	if (other.GetName() == "Player")
		m_IsHit = true;
}

bool EnemyAttack::IsHit() const
{
	return m_IsHit;
}
