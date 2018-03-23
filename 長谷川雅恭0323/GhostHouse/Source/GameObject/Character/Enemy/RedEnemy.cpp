#include "RedEnemy.h"
#include "../../../Utility/Asset/MeshName.h"
#include "../../Light/LightColor.h"
#include "EnemyState/State/EnemyStateIdle.h"
#include "EnemyState/State/EnemyStateDiscovery.h"
#include "EnemyState/State/EnemyStateAttack.h"
#include "EnemyState/State/EnemyStateStop.h"
#include "EnemyState/State/EnemyStateLaugh.h"


RedEnemy::RedEnemy(IWorld & world, GSvector3 position, CollideActor & player, Renderer& renderer)
	: EnemyBase{ world,MeshName::RedEnemy,LightColor::Red,position,player ,renderer }
{
	SetState(player);
	m_Manager.SetUp(EnemyStateName::Idle);
	SetAnimation(renderer, MeshName::RedEnemy, 0);

}

void RedEnemy::SetState(CollideActor & player)
{
	m_Manager.AddState(EnemyStateName::Idle, std::make_shared<EnemyStateIdle>(), player, *this);
	m_Manager.AddState(EnemyStateName::Approach, std::make_shared<EnemyStateDiscovery>(6.5f, 0.35f), player, *this);
	m_Manager.AddState(EnemyStateName::Attack, std::make_shared<EnemyStateAttack>(20, true), player, *this);
	m_Manager.AddState(EnemyStateName::Stop, std::make_shared<EnemyStateStop>(), player, *this);
	m_Manager.AddState(EnemyStateName::Laugh, std::make_shared<EnemyStateLaugh>(), player, *this);
}
