#include "EnemyStateAttack.h"
#include "../EnemyStateManager.h"
#include "../../../../../World/IWorld.h"
#include "../../EnemyAttack/EnemyAttack.h"
#include "../../../../../Actor/ActorGroup.h"
#include "../../../../Light/LightColor.h"

#include "../../../../../Utility/Asset/SoundName.h"

EnemyStateAttack::EnemyStateAttack(float attackTime, bool redAttack)
	: EnemyStateBase{}
	, m_AttackTime{ attackTime }
	, m_RedAttack{ redAttack }
	, p_Attack{ nullptr }
{
}

void EnemyStateAttack::Initialize()
{
	p_Manager->SetSpeed(0.0f);

	if (m_RedAttack == true)
	{
		p_Manager->SetMotionID(1);

		const float l_DeadTime = 10;
		p_Attack = std::make_shared<EnemyAttack>(
			*p_Manager->GetWorld(), *p_Me, l_DeadTime, m_RedAttack, 4.0f, "RedEnemyAttack");
	}
	else
	{
		p_Manager->SetMotionID(9);
		p_Manager->SetVelocity(p_Manager->GetRotate().getAxisZ().getNormalized());

		const float l_DeadTime = 60;
		p_Attack = std::make_shared<EnemyAttack>(
			*p_Manager->GetWorld(), *p_Me, l_DeadTime, m_RedAttack);
	}
}

void EnemyStateAttack::Update(float deltaTime)
{
	p_Manager->Move(deltaTime);
	if (m_RedAttack)
	{
		GSvector3 l_Front = p_Manager->GetPosition() - p_Player->GetPosition();
		p_Manager->SetVelocity(l_Front);
		p_Manager->SetSpeed(0);
		p_Manager->Rotate(deltaTime);
	}
	if (p_Manager->GetTimer() == m_AttackTime)
	{
		//UŒ‚‚ğo‚·
		if (m_RedAttack == true)
		{
			gsPlaySE((GSuint)SoundName::EnemyAttackSE);
			p_Manager->SetSpeed(0);
		}
		else
		{
			p_Manager->SetSpeed(0.4f);
			gsPlaySE((GSuint)SoundName::EnemyAttackSE);
		}
		p_Manager->GetWorld()->AddCollideActor(ActorGroup::HitToPlayer, p_Attack);
	}


	//UŒ‚I—¹‚Ì“®‚«‚ğ’x‚­‚·‚é
	if (p_Manager->GetTimer() >= 90)
		p_Manager->SetSpeed(0.08f);

	if (p_Manager->GetTimer() >= 100 && m_RedAttack == false ||
		p_Manager->GetTimer() >= 45 && m_RedAttack == true)
	{
		//ƒvƒŒƒCƒ„[‚ÉUŒ‚‚ª“–‚½‚Á‚½‚©H
		EnemyAttack* l_pAttack = dynamic_cast<EnemyAttack*>(p_Attack.get());
		if (l_pAttack->IsHit() == true)
		{
			p_Manager->SetNextState(EnemyStateName::Laugh);
		}
		else
			p_Manager->SetNextState(EnemyStateName::Idle);
	}
}

void EnemyStateAttack::Draw() const
{
}

void EnemyStateAttack::Shutdown()
{
	p_Attack->Dead();
}