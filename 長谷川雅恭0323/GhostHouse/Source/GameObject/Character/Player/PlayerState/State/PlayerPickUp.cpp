#include "PlayerPickUp.h"
#include "../../PlayerManager.h"

#include "../../../../../Utility/Asset/SoundName.h"
#include "../../../../Item/ItemManager/ItemManager.h"
#include "../../../../../Actor/CollideActor.h"

PlayerPickUp::PlayerPickUp()
	: PlayerStateBase{}
	, m_IsPickUp{ false }
{
}

void PlayerPickUp::Initialize()
{
	p_Manager->SetMotionID(1);
	gsPlaySE((GSuint)SoundName::GetItemSE);
	m_IsPickUp = false;
}

void PlayerPickUp::Update(float deltaTime)
{
	p_Manager->SpeedUp(-0.05f, 0.5f, deltaTime);
	if (p_Manager->GetTimer() >= 60)
		p_Manager->SetNextState(PlayerState::Idle);
}

void PlayerPickUp::OnCollide(CollideActor & other)
{
	if (other.GetName() == "PutLight" && m_IsPickUp == false)
	{
		other.Dead();
		m_IsPickUp = true;
	}
}

void PlayerPickUp::Draw() const
{
}