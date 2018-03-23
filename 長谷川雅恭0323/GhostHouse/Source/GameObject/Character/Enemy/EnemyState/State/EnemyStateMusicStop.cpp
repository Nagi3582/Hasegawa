#include "EnemyStateMusicStop.h"
#include "../EnemyStateManager.h"
#include "../../../../../World/IWorld.h"
#include "../../../../../Actor/ActorGroup.h"
#include "../../../../Item/MusicBox/MusicBox.h"

#include <GSmusic.h>
#include "../../../../../Utility/Asset/SoundName.h"


EnemyStateMusicStop::EnemyStateMusicStop(SceneInfo& info)
	: EnemyStateBase{}
	, m_PutMusicBox{ false }
	, m_Info{ info }
{
}

void EnemyStateMusicStop::Initialize()
{
	if (m_PutMusicBox == true)return;

	GSvector3 l_Position = p_Manager->GetPosition();
	const float l_Leave = 3.0f;
	l_Position.x += gsRandf(-l_Leave, l_Leave);
	l_Position.z += gsRandf(-l_Leave, l_Leave);
	l_Position.y = 0.0f;
	p_Manager->GetWorld()->AddCollideActor(ActorGroup::HitToPlayer, std::make_shared<MusicBox>(*p_Manager->GetWorld(), l_Position, m_Info));

	m_PutMusicBox = true;
}

void EnemyStateMusicStop::Update(float deltaTime)
{
	if (p_Manager->GetTimer() >= 5)
	{
		p_Manager->SetNextState(EnemyStateName::Idle);
	}
}

void EnemyStateMusicStop::Draw() const
{
}

void EnemyStateMusicStop::Shutdown()
{
}
