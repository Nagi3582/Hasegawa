#include "EnemyStateStop.h"
#include "../../../../../Actor/CollideActor.h"
#include "../EnemyStateManager.h"
#include "../../../../../UI/UITexture.h"

EnemyStateStop::EnemyStateStop()
	: EnemyStateBase{}
{
}

void EnemyStateStop::Initialize()
{
	p_Manager->SetMotionID(8);
	p_Manager->GetMark()->HideOn();
	p_Manager->SetSpeed(0.0f);
}

void EnemyStateStop::Update(float deltaTime)
{
	p_Manager->SetMotionID(8);
	p_Manager->GetMark()->HideOn();

	if (p_Manager->GetTimer() >= 5)
	{
		p_Manager->SetNextState(EnemyStateName::Idle);
	}
}

void EnemyStateStop::Draw() const
{
}

void EnemyStateStop::Shutdown()
{
}
