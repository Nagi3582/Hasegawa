#include "EnemyStateRandomWalk.h"
#include "../../../ModelBase.h"
#include "../EnemyStateManager.h"
#include "../../../../../Utility/Math/Math.h"
#include "../../../../../Actor/ActorGroup.h"
#include "../../../../../World/IWorld.h"
#include "../../../../Field/Field.h"
#include "../../../../../Collide/Line.h"


#include "../../WhiteEnemy.h"
#include "../../RedEnemy.h"
#include "../../GreenEnemy.h"
#include "../../BlueEnemy.h"
#include "../../../../Light/CollideLight/CollideLight.h"

#include "../../../../../Utility/Asset/SoundName.h"


const float LEAVE_MAX = 20.0f;	//ŽŸ‚ÌˆÚ“®’n“_‚ÌÅ‘å’l
const float ADD_TIME = 60 * 20;	//“G‚ð’Ç‰Á‚·‚é‚Ü‚Å‚ÌŽžŠÔ
const float MAX_SPEED = 0.3f;

EnemyStateRandomWalk::EnemyStateRandomWalk(Renderer& renderer)
	: EnemyStateBase{}
	, m_CurrentPoint{ 0.0f,0.0f,0.0f }
	, m_NextPoint{ 0.0f,0.0f,0.0f }
	, m_HaveMusicBox{ true }
	, p_Renderer{ &renderer }
	, m_SECounter{ 0 }
{
}

void EnemyStateRandomWalk::Initialize()
{
	m_NextPoint.x = gsRandf(p_Me->GetPosition().x - LEAVE_MAX, p_Me->GetPosition().x + LEAVE_MAX);
	m_NextPoint.z = gsRandf(p_Me->GetPosition().z - LEAVE_MAX, p_Me->GetPosition().z + LEAVE_MAX);
	p_Manager->SetMotionID(5);
	SetPoint();
}

void EnemyStateRandomWalk::Update(float deltaTime)
{
	p_Manager->Rotate(deltaTime);

	Line l_Line(p_Me->GetPosition(), m_CurrentPoint);
	p_Manager->GetWorld()->GetField()->IsCollide(l_Line, &m_CurrentPoint);
	if (Math::Distance(p_Me->GetPosition(), m_CurrentPoint) <= 6.0f && m_HaveMusicBox == true)
	{
		SetPoint();
	}


	const float l_SpeedUp = 0.005f;
	p_Manager->SpeedUp(l_SpeedUp, MAX_SPEED, deltaTime);

	GSvector3 l_Velocity = p_Me->GetPosition() - m_CurrentPoint;

	p_Manager->SetVelocity(l_Velocity);
	p_Manager->Move(deltaTime);


	AddEnemy();


	float l_Distance = Math::Distance(p_Me->GetPosition(), p_Player->GetPosition());
	if (l_Distance <= 30.0f)
	{
		p_Manager->SetNextState(EnemyStateName::Approach);
		if (m_SECounter <= 0)
		{
			gsPlaySE((GSuint)SoundName::DiscoverySE);
			m_SECounter = 60;
		}
	}
	m_SECounter -= deltaTime / 2;
}

void EnemyStateRandomWalk::Collide(CollideActor & other)
{
	if (other.GetName() == "light")
	{
		CollideLight* light = static_cast<CollideLight*>(&other);

		p_Manager->SetNextState(EnemyStateName::Stop);
		m_HaveMusicBox = false;
	}
}

void EnemyStateRandomWalk::Draw() const
{
}

void EnemyStateRandomWalk::Shutdown()
{
}

void EnemyStateRandomWalk::SetPoint()
{
	m_CurrentPoint = m_NextPoint;
	m_NextPoint.x = gsRandf(p_Me->GetPosition().x - LEAVE_MAX, p_Me->GetPosition().x + LEAVE_MAX);
	m_NextPoint.z = gsRandf(p_Me->GetPosition().z - LEAVE_MAX, p_Me->GetPosition().z + LEAVE_MAX);
}

void EnemyStateRandomWalk::AddEnemy()
{
	if (p_Manager->GetTimer() >= ADD_TIME)
	{
		const int l_Rand = gsRand(0, 3);
		GSvector3 l_Position = p_Me->GetPosition();

		if (l_Rand == 0)
		{
			p_Manager->GetWorld()->AddCollideActor(
				ActorGroup::HitToPlayer, std::make_shared<WhiteEnemy>(*p_Manager->GetWorld(), l_Position, *p_Player, *p_Renderer));
		}
		else if (l_Rand == 1)
		{
			p_Manager->GetWorld()->AddCollideActor(
				ActorGroup::HitToPlayer, std::make_shared<RedEnemy>(*p_Manager->GetWorld(), l_Position, *p_Player, *p_Renderer));
		}
		else if (l_Rand == 2)
		{
			p_Manager->GetWorld()->AddCollideActor(
				ActorGroup::HitToPlayer, std::make_shared<GreenEnemy>(*p_Manager->GetWorld(), l_Position, *p_Player, *p_Renderer));
		}
		else if (l_Rand == 3)
		{
			p_Manager->GetWorld()->AddCollideActor(
				ActorGroup::HitToPlayer, std::make_shared<BlueEnemy>(*p_Manager->GetWorld(), l_Position, *p_Player, *p_Renderer));
		}

		p_Manager->TimerReset();
	}
}
