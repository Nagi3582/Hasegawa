#include "EnemyStateBase.h"
#include "../../../../Actor/CollideActor.h"
#include "EnemyStateManager.h"
#include "../../../Light/CollideLight/CollideLight.h"
#include "../../../Light/LightColor.h"

EnemyStateBase::EnemyStateBase()
	: p_Me{ nullptr }
	, p_Player{ nullptr }
	, p_Manager{ nullptr }
{};

void EnemyStateBase::SetUp(CollideActor & player, ModelBase & me, EnemyStateManager & manager)
{
	p_Player = &player;
	p_Me = &me;
	p_Manager = &manager;
}

void EnemyStateBase::Collide(CollideActor & other)
{
	if (other.GetName() == "Light" || other.GetName() == "ShiningLight")
	{
		p_Manager->SetNextState(EnemyStateName::Stop);
	}

}
