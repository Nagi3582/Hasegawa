#include "GreenEnemy.h"
#include "../../../Utility/Asset/MeshName.h"
#include "../../Light/LightColor.h"
#include "EnemyState/State/EnemyStateRotate.h"
//#include "EnemyState/State/EnemyStateDiscovery.h"
#include "EnemyState/State/EnemyStateGreenFind.h"
#include "EnemyState/State/EnemyStateAttack.h"
#include "EnemyState/State/EnemyStateStop.h"
#include "EnemyState/State/EnemyStateLaugh.h"


GreenEnemy::GreenEnemy(IWorld & world, GSvector3 position, CollideActor & player, Renderer& renderer)
	: EnemyBase{ world,MeshName::GreenEnemy,LightColor::Green,position,player,renderer }
{
	SetState(player);
	m_Manager.SetUp(EnemyStateName::Idle);
	SetAnimation(renderer, MeshName::GreenEnemy, 0);
}

void GreenEnemy::SetState(CollideActor & player)
{
	m_Manager.AddState(EnemyStateName::Idle, std::make_shared<EnemyStateRotate>(10.0f, 0.5f, 35.0f), player, *this);
	m_Manager.AddState(EnemyStateName::Approach, std::make_shared<EnemyStateGreenFind>(), player, *this);
	m_Manager.AddState(EnemyStateName::Attack, std::make_shared<EnemyStateAttack>(20), player, *this);
	m_Manager.AddState(EnemyStateName::Stop, std::make_shared<EnemyStateStop>(), player, *this);
	m_Manager.AddState(EnemyStateName::Laugh, std::make_shared<EnemyStateLaugh>(), player, *this);
}
