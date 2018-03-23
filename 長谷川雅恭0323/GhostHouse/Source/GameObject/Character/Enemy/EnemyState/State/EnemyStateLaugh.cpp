#include "EnemyStateLaugh.h"
#include "../EnemyStateManager.h"

EnemyStateLaugh::EnemyStateLaugh()
	: EnemyStateBase{}
{
}

void EnemyStateLaugh::Initialize()
{
	p_Manager->SetMotionID(6);
}

void EnemyStateLaugh::Update(float deltaTime)
{
	if (p_Manager->GetTimer() >= 180)
		p_Manager->SetNextState(EnemyStateName::Idle);
}

void EnemyStateLaugh::Draw() const
{
}

void EnemyStateLaugh::Shutdown()
{
}
