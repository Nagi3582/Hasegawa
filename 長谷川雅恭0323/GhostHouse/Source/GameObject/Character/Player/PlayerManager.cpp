#include "PlayerManager.h"
#include "PlayerState/PlayerState.h"
#include "PlayerState/State/PlayerIdle.h"
#include "PlayerState/State/PlayerPut.h"
#include "PlayerState/State/PlayerDamage.h"
#include "PlayerState/State/PlayerPickUp.h"
#include "PlayerState/State/PlayerDead.h"

#include "../../../Utility/Asset/SoundName.h"

#include "Player.h"

const float SPEED_MAX = 0.4f;
const int WALKSE_SPEED = 20;

PlayerManager::PlayerManager(IWorld& world, Player& player, ItemManager& item, Renderer& renderer, SceneInfo& info)
	: m_Velocity{ 0.0f,0.0f,1.0f }
	, m_Rotate{ GS_MATRIX4_IDENTITY }
	, m_Speed{ 0.5f }
	, p_Player{ &player }
	, m_CurrentState{ nullptr }
	, m_CurrentStateName{ PlayerState::None }
	, m_Timer{ 0 }
	, m_LerpTimer{ 0 }
	, LERP_TIME{ 10 }
	, m_MotionID{ 2 }
	, m_NextStateName{ PlayerState::None }
	, p_World{ &world }
	, p_ItemManager{ &item }
	, m_Info{ info }
	, m_DamageTime{ 0 }
{
	SetUp(renderer);
	m_Rotate.rotateY(180);
}

void PlayerManager::SetUp(Renderer& renderer)
{
	m_States.clear();
	m_States[PlayerState::Idle] = std::make_shared<PlayerIdle>(renderer);
	m_States[PlayerState::Put] = std::make_shared<PlayerPut>(renderer);
	m_States[PlayerState::Damage] = std::make_shared<PlayerDamage>();
	m_States[PlayerState::PickUp] = std::make_shared<PlayerPickUp>();
	m_States[PlayerState::Dead] = std::make_shared<PlayerDead>();


	m_CurrentStateName = PlayerState::Idle;
	m_CurrentState = m_States[m_CurrentStateName];
	m_CurrentState->SetUp(*p_World, *this, *p_ItemManager, m_Info);
	m_CurrentState->Initialize();
}

void PlayerManager::SetUpOperation(Renderer & renderer, OperationManager& operationManager)
{
	m_States.clear();
	m_States[PlayerState::Idle] = std::make_shared<PlayerIdle>(renderer, operationManager);
	m_States[PlayerState::Put] = std::make_shared<PlayerPut>(renderer, operationManager, false);
	m_States[PlayerState::Damage] = std::make_shared<PlayerDamage>();
	m_States[PlayerState::PickUp] = std::make_shared<PlayerPickUp>();
	m_States[PlayerState::Dead] = std::make_shared<PlayerDead>();


	m_CurrentStateName = PlayerState::Idle;
	m_CurrentState = m_States[m_CurrentStateName];
	m_CurrentState->SetUp(*p_World, *this, *p_ItemManager, m_Info);
	m_CurrentState->Initialize();

}

void PlayerManager::Update(float deltaTime)
{
	m_CurrentState->Update(deltaTime);


	Change();

	m_Timer += deltaTime;
	m_DamageTime -= deltaTime;
}

void PlayerManager::Collide(CollideActor & other)
{
	m_CurrentState->Collide(other);
}

void PlayerManager::Change()
{
	if (m_NextStateName != PlayerState::None)
	{
		m_CurrentStateName = m_NextStateName;
		m_NextStateName = PlayerState::None;
		m_CurrentState->Shutdown();
		m_CurrentState = m_States[m_CurrentStateName];
		m_CurrentState->SetUp(*p_World, *this, *p_ItemManager, m_Info);
		m_CurrentState->Initialize();
		m_Timer = 0;
	}
}

void PlayerManager::WalkSE()
{
	if ((int)m_Timer % WALKSE_SPEED == 0)
		if (m_Velocity.x != 0.0f || m_Velocity.z != 0.0f)
			gsPlaySE((GSuint)SoundName::WalkSE);
}

