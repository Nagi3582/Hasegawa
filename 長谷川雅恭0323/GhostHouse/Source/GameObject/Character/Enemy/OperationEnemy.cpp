/*�`���[�g���A���V�[���p�U�����Ȃ��G*/

#include "OperationEnemy.h"
#include "../../../Utility/Asset/MeshName.h"

#include "EnemyState/State/EnemyStateRotate.h"
#include "EnemyState/State/EnemyStateDiscovery.h"
#include "EnemyState/State/EnemyStateAttack.h"
#include "EnemyState/State/EnemyStateStop.h"
#include "EnemyState/State/EnemyStateLaugh.h"

#include "../../../UIObject/Operation/OperationManager.h"


OperationEnemy::OperationEnemy(IWorld & world, GSvector3 position, CollideActor & player, Renderer & renderer, OperationManager& operationManager)
	: EnemyBase{ world,MeshName::WhiteEnemy,LightColor::White,position,player ,renderer }
	, p_OperationManager{ &operationManager }
{
	SetState(player);
	m_Manager.SetUp(EnemyStateName::Idle);
	SetAnimation(renderer, MeshName::WhiteEnemy, 0);
}

void OperationEnemy::SetState(CollideActor & player)
{
	m_Manager.AddState(EnemyStateName::Idle, std::make_shared<EnemyStateRotate>(10.0f, 0.5f, -1), player, *this);	//�������鋗����-1�ɂ��邱�ƂŌ�����Ȃ�����
	m_Manager.AddState(EnemyStateName::Stop, std::make_shared<EnemyStateStop>(), player, *this);
}

void OperationEnemy::OnCollide(CollideActor & other)
{
	if (other.GetColor() == m_Color)
	{
		m_Manager.Collide(other);
		if (other.GetName() == "Light")
		{
			p_OperationManager->EnemyStop();
		}
		else if (other.GetName() == "ShiningLight")
		{
			p_OperationManager->EnemyStopPutLight();
		}
	}
}
