#include "MusicEnemy.h"
#include "../../../Utility/Asset/MeshName.h"
#include "../../Light/LightColor.h"

#include "EnemyState/State/EnemyStateRandomWalk.h"
#include "EnemyState/State/EnemyStateEscape.h"
#include "EnemyState/State/EnemyStateAttack.h"
#include "EnemyState/State/EnemyStateMusicStop.h"

#include <GSmusic.h>
#include "../../../Utility/Asset/SoundName.h"

MusicEnemy::MusicEnemy(IWorld & world, GSvector3 position, CollideActor & player, Renderer& renderer, SceneInfo& info)
	: EnemyBase{ world,MeshName::WhiteEnemy,LightColor::White,position,player ,renderer }
	, p_Renderer{ &renderer }
	, m_Info{ info }
{
	SetState(player);
	m_Manager.SetUp(EnemyStateName::Idle);
	SetAnimation(renderer, MeshName::MusicEnemy, 0);
	gsStopMusic();
	gsBindMusic((GSuint)SoundName::MusixBox_BGM);
}

MusicEnemy::~MusicEnemy()
{
	gsStopMusic();
}

void MusicEnemy::SetState(CollideActor & player)
{
	m_Manager.AddState(EnemyStateName::Idle, std::make_shared<EnemyStateRandomWalk>(*p_Renderer), player, *this);
	m_Manager.AddState(EnemyStateName::Approach, std::make_shared<EnemyStateEscape>(), player, *this);
	m_Manager.AddState(EnemyStateName::Attack, std::make_shared<EnemyStateAttack>(30), player, *this);
	m_Manager.AddState(EnemyStateName::Stop, std::make_shared<EnemyStateMusicStop>(m_Info), player, *this);
}
