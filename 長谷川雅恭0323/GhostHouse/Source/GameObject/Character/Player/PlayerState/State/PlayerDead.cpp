#include "PlayerDead.h"
#include "../../../../../Scene/SceneInfo/SceneInfo.h"

PlayerDead::PlayerDead()
	: PlayerStateBase{}
{
}

void PlayerDead::Initialize()
{
	p_Info->m_PlayerDead = true;
	p_Info->m_Pause = true;
}

void PlayerDead::Update(float deltaTime)
{
}

void PlayerDead::OnCollide(CollideActor & other)
{
}

void PlayerDead::Draw() const
{}
