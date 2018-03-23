#include "DummyKey.h"
#include "../../../Collide/BoundingSphere.h"
#include "../../../World/IWorld.h"
#include "../../../Actor/ActorGroup.h"
#include "../../Effect/Smoke/Smoke.h"
#include "../../../Scene/SceneInfo/SceneInfo.h"
#include "../../Character/Enemy/WhiteEnemy.h"

DummyKey::DummyKey(IWorld & world, GSvector3 position, Camera & camera, SceneInfo & info)
	: CollideActor{ world,"DummyKey",position,new BoundingSphere(GSvector3(0.0f,0.0f,0.0f),1.0f) }
	, p_Camera{ &camera }
	, m_Info{ info }
{
}

void DummyKey::OnUpdate(float deltaTime)
{
}

void DummyKey::OnCollide(CollideActor & other)
{
	if (other.GetName() == "Player")
	{
		p_World->AddActor(ActorGroup::Effect, std::make_shared<Smoke>(*p_World, m_Position, *p_Camera, m_Info));
		//p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<WhiteEnemy>(*p_World, m_Position, p_Player, p_Renderer));
		Dead();
		m_Info.m_Direction = true;
	}

}

void DummyKey::OnDraw(bool is_shadow, Renderer & renderer) const
{
}
