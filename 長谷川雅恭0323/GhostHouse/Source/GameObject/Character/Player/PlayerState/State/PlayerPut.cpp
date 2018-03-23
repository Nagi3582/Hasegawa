#include "PlayerPut.h"
#include "../../PlayerManager.h"
#include "../../../../Item/ItemManager/ItemManager.h"
#include "../../../../../World/IWorld.h"
#include "../../../../../Actor/ActorGroup.h"
#include "../../../../Item/Flashlight/ShiningLight.h"
#include "../../Player.h"

#include "../../../../../Utility/Asset/SoundName.h"


PlayerPut::PlayerPut(Renderer& renderer)
	: PlayerStateBase{}
	, p_Renderer{ &renderer }
	, m_IsUseBattery{ true }
	, p_OperationManager{ nullptr }
{
}

PlayerPut::PlayerPut(Renderer & renderer, OperationManager & operationManager, bool is_UseBattery)
	: PlayerStateBase{}
	, p_Renderer{ &renderer }
	, m_IsUseBattery{ is_UseBattery }
	, p_OperationManager{ &operationManager }
{
}

void PlayerPut::Initialize()
{
	p_Manager->SetMotionID(1);
	if (p_OperationManager != nullptr)
	{
		p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<ShiningLight>(
			*p_World, p_Manager->GetPlayer()->GetPosition(), p_ItemManager->BatterySize(), p_ItemManager->GetColor(),
			*p_ItemManager, *p_Manager->GetPlayer(), *p_Renderer, *p_OperationManager, m_IsUseBattery));
	}
	else
	{
		p_World->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<ShiningLight>(
			*p_World, p_Manager->GetPlayer()->GetPosition(), p_ItemManager->BatterySize(), p_ItemManager->GetColor(),
			*p_ItemManager, *p_Manager->GetPlayer(), *p_Renderer, m_IsUseBattery));
	}

	p_ItemManager->RemoveLight(p_ItemManager->GetColor());


	if (p_ItemManager->GetLightSize(p_ItemManager->GetColor()) <= 0)
		p_ItemManager->ChangeColor(true);


	gsPlaySE((GSuint)SoundName::GetItemSE);
}

void PlayerPut::Update(float deltaTime)
{
	p_Manager->SpeedUp(-0.05f, 0.5f, deltaTime);
	if (p_Manager->GetTimer() >= 60)
		p_Manager->SetNextState(PlayerState::Idle);
}

void PlayerPut::OnCollide(CollideActor & other)
{
}

void PlayerPut::Draw() const
{
}
