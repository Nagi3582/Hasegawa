#include "PlayerStateBase.h"
#include "../../../../Actor/CollideActor.h"
#include "../PlayerManager.h"
#include "../../../Item/ItemManager/ItemManager.h"
#include "../../../../World/IWorld.h"
#include "../../../../Actor/ActorGroup.h"
#include "../../../Item/Flashlight/FlashLight.h"
#include "../Player.h"
#include "../../../../Scene/SceneInfo/SceneInfo.h"
#include "../../../../Scene/SceneType/SceneType.h"
#include "../../../../Utility/Asset/SoundName.h"
#include "../../../Field/Field.h"
#include "../../../../Collide/Line.h"

PlayerStateBase::PlayerStateBase()
	: p_World{ nullptr }
	, p_Manager{ nullptr }
	, p_ItemManager{ nullptr }
	, p_Info{ nullptr }
	, m_IsHitEnemyAttack{ false }
{
}

PlayerStateBase::PlayerStateBase(Renderer& renderer)
	: p_World{ nullptr }
	, p_Manager{ nullptr }
	, p_ItemManager{ nullptr }
	, p_renderer{ &renderer }
	, m_IsHitEnemyAttack{ false }
{}

void PlayerStateBase::SetUp(IWorld & world, PlayerManager & manager, ItemManager & item, SceneInfo& info)
{
	p_World = &world;
	p_Manager = &manager;
	p_ItemManager = &item;
	p_Info = &info;
	m_IsHitEnemyAttack = false;
}

void PlayerStateBase::Collide(CollideActor & other)
{
	if (p_Manager->GetState() != PlayerState::Damage && p_Manager->GetDamageTime() <= 0 && m_IsHitEnemyAttack == false)
	{
		if (other.GetName() == "RedEnemyAttack")
		{
			p_Manager->SetNextState(PlayerState::Damage);

			HitEnemy();
			HitEnemy();
			gsPlaySE((int)SoundName::HitSE);
			m_IsHitEnemyAttack = true;
		}
		else if (other.GetName() == "EnemyAttack")
		{
			p_Manager->SetNextState(PlayerState::Damage);

			HitEnemy();
			gsPlaySE((int)SoundName::HitSE);
			m_IsHitEnemyAttack = true;
		}
	}

	OnCollide(other);
}

void PlayerStateBase::Shutdown()
{
	OnShutdown();
	p_World = nullptr;
	p_Manager = nullptr;
	p_ItemManager = nullptr;
}

void PlayerStateBase::HitEnemy()
{
	if (p_Info->m_CurrentScene == SceneType::Operation || p_ItemManager->GetLightSize(p_ItemManager->GetColor()) <= 0)return;


	GSvector3 l_Position = p_Manager->GetPlayer()->GetPosition() + p_Manager->GetRotate().getAxisZ().getNormalized() * 7.0f;

	Line l_Line(p_Manager->GetPlayer()->GetPosition(), l_Position);
	if (p_World->GetField()->IsCollide(l_Line))
	{
		l_Position = p_Manager->GetPlayer()->GetPosition() + p_Manager->GetRotate().getAxisX().getNormalized() * 7.0f;
	}
	l_Line = Line(p_Manager->GetPlayer()->GetPosition(), l_Position);
	if (p_World->GetField()->IsCollide(l_Line))
	{
		l_Position = p_Manager->GetPlayer()->GetPosition() - p_Manager->GetRotate().getAxisX().getNormalized() * 7.0f;
	}

	GSvector3 l_RandPosition(0.0f, 0.0f, 0.0f);
	const float l_Leave = 2.0f;	//ƒ‰ƒ“ƒ_ƒ€‚Ì”ÍˆÍ
	l_RandPosition.x = gsRandf(-l_Leave, l_Leave);
	l_RandPosition.z = gsRandf(-l_Leave, l_Leave);
	l_Position = l_Position + l_RandPosition;



	p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<Flashlight>(
		*p_World, l_Position, p_ItemManager->GetColor(), *p_ItemManager, p_ItemManager->BatterySize()));

	p_ItemManager->HitEnemy();

	if (p_ItemManager->GetLightSize(p_ItemManager->GetColor()) <= 0)
		p_ItemManager->ChangeColor(true);
}
