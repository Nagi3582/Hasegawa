#include "DoorGoalCollide.h"
#include "../../../Collide/BoundingSphere.h"
#include "../../../Scene/SceneInfo/SceneInfo.h"

DoorGoalCollide::DoorGoalCollide(IWorld& world, GSvector3 position, SceneInfo& info, SceneType& next)
	: CollideActor{ world,"DoorCollide",position,new BoundingSphere(GSvector3(0,0,0),5.0f) }
	, m_Info{ info }
	, m_NextScene{ next }
{}

void DoorGoalCollide::OnUpdate(float deltaTime)
{
}

void DoorGoalCollide::OnDraw(bool is_shadow, Renderer & renderer) const
{
}

void DoorGoalCollide::OnCollide(CollideActor & other)
{
	if (other.GetName() == "Player")
	{
		m_Info.m_Goal = true;
		m_Info.m_NextScene = m_NextScene;
	}
}