GSvector3 PlayerManager::GetVelocity(float deltaTime)
{
	m_Velocity.normalize();
	return m_Velocity * m_Speed * deltaTime;
}

GSmatrix4 PlayerManager::GetRotate()const
{
	return m_Rotate;
}

float PlayerManager::GetSpeed() const
{
	return m_Speed;
}

void PlayerManager::Move(float deltaTime)
{
	GSvector2 l_Stick;
	gsXBoxPadGetLeftAxis(0, &l_Stick);

	m_Velocity = GSvector3(-l_Stick.x, 0.0f, l_Stick.y);
	m_Velocity.normalize();

	if (m_Velocity.x != 0.0f || m_Velocity.z != 0.0f)
	{
		SpeedUp(0.02f, SPEED_MAX, deltaTime);
	}
	else
	{
		SpeedUp(-0.05f, SPEED_MAX, deltaTime);
	}
	WalkSE();
}

void PlayerManager::Rotate(float deltaTime)
{
	if (RightStick(deltaTime) ||
		FaceForward(deltaTime))
		return;

}

bool PlayerManager::RightStick(float deltaTime)
{
	GSvector2 l_RightStick;
	gsXBoxPadGetRightAxis(0, &l_RightStick);
	if (l_RightStick.x != 0.0f || l_RightStick.y != 0.0f)
	{
		GSvector3 l_Vec3Stick(-l_RightStick.x, 0.0f, l_RightStick.y);

		m_LerpTimer = std::min(m_LerpTimer + deltaTime, LERP_TIME);
		GSvector3 l_Front = l_Vec3Stick.lerp(m_Rotate.getAxisZ(), m_LerpTimer);
		l_Front.y = 0.0f;
		l_Front.normalize();

		const GSvector3 l_Up = m_Rotate.getAxisY();
		const GSvector3 l_Left = l_Up.cross(l_Front);

		m_Rotate.setAxisX(l_Left);
		m_Rotate.setAxisY(l_Up);
		m_Rotate.setAxisZ(l_Front);
		return true;
	}
	return false;
}

bool PlayerManager::FaceForward(float deltaTime)
{
	if (m_Velocity.x != 0.0f || m_Velocity.z != 0.0f)
	{
		m_LerpTimer = std::min(m_LerpTimer + deltaTime, LERP_TIME);
		GSvector3 l_Front = m_Velocity.lerp(m_Rotate.getAxisZ(), m_LerpTimer);
		l_Front.y = 0.0f;
		l_Front.normalize();

		const GSvector3 l_Up = m_Rotate.getAxisY();
		const GSvector3 l_Left = l_Up.cross(l_Front);

		m_Rotate.setAxisX(l_Left);
		m_Rotate.setAxisY(l_Up);
		m_Rotate.setAxisZ(l_Front);

		return true;
	}
	m_LerpTimer = 0;
	return false;
}

void PlayerManager::SpeedUp(float plus, float max, float deltaTime)
{
	m_Speed += plus * deltaTime;
	m_Speed = CLAMP(m_Speed, 0.0f, max);
}

void PlayerManager::SetSpeed(float speed)
{
	m_Speed = speed;
}

int PlayerManager::GetMotionID() const
{
	return m_MotionID;
}

void PlayerManager::SetMotionID(int id)
{
	m_MotionID = id;
}

float PlayerManager::GetTimer()const
{
	return m_Timer;
}

void PlayerManager::ResetTimer()
{
	m_Timer = 0;
}

void PlayerManager::SetNextState(PlayerState state)
{
	m_NextStateName = state;
}

Player* PlayerManager::GetPlayer() const
{
	return p_Player;
}

PlayerState PlayerManager::GetState() const
{
	return m_CurrentStateName;
}

ItemManager & PlayerManager::get_item()
{
	return *p_ItemManager;
}

void PlayerManager::SetDamageTime(int time)
{
	m_DamageTime = time;
}

float PlayerManager::GetDamageTime() const
{
	return m_DamageTime;
}
