#include "WhiteEnemy.h"
#include "../../../Utility/Asset/MeshName.h"

#include "EnemyState/State/EnemyStateRotate.h"
#include "EnemyState/State/EnemyStateDiscovery.h"
#include "EnemyState/State/EnemyStateAttack.h"
#include "EnemyState/State/EnemyStateStop.h"
#include "EnemyState/State/EnemyStateLaugh.h"

WhiteEnemy::WhiteEnemy(IWorld & world, GSvector3 position, CollideActor & player, Renderer& renderer)
	: EnemyBase{ world,MeshName::WhiteEnemy,LightColor::White,position,player ,renderer }
{
	SetState(player);
	m_Manager.SetUp(EnemyStateName::Idle);
	SetAnimation(renderer, MeshName::WhiteEnemy, 0);
}

void WhiteEnemy::SetState(CollideActor & player)
{
	m_Manager.AddState(EnemyStateName::Idle, std::make_shared<EnemyStateRotate>(10.0f, 0.5f), player, *this);
	m_Manager.AddState(EnemyStateName::Approach, std::make_shared<EnemyStateDiscovery>(), player, *this);
	m_Manager.AddState(EnemyStateName::Attack, std::make_shared<EnemyStateAttack>(20), player, *this);
	m_Manager.AddState(EnemyStateName::Stop, std::make_shared<EnemyStateStop>(), player, *this);
	m_Manager.AddState(EnemyStateName::Laugh, std::make_shared<EnemyStateLaugh>(), player, *this);
}
