#include "EnemyStateMiss.h"
#include "../EnemyStateManager.h"
#include "../EnemyStateName.h"
#include "../../../../../UI/UITexture.h"

EnemyStateMiss::EnemyStateMiss()
	: EnemyStateBase{}
{
}

void EnemyStateMiss::Initialize()
{
	p_Manager->SetMotionID(7);
}

void EnemyStateMiss::Update(float deltaTime)
{
	if (p_Manager->GetTimer() >= 60)
	{
		p_Manager->SetNextState(EnemyStateName::Idle);
	}
}

void EnemyStateMiss::Draw() const
{
}

void EnemyStateMiss::Shutdown()
{
}
