#include "BlueEnemy.h"
#include "../../../Utility/Asset/MeshName.h"
#include "../../Light/LightColor.h"
#include "EnemyState/State/EnemyStateIdle.h"
#include "EnemyState/State/EnemyStateDiscovery.h"
#include "EnemyState/State/EnemyStateBlueFind.h"
#include "EnemyState/State/EnemyStateAttack.h"
#include "EnemyState/State/EnemyStateStop.h"
#include "EnemyState/State/EnemyStateLaugh.h"


BlueEnemy::BlueEnemy(IWorld & world, GSvector3 position, CollideActor & player, Renderer& renderer)
	: EnemyBase{ world,MeshName::BlueEnemy,LightColor::Blue,position,player ,renderer }
{
	SetState(player);
	m_Manager.SetUp(EnemyStateName::Idle);
	SetAnimation(renderer, MeshName::BlueEnemy, 0);
}

void BlueEnemy::SetState(CollideActor & player)
{
	const float l_SpeedUp = 0.15f;
	m_Manager.AddState(EnemyStateName::Idle, std::make_shared<EnemyStateIdle>(l_SpeedUp), player, *this);
	m_Manager.AddState(EnemyStateName::Approach, std::make_shared<EnemyStateBlueFind>(), player, *this);
	m_Manager.AddState(EnemyStateName::Attack, std::make_shared<EnemyStateAttack>(20), player, *this);
	m_Manager.AddState(EnemyStateName::Stop, std::make_shared<EnemyStateStop>(), player, *this);
	m_Manager.AddState(EnemyStateName::Laugh, std::make_shared<EnemyStateLaugh>(), player, *this);
}