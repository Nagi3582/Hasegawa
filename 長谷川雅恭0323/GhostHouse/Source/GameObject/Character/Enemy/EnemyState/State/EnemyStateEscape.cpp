#include "EnemyStateEscape.h"
#include "../../../ModelBase.h"
#include "../EnemyStateManager.h"
#include <gslib.h>

EnemyStateEscape::EnemyStateEscape()
	: EnemyStateBase{}
{
}

void EnemyStateEscape::Initialize()
{
	GSvector3 l_Velocity = p_Player->GetPosition() - p_Me->GetPosition();
	p_Manager->SetVelocity(l_Velocity);
	p_Manager->SetMotionID(5);
}

void EnemyStateEscape::Update(float deltaTime)
{
	p_Manager->Rotate(deltaTime);
	p_Manager->Move(deltaTime);


	//“¦‚°‚éŽžŠÔ
	const float ESCAPE_TIME = 60 * 5;


	if (p_Manager->GetTimer() >= ESCAPE_TIME)
	{
		p_Manager->SetNextState(EnemyStateName::Idle);
	}
}

void EnemyStateEscape::Draw() const
{
}

void EnemyStateEscape::Shutdown()
{
}
