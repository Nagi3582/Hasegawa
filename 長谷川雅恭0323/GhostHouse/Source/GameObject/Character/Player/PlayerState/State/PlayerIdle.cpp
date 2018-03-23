#include "PlayerIdle.h"
#include "../../PlayerManager.h"
#include "../../../../../Actor/CollideActor.h"
#include "../../../../Item/ItemManager/ItemManager.h"
#include "../../../../../Utility/Renderer/Renderer.h"
#include "../../../../../UIObject/Operation/OperationManager.h"

PlayerIdle::PlayerIdle(Renderer& renderer)
	: PlayerStateBase{ renderer }
	, m_IsPickUp{ false }
	, p_OperationManager{ nullptr }
{
}

PlayerIdle::PlayerIdle(Renderer & renderer, OperationManager & operationManager)
	: PlayerStateBase{ renderer }
	, m_IsPickUp{ false }
	, p_OperationManager{ &operationManager }
{
}

void PlayerIdle::Initialize()
{
	p_Manager->SetMotionID(3);
}

void PlayerIdle::Update(float deltaTime)
{
	if (p_OperationManager != nullptr && p_OperationManager->IsMove() == false)
	{
		p_Manager->SetSpeed(0.0f);
		if (p_Manager->RightStick(deltaTime))
		{
			p_OperationManager->PlayerRotate();
		}
	}
	else
	{
		p_Manager->Rotate(deltaTime);
		p_Manager->Move(deltaTime);
	}


	if (p_Manager->GetSpeed() >= 0.1f)
		p_Manager->SetMotionID(4);
	else
		p_Manager->SetMotionID(3);


	if (gsXBoxPadButtonTrigger(0, GS_XBOX_PAD_A))
	{
		if (p_ItemManager->IsHaveLight() &&
			p_renderer->get_light_params_size() < 5 &&
			m_IsPickUp == false)
		{
			p_Manager->SetNextState(PlayerState::Put);
		}
	}
	m_IsPickUp = false;
}

void PlayerIdle::OnCollide(CollideActor & other)
{
	if (other.GetName() == "PutLight")
	{
		m_IsPickUp = true;
		if (gsXBoxPadButtonTrigger(0, GS_XBOX_PAD_A))
		{
			p_Manager->SetNextState(PlayerState::PickUp);
			if (p_OperationManager != nullptr)
			{
				p_OperationManager->TakeShiningLight();
			}
		}

	}
}

void PlayerIdle::Draw() const
{
}