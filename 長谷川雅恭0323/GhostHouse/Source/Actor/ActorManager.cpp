#include "ActorManager.h"
#include "ActorGroup.h"

ActorManager::ActorManager()
{
	Initialize();
}

void ActorManager::Initialize()
{
	m_Actors[ActorGroup::Effect] = std::make_shared<Actor>();

	m_CollideActors[ActorGroup::Player] = std::make_shared<CollideActor>();
	m_CollideActors[ActorGroup::HitToPlayer] = std::make_shared<CollideActor>();
	m_CollideActors[ActorGroup::Light] = std::make_shared<CollideActor>();

	m_Root.ClearChildren();
	m_Root.AddChild(m_CollideActors[ActorGroup::HitToPlayer]);
	m_Root.AddChild(m_CollideActors[ActorGroup::Player]);
	m_Root.AddChild(m_CollideActors[ActorGroup::Light]);
	m_Root.AddChild(m_Actors[ActorGroup::Effect]);

}

void ActorManager::Update(float deltaTime)
{
	m_Root.Update(deltaTime);
	Collide();
	m_Root.RemoveChildren();
	m_CollideActors[ActorGroup::Player]->RemoveCollideChildren();
	m_CollideActors[ActorGroup::HitToPlayer]->RemoveCollideChildren();
	m_CollideActors[ActorGroup::Light]->RemoveCollideChildren();
	m_Actors[ActorGroup::Effect]->RemoveChildren();
}

void ActorManager::EffectUpdate(float deltaTime)
{
	m_Actors[ActorGroup::Effect]->Update(deltaTime);
	m_Actors[ActorGroup::Effect]->RemoveChildren();
}

void ActorManager::Draw(const bool is_shadow, Renderer& m_renderer) const
{
	m_Root.Draw(is_shadow, m_renderer);
}

void ActorManager::AddActor(ActorGroup group, const ActorPtr & actor)
{
	m_Actors[group]->AddChild(actor);
}

void ActorManager::AddCollideActor(ActorGroup group, const CollideActorPtr& actor)
{
	m_CollideActors[group]->AddCollideChild(actor);
}

ActorPtr ActorManager::FindActor(const std::string & name)
{
	return m_Root.FindChildren(name);
}

void ActorManager::Collide()
{
	m_CollideActors[ActorGroup::Player]->CollideChildren(*m_CollideActors[ActorGroup::HitToPlayer]);
	m_CollideActors[ActorGroup::Light]->CollideChildren(*m_CollideActors[ActorGroup::HitToPlayer]);
}
