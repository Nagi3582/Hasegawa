#include "PlayerDamage.h"
#include "../../PlayerManager.h"
#include "../../../../Item/ItemManager/ItemManager.h"
#include "../../../../Light/LightColor.h"
#include "../../../../../Scene/SceneInfo/SceneInfo.h"
#include "../../../../../Scene/SceneType/SceneType.h"

PlayerDamage::PlayerDamage()
	: PlayerStateBase{}
{
}

void PlayerDamage::Initialize()
{
	p_Manager->SetMotionID(0);
	if (p_Info->m_CurrentScene != SceneType::Operation &&
		p_ItemManager->GetLightSize(LightColor::White) <= 0 &&
		p_ItemManager->GetLightSize(LightColor::Red) <= 0 &&
		p_ItemManager->GetLightSize(LightColor::Green) <= 0 &&
		p_ItemManager->GetLightSize(LightColor::Blue) <= 0)
	{
		p_Manager->SetNextState(PlayerState::Dead);
	}
}

void PlayerDamage::Update(float deltaTime)
{
	p_Manager->SpeedUp(-0.05f, 0.5f, deltaTime);
	if (p_Manager->GetTimer() >= 100)
	{
		p_Manager->SetNextState(PlayerState::Idle);
	}
}

void PlayerDamage::OnCollide(CollideActor & other)
{
}

void PlayerDamage::Draw() const
{
}

void PlayerDamage::OnShutdown()
{
	//30fps‚Ìˆ×*2‚·‚é
	p_Manager->SetDamageTime(60 * 4);
}
